/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "../gtk/gtkinst.cxx"

#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include "com/sun/star/lang/XServiceInfo.hpp"
#include "com/sun/star/lang/XSingleServiceFactory.hpp"
#include "com/sun/star/lang/XInitialization.hpp"
#include "com/sun/star/datatransfer/XTransferable.hpp"
#include "com/sun/star/datatransfer/clipboard/XClipboard.hpp"
#include "com/sun/star/datatransfer/clipboard/XClipboardEx.hpp"
#include "com/sun/star/datatransfer/clipboard/XClipboardNotifier.hpp"
#include "com/sun/star/datatransfer/clipboard/XClipboardListener.hpp"
#include "com/sun/star/datatransfer/clipboard/XFlushableClipboard.hpp"
#include "com/sun/star/datatransfer/clipboard/XSystemClipboard.hpp"
#include "com/sun/star/datatransfer/dnd/DNDConstants.hpp"
#include <comphelper/processfactory.hxx>
#include <comphelper/sequence.hxx>
#include "cppuhelper/compbase.hxx"
#include <cppuhelper/implbase.hxx>
#include <cppuhelper/supportsservice.hxx>

using namespace com::sun::star;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;

namespace
{
    struct TypeEntry
    {
        const char*     pNativeType;        // string corresponding to nAtom for the case of nAtom being uninitialized
        const char*     pType;              // Mime encoding on our side
    };

    static const TypeEntry aConversionTab[] =
    {
        { "ISO10646-1", "text/plain;charset=utf-16" },
        { "UTF8_STRING", "text/plain;charset=utf-8" },
        { "UTF-8", "text/plain;charset=utf-8" },
        { "text/plain;charset=UTF-8", "text/plain;charset=utf-8" },
        // ISO encodings
        { "ISO8859-2", "text/plain;charset=iso8859-2" },
        { "ISO8859-3", "text/plain;charset=iso8859-3" },
        { "ISO8859-4", "text/plain;charset=iso8859-4" },
        { "ISO8859-5", "text/plain;charset=iso8859-5" },
        { "ISO8859-6", "text/plain;charset=iso8859-6" },
        { "ISO8859-7", "text/plain;charset=iso8859-7" },
        { "ISO8859-8", "text/plain;charset=iso8859-8" },
        { "ISO8859-9", "text/plain;charset=iso8859-9" },
        { "ISO8859-10", "text/plain;charset=iso8859-10" },
        { "ISO8859-13", "text/plain;charset=iso8859-13" },
        { "ISO8859-14", "text/plain;charset=iso8859-14" },
        { "ISO8859-15", "text/plain;charset=iso8859-15" },
        // asian encodings
        { "JISX0201.1976-0", "text/plain;charset=jisx0201.1976-0" },
        { "JISX0208.1983-0", "text/plain;charset=jisx0208.1983-0" },
        { "JISX0208.1990-0", "text/plain;charset=jisx0208.1990-0" },
        { "JISX0212.1990-0", "text/plain;charset=jisx0212.1990-0" },
        { "GB2312.1980-0", "text/plain;charset=gb2312.1980-0" },
        { "KSC5601.1992-0", "text/plain;charset=ksc5601.1992-0" },
        // eastern european encodings
        { "KOI8-R", "text/plain;charset=koi8-r" },
        { "KOI8-U", "text/plain;charset=koi8-u" },
        // String (== iso8859-1)
        { "STRING", "text/plain;charset=iso8859-1" },
        // special for compound text
        { "COMPOUND_TEXT", "text/plain;charset=compound_text" },

        // PIXMAP
        { "PIXMAP", "image/bmp" }
    };

    class DataFlavorEq : public std::unary_function<const css::datatransfer::DataFlavor&, bool>
    {
    private:
        const css::datatransfer::DataFlavor& m_rData;
    public:
        explicit DataFlavorEq(const css::datatransfer::DataFlavor& rData) : m_rData(rData) {}
        bool operator() (const css::datatransfer::DataFlavor& rData) const
        {
            return rData.MimeType == m_rData.MimeType &&
                   rData.DataType  == m_rData.DataType;
        }
    };
}

std::vector<css::datatransfer::DataFlavor> GtkTransferable::getTransferDataFlavorsAsVector(GdkAtom *targets, gint n_targets)
{
    std::vector<css::datatransfer::DataFlavor> aVector;

    bool bHaveText = false, bHaveUTF16 = false;

    for (gint i = 0; i < n_targets; ++i)
    {
        gchar* pName = gdk_atom_name(targets[i]);
        const char* pFinalName = pName;
        css::datatransfer::DataFlavor aFlavor;

        for (size_t j = 0; j < SAL_N_ELEMENTS(aConversionTab); ++j)
        {
            if (rtl_str_compare(pName, aConversionTab[j].pNativeType) == 0)
            {
                pFinalName = aConversionTab[j].pType;
                break;
            }
        }

        aFlavor.MimeType = OUString(pFinalName,
                                    rtl_str_getLength(pFinalName),
                                    RTL_TEXTENCODING_UTF8);

        m_aMimeTypeToAtom[aFlavor.MimeType] = targets[i];

        aFlavor.DataType = cppu::UnoType<Sequence< sal_Int8 >>::get();

        sal_Int32 nIndex(0);
        if (aFlavor.MimeType.getToken(0, ';', nIndex) == "text/plain")
        {
            bHaveText = true;
            OUString aToken(aFlavor.MimeType.getToken(0, ';', nIndex));
            if (aToken == "charset=utf-16")
            {
                bHaveUTF16 = true;
                aFlavor.DataType = cppu::UnoType<OUString>::get();
            }
        }
        aVector.push_back(aFlavor);
        g_free(pName);
    }

    //If we have text, but no UTF-16 format which is basically the only
    //text-format LibreOffice supports for cnp then claim we do and we
    //will convert on demand
    if (bHaveText && !bHaveUTF16)
    {
        css::datatransfer::DataFlavor aFlavor;
        aFlavor.MimeType = "text/plain;charset=utf-16";
        aFlavor.DataType = cppu::UnoType<OUString>::get();
        aVector.push_back(aFlavor);
    }

    return aVector;
}


css::uno::Sequence<css::datatransfer::DataFlavor> SAL_CALL GtkTransferable::getTransferDataFlavors()
        throw(css::uno::RuntimeException, std::exception)
{
    return comphelper::containerToSequence(getTransferDataFlavorsAsVector());
}

sal_Bool SAL_CALL GtkTransferable::isDataFlavorSupported(const css::datatransfer::DataFlavor& rFlavor)
        throw(css::uno::RuntimeException, std::exception)
{
    const std::vector<css::datatransfer::DataFlavor> aAll =
        getTransferDataFlavorsAsVector();

    return std::find_if(aAll.begin(), aAll.end(), DataFlavorEq(rFlavor)) != aAll.end();
}

class GtkClipboardTransferable : public GtkTransferable
{
private:
    GdkAtom m_nSelection;
public:

    explicit GtkClipboardTransferable(GdkAtom nSelection)
        : m_nSelection(nSelection)
    {
    }

    /*
     * XTransferable
     */

    virtual css::uno::Any SAL_CALL getTransferData(const css::datatransfer::DataFlavor& rFlavor)
        throw(css::datatransfer::UnsupportedFlavorException,
              css::io::IOException,
              css::uno::RuntimeException, std::exception
              ) override
    {
        GtkClipboard* clipboard = gtk_clipboard_get(m_nSelection);
        if (rFlavor.MimeType == "text/plain;charset=utf-16")
        {
            OUString aStr;
            gchar *pText = gtk_clipboard_wait_for_text(clipboard);
            if (pText)
                aStr = OUString(pText, rtl_str_getLength(pText), RTL_TEXTENCODING_UTF8);
            g_free(pText);
            css::uno::Any aRet;
            aRet <<= aStr.replaceAll("\r\n", "\n");
            return aRet;
        }

        auto it = m_aMimeTypeToAtom.find(rFlavor.MimeType);
        if (it == m_aMimeTypeToAtom.end())
            return css::uno::Any();

        css::uno::Any aRet;
        GtkSelectionData* data = gtk_clipboard_wait_for_contents(clipboard,
                                                                 it->second);
        if (!data)
        {
            return css::uno::Any();
        }
        gint length;
        const guchar *rawdata = gtk_selection_data_get_data_with_length(data,
                                                                        &length);
        Sequence<sal_Int8> aSeq(reinterpret_cast<const sal_Int8*>(rawdata), length);
        gtk_selection_data_free(data);
        aRet <<= aSeq;
        return aRet;
    }

    std::vector<css::datatransfer::DataFlavor> getTransferDataFlavorsAsVector()
        override
    {
        std::vector<css::datatransfer::DataFlavor> aVector;

        GtkClipboard* clipboard = gtk_clipboard_get(m_nSelection);

        GdkAtom *targets;
        gint n_targets;
        if (gtk_clipboard_wait_for_targets(clipboard, &targets, &n_targets))
        {
            aVector = GtkTransferable::getTransferDataFlavorsAsVector(targets, n_targets);
            g_free(targets);
        }

        return aVector;
    }
};

//We want to use gtk_clipboard_get_owner own owner-change to distinguish between
//us gaining the clipboard ownership vs losing it. To do that we need to use
//gtk_clipboard_set_with_owner and to do that we need a GObject, so define
//one here for that purpose and just give it a VclGtkClipboard* member
class VclGtkClipboard;

struct ClipboardOwner
{
    GObject parent_instance;

    /* instance members */
    VclGtkClipboard* m_pThis;
};

struct ClipboardOwnerClass
{
  GObjectClass parent_class;

  /* class members */
};

#define CLIPBOARD_OWNER_OBJECT           (clipboard_owner_get_type ())
#define CLIPBOARD_OWNER(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), CLIPBOARD_OWNER_OBJECT, ClipboardOwner))

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#endif
G_DEFINE_TYPE(ClipboardOwner, clipboard_owner, G_TYPE_OBJECT);
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

static void clipboard_owner_class_init (ClipboardOwnerClass *)
{
}

static void clipboard_owner_init(ClipboardOwner *)
{
}

class VclGtkClipboard :
        public cppu::WeakComponentImplHelper<
        datatransfer::clipboard::XSystemClipboard,
        datatransfer::clipboard::XFlushableClipboard,
        XServiceInfo>
{
    GdkAtom                                                  m_nSelection;
    osl::Mutex                                               m_aMutex;
    ClipboardOwner*                                          m_pOwner;
    gulong                                                   m_nOwnerChangedSignalId;
    Reference<css::datatransfer::XTransferable>              m_aContents;
    Reference<css::datatransfer::clipboard::XClipboardOwner> m_aOwner;
    std::list< Reference<css::datatransfer::clipboard::XClipboardListener> > m_aListeners;
    std::vector<GtkTargetEntry> m_aGtkTargets;
    VclToGtkHelper m_aConversionHelper;

public:

    explicit VclGtkClipboard(GdkAtom nSelection);
    virtual ~VclGtkClipboard();

    /*
     * XServiceInfo
     */

    virtual OUString SAL_CALL getImplementationName() throw( RuntimeException, std::exception ) override;
    virtual sal_Bool SAL_CALL supportsService( const OUString& ServiceName ) throw( RuntimeException, std::exception ) override;
    virtual Sequence< OUString > SAL_CALL getSupportedServiceNames() throw( RuntimeException, std::exception ) override;

    /*
     * XClipboard
     */

    virtual Reference< css::datatransfer::XTransferable > SAL_CALL getContents()
        throw(RuntimeException, std::exception) override;

    virtual void SAL_CALL setContents(
        const Reference< css::datatransfer::XTransferable >& xTrans,
        const Reference< css::datatransfer::clipboard::XClipboardOwner >& xClipboardOwner )
        throw(RuntimeException, std::exception) override;

    virtual OUString SAL_CALL getName()
        throw(RuntimeException, std::exception) override;

    /*
     * XClipboardEx
     */

    virtual sal_Int8 SAL_CALL getRenderingCapabilities()
        throw(RuntimeException, std::exception) override;

    /*
     * XFlushableClipboard
     */
    virtual void SAL_CALL flushClipboard()
        throw(RuntimeException, std::exception) override;

    /*
     * XClipboardNotifier
     */
    virtual void SAL_CALL addClipboardListener(
        const Reference< css::datatransfer::clipboard::XClipboardListener >& listener )
        throw(RuntimeException, std::exception) override;

    virtual void SAL_CALL removeClipboardListener(
        const Reference< css::datatransfer::clipboard::XClipboardListener >& listener )
        throw(RuntimeException, std::exception) override;

    void ClipboardGet(GtkClipboard *clipboard, GtkSelectionData *selection_data, guint info);
    void ClipboardClear(GtkClipboard *clipboard);
    void OwnerChanged(GtkClipboard *clipboard, GdkEvent *event);
};

OUString VclGtkClipboard::getImplementationName() throw( RuntimeException, std::exception )
{
    return OUString("com.sun.star.datatransfer.VclGtkClipboard");
}

Sequence< OUString > VclGtkClipboard::getSupportedServiceNames() throw( RuntimeException, std::exception )
{
    Sequence<OUString> aRet { "com.sun.star.datatransfer.clipboard.SystemClipboard" };
    return aRet;
}

sal_Bool VclGtkClipboard::supportsService( const OUString& ServiceName ) throw( RuntimeException, std::exception )
{
    return cppu::supportsService(this, ServiceName);
}

Reference< css::datatransfer::XTransferable > VclGtkClipboard::getContents() throw( RuntimeException, std::exception )
{
    if (G_OBJECT(m_pOwner) != gtk_clipboard_get_owner(gtk_clipboard_get(m_nSelection)) &&
        !m_aContents.is())
    {
        //tdf#93887 This is the system clipboard/selection. We fetch it when we are not
        //the owner of the clipboard and have not already fetched it.
        m_aContents = new GtkClipboardTransferable(m_nSelection);
    }
    return m_aContents;
}

void VclGtkClipboard::ClipboardGet(GtkClipboard* /*clipboard*/, GtkSelectionData *selection_data,
                                   guint info)
{
    if (!m_aContents.is())
        return;
    m_aConversionHelper.setSelectionData(m_aContents, selection_data, info);
}

void VclGtkClipboard::OwnerChanged(GtkClipboard* clipboard, GdkEvent* /*event*/)
{
    if (G_OBJECT(m_pOwner) != gtk_clipboard_get_owner(clipboard))
    {
        //null out m_aContents to return control to the system-one which
        //will be retrieved if getContents is called again
        setContents(Reference<css::datatransfer::XTransferable>(),
                    Reference<css::datatransfer::clipboard::XClipboardOwner>());
    }
}

void VclGtkClipboard::ClipboardClear(GtkClipboard * /*clipboard*/)
{
    for (auto &a : m_aGtkTargets)
        g_free(a.target);
    m_aGtkTargets.clear();
}

GtkTargetEntry VclToGtkHelper::makeGtkTargetEntry(const css::datatransfer::DataFlavor& rFlavor)
{
    GtkTargetEntry aEntry;
    aEntry.target =
        g_strdup(OUStringToOString(rFlavor.MimeType, RTL_TEXTENCODING_UTF8).getStr());
    aEntry.flags = 0;
    auto it = std::find_if(aInfoToFlavor.begin(), aInfoToFlavor.end(),
                        DataFlavorEq(rFlavor));
    if (it != aInfoToFlavor.end())
        aEntry.info = std::distance(aInfoToFlavor.begin(), it);
    else
    {
        aEntry.info = aInfoToFlavor.size();
        aInfoToFlavor.push_back(rFlavor);
    }
    return aEntry;
}

void VclToGtkHelper::setSelectionData(const Reference<css::datatransfer::XTransferable> &rTrans,
                                      GtkSelectionData *selection_data, guint info)
{
    GdkAtom type(gdk_atom_intern(OUStringToOString(aInfoToFlavor[info].MimeType,
                                                   RTL_TEXTENCODING_UTF8).getStr(),
                                 false));

    css::datatransfer::DataFlavor aFlavor(aInfoToFlavor[info]);
    if (aFlavor.MimeType == "UTF8_STRING" || aFlavor.MimeType == "STRING")
        aFlavor.MimeType = "text/plain;charset=utf-8";

    Sequence<sal_Int8> aData;
    Any aValue;

    try
    {
        aValue = rTrans->getTransferData(aFlavor);
    }
    catch (...)
    {
    }

    if (aValue.getValueTypeClass() == TypeClass_STRING)
    {
        OUString aString;
        aValue >>= aString;
        aData = Sequence< sal_Int8 >( reinterpret_cast<sal_Int8 const *>(aString.getStr()), aString.getLength() * sizeof( sal_Unicode ) );
    }
    else if (aValue.getValueType() == cppu::UnoType<Sequence< sal_Int8 >>::get())
    {
        aValue >>= aData;
    }
    else if (aFlavor.MimeType == "text/plain;charset=utf-8")
    {
        //didn't have utf-8, try utf-16 and convert
        aFlavor.MimeType = "text/plain;charset=utf-16";
        aFlavor.DataType = cppu::UnoType<OUString>::get();
        try
        {
            aValue = rTrans->getTransferData(aFlavor);
        }
        catch (...)
        {
        }
        OUString aString;
        aValue >>= aString;
        OString aUTF8String(OUStringToOString(aString, RTL_TEXTENCODING_UTF8));
        gtk_selection_data_set(selection_data, type, 8,
                               reinterpret_cast<const guchar *>(aUTF8String.getStr()),
                               aUTF8String.getLength());
        return;
    }

    gtk_selection_data_set(selection_data, type, 8,
                           reinterpret_cast<const guchar *>(aData.getArray()),
                           aData.getLength());
}

namespace
{
    void ClipboardGetFunc(GtkClipboard *clipboard, GtkSelectionData *selection_data,
                          guint info,
                          gpointer user_data_or_owner)
    {
        VclGtkClipboard* pThis = CLIPBOARD_OWNER(user_data_or_owner)->m_pThis;
        pThis->ClipboardGet(clipboard, selection_data, info);
    }

    void ClipboardClearFunc(GtkClipboard *clipboard, gpointer user_data_or_owner)
    {
        VclGtkClipboard* pThis = CLIPBOARD_OWNER(user_data_or_owner)->m_pThis;
        pThis->ClipboardClear(clipboard);
    }

    void handle_owner_change(GtkClipboard *clipboard, GdkEvent *event, gpointer user_data)
    {
        VclGtkClipboard* pThis = static_cast<VclGtkClipboard*>(user_data);
        pThis->OwnerChanged(clipboard, event);
    }
}

VclGtkClipboard::VclGtkClipboard(GdkAtom nSelection)
    : cppu::WeakComponentImplHelper<datatransfer::clipboard::XSystemClipboard,
                                    datatransfer::clipboard::XFlushableClipboard, XServiceInfo>
        (m_aMutex)
    , m_nSelection(nSelection)
{
    GtkClipboard* clipboard = gtk_clipboard_get(m_nSelection);
    m_nOwnerChangedSignalId = g_signal_connect(clipboard, "owner-change",
                                               G_CALLBACK(handle_owner_change), this);
    m_pOwner = CLIPBOARD_OWNER(g_object_new(CLIPBOARD_OWNER_OBJECT, nullptr));
    m_pOwner->m_pThis = this;
}

void VclGtkClipboard::flushClipboard()
  throw (RuntimeException, std::exception)
{
    SolarMutexGuard aGuard;

    if (GDK_SELECTION_CLIPBOARD != m_nSelection)
        return;

    GtkClipboard* clipboard = gtk_clipboard_get(m_nSelection);
    gtk_clipboard_store(clipboard);
}

VclGtkClipboard::~VclGtkClipboard()
{
    GtkClipboard* clipboard = gtk_clipboard_get(m_nSelection);
    g_signal_handler_disconnect(clipboard, m_nOwnerChangedSignalId);
    g_object_unref(m_pOwner);
    ClipboardClear(nullptr);
}

std::vector<GtkTargetEntry> VclToGtkHelper::FormatsToGtk(const css::uno::Sequence<css::datatransfer::DataFlavor> &rFormats)
{
    std::vector<GtkTargetEntry> aGtkTargets;

    bool bHaveText(false), bHaveUTF8(false);
    for (int i = 0; i < rFormats.getLength(); ++i)
    {
        const css::datatransfer::DataFlavor& rFlavor = rFormats[i];

        sal_Int32 nIndex(0);
        if (rFlavor.MimeType.getToken(0, ';', nIndex) == "text/plain")
        {
            bHaveText = true;
            OUString aToken(rFlavor.MimeType.getToken(0, ';', nIndex));
            if (aToken == "charset=utf-8")
            {
                bHaveUTF8 = true;
            }
        }
        GtkTargetEntry aEntry(makeGtkTargetEntry(rFlavor));
        aGtkTargets.push_back(aEntry);
    }

    if (bHaveText)
    {
        css::datatransfer::DataFlavor aFlavor;
        aFlavor.DataType = cppu::UnoType<Sequence< sal_Int8 >>::get();
        if (!bHaveUTF8)
        {
            aFlavor.MimeType = "text/plain;charset=utf-8";
            aGtkTargets.push_back(makeGtkTargetEntry(aFlavor));
        }
        aFlavor.MimeType = "UTF8_STRING";
        aGtkTargets.push_back(makeGtkTargetEntry(aFlavor));
        aFlavor.MimeType = "STRING";
        aGtkTargets.push_back(makeGtkTargetEntry(aFlavor));
    }

    return aGtkTargets;
}

void VclGtkClipboard::setContents(
        const Reference< css::datatransfer::XTransferable >& xTrans,
        const Reference< css::datatransfer::clipboard::XClipboardOwner >& xClipboardOwner )
    throw(RuntimeException, std::exception)
{
    osl::ClearableMutexGuard aGuard( m_aMutex );
    Reference< datatransfer::clipboard::XClipboardOwner > xOldOwner( m_aOwner );
    Reference< datatransfer::XTransferable > xOldContents( m_aContents );
    m_aContents = xTrans;
    m_aOwner = xClipboardOwner;

    std::list< Reference< datatransfer::clipboard::XClipboardListener > > aListeners( m_aListeners );
    datatransfer::clipboard::ClipboardEvent aEv;

    if (m_aContents.is())
    {
        css::uno::Sequence<css::datatransfer::DataFlavor> aFormats = xTrans->getTransferDataFlavors();
        std::vector<GtkTargetEntry> aGtkTargets(m_aConversionHelper.FormatsToGtk(aFormats));
        if (!aGtkTargets.empty())
        {
            //if there was a previous gtk_clipboard_set_with_data call then
            //ClipboardClearFunc will be called now
            GtkClipboard* clipboard = gtk_clipboard_get(m_nSelection);
            if(G_OBJECT(m_pOwner) == gtk_clipboard_get_owner(clipboard))
                gtk_clipboard_clear(clipboard);
            //use with_owner with m_pOwner so we can distinguish in handle_owner_change
            //if we have gained or lost ownership of the clipboard
            gtk_clipboard_set_with_owner(clipboard, aGtkTargets.data(), aGtkTargets.size(),
                                        ClipboardGetFunc, ClipboardClearFunc, G_OBJECT(m_pOwner));
            gtk_clipboard_set_can_store(clipboard, aGtkTargets.data(), aGtkTargets.size());
        }

        for (auto &a : m_aGtkTargets)
            g_free(a.target);

        m_aGtkTargets = aGtkTargets;
    }

    aEv.Contents = getContents();

    aGuard.clear();

    if( xOldOwner.is() && xOldOwner != xClipboardOwner )
        xOldOwner->lostOwnership( this, xOldContents );
    for( std::list< Reference< datatransfer::clipboard::XClipboardListener > >::iterator it =
         aListeners.begin(); it != aListeners.end() ; ++it )
    {
        (*it)->changedContents( aEv );
    }
}

OUString VclGtkClipboard::getName() throw( RuntimeException, std::exception )
{
    return (m_nSelection == GDK_SELECTION_CLIPBOARD) ? OUString("CLIPBOARD") : OUString("PRIMARY");
}

sal_Int8 VclGtkClipboard::getRenderingCapabilities() throw( RuntimeException, std::exception )
{
    return 0;
}

void VclGtkClipboard::addClipboardListener( const Reference< datatransfer::clipboard::XClipboardListener >& listener )
    throw( RuntimeException, std::exception )
{
    osl::ClearableMutexGuard aGuard( m_aMutex );

    m_aListeners.push_back( listener );
}

void VclGtkClipboard::removeClipboardListener( const Reference< datatransfer::clipboard::XClipboardListener >& listener )
    throw( RuntimeException, std::exception )
{
    osl::ClearableMutexGuard aGuard( m_aMutex );

    m_aListeners.remove( listener );
}

Reference< XInterface > GtkInstance::CreateClipboard(const Sequence< Any >& arguments)
{
    OUString sel;
    if (arguments.getLength() == 0) {
        sel = "CLIPBOARD";
    } else if (arguments.getLength() != 1 || !(arguments[0] >>= sel)) {
        throw css::lang::IllegalArgumentException(
            "bad GtkInstance::CreateClipboard arguments",
            css::uno::Reference<css::uno::XInterface>(), -1);
    }

    GdkAtom nSelection = (sel == "CLIPBOARD") ? GDK_SELECTION_CLIPBOARD : GDK_SELECTION_PRIMARY;

    return Reference< XInterface >( static_cast<cppu::OWeakObject *>(new VclGtkClipboard(nSelection)) );
}

GtkDropTarget::GtkDropTarget()
    : WeakComponentImplHelper(m_aMutex)
    , m_pFrame(nullptr)
    , m_bActive(false)
    , m_nDefaultActions(0)
{
}

OUString SAL_CALL GtkDropTarget::getImplementationName()
            throw (css::uno::RuntimeException, std::exception)
{
    return OUString("com.sun.star.datatransfer.dnd.VclGtkDropTarget");
}

sal_Bool SAL_CALL GtkDropTarget::supportsService(OUString const & ServiceName)
    throw (css::uno::RuntimeException, std::exception)
{
    return cppu::supportsService(this, ServiceName);
}

css::uno::Sequence<OUString> SAL_CALL GtkDropTarget::getSupportedServiceNames()
    throw (css::uno::RuntimeException, std::exception)
{
    Sequence<OUString> aRet { "com.sun.star.datatransfer.dnd.GtkDropTarget" };
    return aRet;
}

GtkDropTarget::~GtkDropTarget()
{
    if (m_pFrame)
        m_pFrame->deregisterDropTarget(this);
}

void GtkDropTarget::deinitialize()
{
    m_pFrame = nullptr;
    m_bActive = false;
}

void GtkDropTarget::initialize(const Sequence<Any>& rArguments) throw( Exception, std::exception )
{
    if (rArguments.getLength() < 2)
    {
        throw RuntimeException("DropTarget::initialize: Cannot install window event handler",
                               static_cast<OWeakObject*>(this));
    }

    sal_Size nFrame = 0;
    rArguments.getConstArray()[1] >>= nFrame;

    if (!nFrame)
    {
        throw RuntimeException("DropTarget::initialize: missing SalFrame",
                               static_cast<OWeakObject*>(this));
    }

    m_pFrame = reinterpret_cast<GtkSalFrame*>(nFrame);
    m_pFrame->registerDropTarget(this);
    m_bActive = true;
}

void GtkDropTarget::addDropTargetListener( const Reference< css::datatransfer::dnd::XDropTargetListener >& xListener) throw(std::exception)
{
    ::osl::Guard< ::osl::Mutex > aGuard( m_aMutex );

    m_aListeners.push_back( xListener );
}

void GtkDropTarget::removeDropTargetListener( const Reference< css::datatransfer::dnd::XDropTargetListener >& xListener) throw(std::exception)
{
    ::osl::Guard< ::osl::Mutex > aGuard( m_aMutex );

    m_aListeners.remove( xListener );
}

void GtkDropTarget::fire_drop(const css::datatransfer::dnd::DropTargetDropEvent& dtde)
{
    osl::ClearableGuard<osl::Mutex> aGuard( m_aMutex );
    std::list<css::uno::Reference<css::datatransfer::dnd::XDropTargetListener>> aListeners(m_aListeners);
    aGuard.clear();

    for (auto it = aListeners.begin(); it != aListeners.end(); ++it)
    {
        (*it)->drop( dtde );
    }
}

void GtkDropTarget::fire_dragEnter(const css::datatransfer::dnd::DropTargetDragEnterEvent& dtde)
{
    osl::ClearableGuard< ::osl::Mutex > aGuard( m_aMutex );
    std::list<css::uno::Reference<css::datatransfer::dnd::XDropTargetListener>> aListeners(m_aListeners);
    aGuard.clear();

    for (auto it = aListeners.begin(); it != aListeners.end(); ++it)
    {
        (*it)->dragEnter( dtde );
    }
}

void GtkDropTarget::fire_dragOver(const css::datatransfer::dnd::DropTargetDragEvent& dtde)
{
    osl::ClearableGuard< ::osl::Mutex > aGuard( m_aMutex );
    std::list<css::uno::Reference<css::datatransfer::dnd::XDropTargetListener>> aListeners(m_aListeners);
    aGuard.clear();

    for (auto it = aListeners.begin(); it != aListeners.end(); ++it)
    {
        (*it)->dragOver( dtde );
    }
}

void GtkDropTarget::fire_dragExit(const css::datatransfer::dnd::DropTargetEvent& dte)
{
    osl::ClearableGuard< ::osl::Mutex > aGuard( m_aMutex );
    std::list<css::uno::Reference<css::datatransfer::dnd::XDropTargetListener>> aListeners(m_aListeners);
    aGuard.clear();

    for (auto it = aListeners.begin(); it != aListeners.end(); ++it)
    {
        (*it)->dragExit( dte );
    }
}

sal_Bool GtkDropTarget::isActive() throw(std::exception)
{
    return m_bActive;
}

void GtkDropTarget::setActive(sal_Bool bActive) throw(std::exception)
{
    m_bActive = bActive;
}

sal_Int8 GtkDropTarget::getDefaultActions() throw(std::exception)
{
    return m_nDefaultActions;
}

void GtkDropTarget::setDefaultActions(sal_Int8 nDefaultActions) throw(std::exception)
{
    m_nDefaultActions = nDefaultActions;
}

Reference< XInterface > GtkInstance::CreateDropTarget()
{
    return Reference< XInterface >( static_cast<cppu::OWeakObject *>(new GtkDropTarget()) );
}

GtkDragSource::~GtkDragSource()
{
    if (m_pFrame)
        m_pFrame->deregisterDragSource(this);

    if (GtkDragSource::g_ActiveDragSource == this)
    {
        SAL_WARN( "vcl.gtk", "dragEnd should have been called on GtkDragSource before dtor");
        GtkDragSource::g_ActiveDragSource = nullptr;
    }
}

void GtkDragSource::deinitialize()
{
    m_pFrame = nullptr;
}

sal_Bool GtkDragSource::isDragImageSupported() throw(std::exception)
{
    return true;
}

sal_Int32 GtkDragSource::getDefaultCursor( sal_Int8 ) throw(std::exception)
{
    return 0;
}

void GtkDragSource::initialize(const css::uno::Sequence<css::uno::Any >& rArguments) throw(Exception, std::exception)
{
    if (rArguments.getLength() < 2)
    {
        throw RuntimeException("DragSource::initialize: Cannot install window event handler",
                               static_cast<OWeakObject*>(this));
    }

    sal_Size nFrame = 0;
    rArguments.getConstArray()[1] >>= nFrame;

    if (!nFrame)
    {
        throw RuntimeException("DragSource::initialize: missing SalFrame",
                               static_cast<OWeakObject*>(this));
    }

    m_pFrame = reinterpret_cast<GtkSalFrame*>(nFrame);
    m_pFrame->registerDragSource(this);
}

OUString SAL_CALL GtkDragSource::getImplementationName()
    throw (css::uno::RuntimeException, std::exception)
{
    return OUString("com.sun.star.datatransfer.dnd.VclGtkDragSource");
}

sal_Bool SAL_CALL GtkDragSource::supportsService(OUString const & ServiceName)
    throw (css::uno::RuntimeException, std::exception)
{
    return cppu::supportsService(this, ServiceName);
}

css::uno::Sequence<OUString> SAL_CALL GtkDragSource::getSupportedServiceNames()
    throw (css::uno::RuntimeException, std::exception)
{
    Sequence<OUString> aRet { "com.sun.star.datatransfer.dnd.GtkDragSource" };
    return aRet;
}

Reference< XInterface > GtkInstance::CreateDragSource()
{
    return Reference< XInterface >( static_cast<cppu::OWeakObject *>(new GtkDragSource()) );
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
