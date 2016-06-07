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

#ifndef INCLUDED_SVX_XFLBMPIT_HXX
#define INCLUDED_SVX_XFLBMPIT_HXX

#include <svl/eitem.hxx>
#include <svx/rectenum.hxx>
#include <svx/svxdllapi.h>

class SVX_DLLPUBLIC XFillBmpPosItem : public SfxEnumItem
{
public:
                            static SfxPoolItem* CreateDefault();
                            XFillBmpPosItem( RECT_POINT eRP = RP_MM );
                            SVX_DLLPRIVATE XFillBmpPosItem( SvStream& rIn );

    SVX_DLLPRIVATE virtual SfxPoolItem*    Clone( SfxItemPool* pPool = nullptr ) const override;
    SVX_DLLPRIVATE virtual SfxPoolItem*    Create( SvStream& rIn, sal_uInt16 nVer ) const override;

    SVX_DLLPRIVATE virtual bool GetPresentation( SfxItemPresentation ePres,
                                    SfxMapUnit eCoreMetric,
                                    SfxMapUnit ePresMetric,
                                    OUString &rText, const IntlWrapper * = nullptr ) const override;

    SVX_DLLPRIVATE virtual sal_uInt16           GetValueCount() const override;
    SVX_DLLPRIVATE RECT_POINT               GetValue() const { return (RECT_POINT) SfxEnumItem::GetValue(); }
    void dumpAsXml(struct _xmlTextWriter* pWriter) const override;
};


#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
