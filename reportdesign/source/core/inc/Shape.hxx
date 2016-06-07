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
#ifndef INCLUDED_REPORTDESIGN_SOURCE_CORE_INC_SHAPE_HXX
#define INCLUDED_REPORTDESIGN_SOURCE_CORE_INC_SHAPE_HXX

#include <cppuhelper/propertysetmixin.hxx>
#include <com/sun/star/report/XShape.hpp>
#include "ReportControlModel.hxx"
#include <cppuhelper/compbase.hxx>
#include <comphelper/broadcasthelper.hxx>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include "ReportHelperDefines.hxx"
#include <comphelper/propagg.hxx>
#include <memory>

namespace reportdesign
{
    typedef ::cppu::PropertySetMixin<        css::report::XShape > ShapePropertySet;
    typedef ::cppu::WeakComponentImplHelper<    css::report::XShape
                                                ,css::lang::XServiceInfo > ShapeBase;

    /** \class OShape Defines the implementation of a \interface com:::sun::star::report::XShape
     * \ingroup reportdesign_api
     *
     */
    class OShape :  public comphelper::OBaseMutex,
                    public ShapeBase,
                    public ShapePropertySet
    {
        friend class OShapeHelper;
        ::std::unique_ptr< ::comphelper::OPropertyArrayAggregationHelper> m_pAggHelper;
        OReportControlModel                                             m_aProps;
        css::drawing::HomogenMatrix3                                    m_Transformation;
        sal_Int32                                                       m_nZOrder;
        bool                                                            m_bOpaque;

        OUString                                                        m_sServiceName;
        OUString                                                        m_CustomShapeEngine;
        OUString                                                        m_CustomShapeData;
        css::uno::Sequence< css::beans::PropertyValue >                 m_CustomShapeGeometry;

    private:
        OShape(const OShape&) = delete;
        OShape& operator=(const OShape&) = delete;

        template <typename T> void set(  const OUString& _sProperty
                                        ,const T& Value
                                        ,T& _member)
        {
            BoundListeners l;
            {
                ::osl::MutexGuard aGuard(m_aMutex);
                prepareSet(_sProperty, css::uno::makeAny(_member), css::uno::makeAny(Value), &l);
                _member = Value;
            }
            l.notify();
        }
        void set(  const OUString& _sProperty
                  ,bool Value
                  ,bool& _member)
        {
            BoundListeners l;
            {
                ::osl::MutexGuard aGuard(m_aMutex);
                prepareSet(_sProperty, css::uno::makeAny(_member), css::uno::makeAny(Value), &l);
                _member = Value;
            }
            l.notify();
        }
        cppu::IPropertyArrayHelper& getInfoHelper();
    protected:
        virtual ~OShape();
    public:
        explicit OShape(css::uno::Reference< css::uno::XComponentContext > const & _xContext);
        explicit OShape(css::uno::Reference< css::uno::XComponentContext > const & _xContext
                        ,const css::uno::Reference< css::lang::XMultiServiceFactory > & _xFactory
                        ,css::uno::Reference< css::drawing::XShape >& _xShape
                        ,const OUString& _sServiceName);

        DECLARE_XINTERFACE( )
        // css::lang::XServiceInfo
        virtual sal_Bool SAL_CALL supportsService( const OUString& ServiceName ) throw (css::uno::RuntimeException, std::exception) override;
        virtual OUString SAL_CALL getImplementationName(  ) throw(css::uno::RuntimeException, std::exception) override;
        virtual css::uno::Sequence< OUString > SAL_CALL getSupportedServiceNames(  ) throw(css::uno::RuntimeException, std::exception) override;

        static css::uno::Sequence< OUString > getSupportedServiceNames_Static() throw( css::uno::RuntimeException );
        static OUString getImplementationName_Static() throw( css::uno::RuntimeException );
        static css::uno::Reference< css::uno::XInterface > SAL_CALL
            create(css::uno::Reference< css::uno::XComponentContext > const & xContext);
        // css::beans::XPropertySet
        virtual css::uno::Reference< css::beans::XPropertySetInfo > SAL_CALL getPropertySetInfo(  ) throw(css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL setPropertyValue( const OUString& aPropertyName, const css::uno::Any& aValue ) throw (css::beans::UnknownPropertyException, css::beans::PropertyVetoException, css::lang::IllegalArgumentException, css::lang::WrappedTargetException, css::uno::RuntimeException, std::exception) override;
        virtual css::uno::Any SAL_CALL getPropertyValue( const OUString& PropertyName ) throw (css::beans::UnknownPropertyException, css::lang::WrappedTargetException, css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL addPropertyChangeListener( const OUString& aPropertyName, const css::uno::Reference< css::beans::XPropertyChangeListener >& xListener ) throw (css::beans::UnknownPropertyException, css::lang::WrappedTargetException, css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL removePropertyChangeListener( const OUString& aPropertyName, const css::uno::Reference< css::beans::XPropertyChangeListener >& aListener ) throw (css::beans::UnknownPropertyException, css::lang::WrappedTargetException, css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL addVetoableChangeListener( const OUString& PropertyName, const css::uno::Reference< css::beans::XVetoableChangeListener >& aListener ) throw (css::beans::UnknownPropertyException, css::lang::WrappedTargetException, css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL removeVetoableChangeListener( const OUString& PropertyName, const css::uno::Reference< css::beans::XVetoableChangeListener >& aListener ) throw (css::beans::UnknownPropertyException, css::lang::WrappedTargetException, css::uno::RuntimeException, std::exception) override;

        // XReportComponent
        REPORTCOMPONENT_HEADER()

        // XShape
        SHAPE_HEADER()

        virtual OUString SAL_CALL getCustomShapeEngine() throw (css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL setCustomShapeEngine( const OUString& _customshapeengine ) throw (css::uno::RuntimeException, std::exception) override;
        virtual OUString SAL_CALL getCustomShapeData() throw (css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL setCustomShapeData( const OUString& _customshapedata ) throw (css::uno::RuntimeException, std::exception) override;
        virtual css::uno::Sequence< css::beans::PropertyValue > SAL_CALL getCustomShapeGeometry() throw (css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL setCustomShapeGeometry( const css::uno::Sequence< css::beans::PropertyValue >& _customshapegeometry ) throw (css::uno::RuntimeException, std::exception) override;

        virtual sal_Bool SAL_CALL getOpaque() throw (css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL setOpaque( sal_Bool _opaque ) throw (css::uno::RuntimeException, std::exception) override;

        // XShapeDescriptor
        virtual OUString SAL_CALL getShapeType(  ) throw (css::uno::RuntimeException, std::exception) override;

        // XReportControlModel
        REPORTCONTROLMODEL_HEADER()

        // XReportControlFormat
        REPORTCONTROLFORMAT_HEADER()
        // XShape
        virtual ::sal_Int32 SAL_CALL getZOrder() throw (css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL setZOrder( ::sal_Int32 _zorder ) throw (css::uno::RuntimeException, std::exception) override;
        virtual css::drawing::HomogenMatrix3 SAL_CALL getTransformation() throw (css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL setTransformation( const css::drawing::HomogenMatrix3& _transformation ) throw (css::uno::RuntimeException, std::exception) override;

        // XCloneable
        virtual css::uno::Reference< css::util::XCloneable > SAL_CALL createClone(  ) throw (css::uno::RuntimeException, std::exception) override;

        // XComponent
        virtual void SAL_CALL dispose() throw(css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL addEventListener(const css::uno::Reference< css::lang::XEventListener > & aListener) throw(css::uno::RuntimeException, std::exception) override
        {
            cppu::WeakComponentImplHelperBase::addEventListener(aListener);
        }
        virtual void SAL_CALL removeEventListener(const css::uno::Reference< css::lang::XEventListener > & aListener) throw(css::uno::RuntimeException, std::exception) override
        {
            cppu::WeakComponentImplHelperBase::removeEventListener(aListener);
        }

        // XChild
        virtual css::uno::Reference< css::uno::XInterface > SAL_CALL getParent(  ) throw (css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL setParent( const css::uno::Reference< css::uno::XInterface >& Parent ) throw (css::lang::NoSupportException, css::uno::RuntimeException, std::exception) override;

        // XContainer
        virtual void SAL_CALL addContainerListener( const css::uno::Reference< css::container::XContainerListener >& xListener ) throw (css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL removeContainerListener( const css::uno::Reference< css::container::XContainerListener >& xListener ) throw (css::uno::RuntimeException, std::exception) override;

        // XElementAccess
        virtual css::uno::Type SAL_CALL getElementType(  ) throw (css::uno::RuntimeException, std::exception) override;
        virtual sal_Bool SAL_CALL hasElements(  ) throw (css::uno::RuntimeException, std::exception) override;

        // XIndexReplace
        virtual void SAL_CALL replaceByIndex( ::sal_Int32 Index, const css::uno::Any& Element ) throw (css::lang::IllegalArgumentException, css::lang::IndexOutOfBoundsException, css::lang::WrappedTargetException, css::uno::RuntimeException, std::exception) override;

        // XIndexContainer
        virtual void SAL_CALL insertByIndex( ::sal_Int32 Index, const css::uno::Any& Element ) throw (css::lang::IllegalArgumentException, css::lang::IndexOutOfBoundsException, css::lang::WrappedTargetException, css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL removeByIndex( ::sal_Int32 Index ) throw (css::lang::IndexOutOfBoundsException, css::lang::WrappedTargetException, css::uno::RuntimeException, std::exception) override;

        // XIndexAccess
        virtual ::sal_Int32 SAL_CALL getCount(  ) throw (css::uno::RuntimeException, std::exception) override;
        virtual css::uno::Any SAL_CALL getByIndex( ::sal_Int32 Index ) throw (css::lang::IndexOutOfBoundsException, css::lang::WrappedTargetException, css::uno::RuntimeException, std::exception) override;
    };
}
#endif // INCLUDED_REPORTDESIGN_SOURCE_CORE_INC_SHAPE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
