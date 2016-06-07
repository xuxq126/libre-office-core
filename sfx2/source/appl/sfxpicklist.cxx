/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#include <config_features.h>

#include <comphelper/lok.hxx>
#include <com/sun/star/document/XDocumentProperties.hpp>
#include <unotools/historyoptions.hxx>
#include <unotools/useroptions.hxx>
#include <tools/urlobj.hxx>
#include <framework/menuconfiguration.hxx>
#include <sax/tools/converter.hxx>
#include <svl/inethist.hxx>
#include <svl/stritem.hxx>
#include <svl/eitem.hxx>
#include <vcl/gdimtf.hxx>
#include <vcl/pngwrite.hxx>
#include <officecfg/Office/Common.hxx>
#include <osl/file.hxx>
#include <unotools/localfilehelper.hxx>
#include <cppuhelper/implbase.hxx>


#include <sfx2/app.hxx>
#include "sfxpicklist.hxx"
#include <sfx2/sfxuno.hxx>
#include "sfxtypes.hxx"
#include <sfx2/request.hxx>
#include <sfx2/sfxsids.hrc>
#include <sfx2/sfx.hrc>
#include <sfx2/event.hxx>
#include <sfx2/objsh.hxx>
#include <sfx2/bindings.hxx>
#include <sfx2/docfile.hxx>
#include "objshimp.hxx"
#include <stringhint.hxx>
#include <sfx2/docfilt.hxx>

#include <rtl/instance.hxx>

#include <algorithm>


using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::util;


class StringLength : public ::cppu::WeakImplHelper< XStringWidth >
{
    public:
        StringLength() {}
        virtual ~StringLength() {}

        // XStringWidth
        sal_Int32 SAL_CALL queryStringWidth( const OUString& aString )
            throw (css::uno::RuntimeException, std::exception) override
        {
            return aString.getLength();
        }
};


namespace
{
    class thePickListMutex
        : public rtl::Static<osl::Mutex, thePickListMutex> {};
}

void SfxPickList::AddDocumentToPickList( SfxObjectShell* pDocSh )
{
    if (pDocSh->IsAvoidRecentDocs() || comphelper::LibreOfficeKit::isActive())
        return;

    SfxMedium *pMed = pDocSh->GetMedium();
    if( !pMed )
        return;

    // Unnamed Documents and embedded-Documents not in Picklist
    if ( !pDocSh->HasName() ||
            SfxObjectCreateMode::STANDARD != pDocSh->GetCreateMode() )
        return;

    // Help not in History
    INetURLObject aURL( pDocSh->IsDocShared() ? pDocSh->GetSharedFileURL() : OUString( pMed->GetOrigURL() ) );
    if ( aURL.GetProtocol() == INetProtocol::VndSunStarHelp )
        return;

    if ( !pMed->IsUpdatePickList() )
        return;

    // add no document that forbids this (for example Message-Body)
    const SfxBoolItem* pPicklistItem = SfxItemSet::GetItem<SfxBoolItem>(pMed->GetItemSet(), SID_PICKLIST, false);
    if ( pPicklistItem && !pPicklistItem->GetValue() )
        return;

    // ignore hidden documents
    if ( !SfxViewFrame::GetFirst( pDocSh ) )
        return;

    OUString  aTitle = pDocSh->GetTitle(SFX_TITLE_PICKLIST);
    OUString  aFilter;
    std::shared_ptr<const SfxFilter> pFilter = pMed->GetOrigFilter();
    if ( pFilter )
        aFilter = pFilter->GetFilterName();

    boost::optional<OUString> aThumbnail;

    // generate the thumbnail
    //fdo#74834: only generate thumbnail for history if the corresponding option is not disabled in the configuration
    if (!pDocSh->IsModified() && !Application::IsHeadlessModeEnabled() &&
            officecfg::Office::Common::History::RecentDocsThumbnail::get())
    {
        // not modified => the document matches what is in the shell
        const SfxUnoAnyItem* pEncryptionDataItem = SfxItemSet::GetItem<SfxUnoAnyItem>(pMed->GetItemSet(), SID_ENCRYPTIONDATA, false);
        if ( pEncryptionDataItem )
        {
            // encrypted document, will show a generic document icon instead
            aThumbnail = OUString();
        }
        else
        {
            std::shared_ptr<GDIMetaFile> xMetaFile = pDocSh->GetPreviewMetaFile();
            BitmapEx aResultBitmap;
            if (xMetaFile->CreateThumbnail(aResultBitmap))
            {
                SvMemoryStream aStream(65535, 65535);
                vcl::PNGWriter aWriter(aResultBitmap);
                if (aWriter.Write(aStream))
                {
                    Sequence<sal_Int8> aSequence(static_cast<const sal_Int8*>(aStream.GetData()), aStream.Tell());
                    OUStringBuffer aBuffer;
                    ::sax::Converter::encodeBase64(aBuffer, aSequence);
                    aThumbnail = aBuffer.makeStringAndClear();
                }
            }
        }
    }

    // add to svtool history options
    SvtHistoryOptions().AppendItem( ePICKLIST,
            aURL.GetURLNoPass( INetURLObject::NO_DECODE ),
            aFilter,
            aTitle,
            OUString(),
            aThumbnail);

    if ( aURL.GetProtocol() == INetProtocol::File )
        Application::AddToRecentDocumentList( aURL.GetURLNoPass( INetURLObject::NO_DECODE ),
                                                                 (pFilter) ? pFilter->GetMimeType() : OUString(),
                                                                 (pFilter) ? pFilter->GetServiceName() : OUString() );
}

SfxPickList& SfxPickList::Get()
{
    static SfxPickList aUniqueInstance(SvtHistoryOptions().GetSize(ePICKLIST));
    return aUniqueInstance;
}

SfxPickList::SfxPickList( sal_uInt32 nAllowedMenuSize ) :
    m_nAllowedMenuSize( nAllowedMenuSize )
{
    m_xStringLength = new StringLength;
    m_nAllowedMenuSize = ::std::min( m_nAllowedMenuSize, (sal_uInt32)PICKLIST_MAXSIZE );
    StartListening( *SfxGetpApp() );
}

SfxPickList::~SfxPickList()
{
}


void SfxPickList::Notify( SfxBroadcaster&, const SfxHint& rHint )
{
    const SfxStringHint* pStringHint = dynamic_cast<const SfxStringHint*>(&rHint);
    if ( pStringHint )
    {
        if ( pStringHint->GetId() == SID_OPENURL )
            INetURLHistory::GetOrCreate()->PutUrl( INetURLObject( pStringHint->GetObject() ));
    }

    const SfxEventHint* pEventHint = dynamic_cast<const SfxEventHint*>(&rHint);
    if ( pEventHint )
    {
        // only ObjectShell-related events with media interest
        SfxObjectShell* pDocSh = pEventHint->GetObjShell();
        if( !pDocSh )
            return;

        switch ( pEventHint->GetEventId() )
        {
            case SFX_EVENT_CREATEDOC:
            {
                bool bAllowModif = pDocSh->IsEnableSetModified();
                if ( bAllowModif )
                    pDocSh->EnableSetModified( false );

                using namespace ::com::sun::star;
                uno::Reference<document::XDocumentProperties> xDocProps(
                    pDocSh->getDocProperties());
                if (xDocProps.is()) {
                    xDocProps->setAuthor( SvtUserOptions().GetFullName() );
                    ::DateTime now( ::DateTime::SYSTEM );
                    xDocProps->setCreationDate( now.GetUNODateTime() );
                }

                if ( bAllowModif )
                    pDocSh->EnableSetModified( bAllowModif );
            }
            break;

            case SFX_EVENT_OPENDOC:
            case SFX_EVENT_SAVEDOCDONE:
            case SFX_EVENT_SAVEASDOCDONE:
            case SFX_EVENT_SAVETODOCDONE:
            case SFX_EVENT_CLOSEDOC:
            {
                AddDocumentToPickList(pDocSh);
            }
            break;

            case SFX_EVENT_SAVEASDOC:
            {
                SfxMedium *pMedium = pDocSh->GetMedium();
                if (!pMedium)
                    return;

                // We're starting a "Save As". Add the current document (if it's
                // not a "new" document) to the "Recent Documents" list before we
                // switch to the new path.
                // If the current document is new, path will be empty.
                OUString path = pMedium->GetOrigURL();
                if (!path.isEmpty())
                {
                    AddDocumentToPickList(pDocSh);
                }
            }
            break;
        }
    }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
