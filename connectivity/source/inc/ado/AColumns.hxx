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

#ifndef INCLUDED_CONNECTIVITY_SOURCE_INC_ADO_ACOLUMNS_HXX
#define INCLUDED_CONNECTIVITY_SOURCE_INC_ADO_ACOLUMNS_HXX

#include <connectivity/sdbcx/VCollection.hxx>
#include <com/sun/star/sdbc/XDatabaseMetaData.hpp>
#include <connectivity/sdbcx/IRefreshable.hxx>
#include "ado/Awrapadox.hxx"

namespace connectivity
{
    namespace ado
    {
        class OConnection;
        class OColumns : public sdbcx::OCollection
        {
        protected:
            WpADOColumns    m_aCollection;
            OConnection*    m_pConnection;

            virtual sdbcx::ObjectType createObject(const OUString& _rName);
            virtual void impl_refresh() throw(css::uno::RuntimeException);
            virtual css::uno::Reference< css::beans::XPropertySet > createDescriptor();
            virtual sdbcx::ObjectType appendObject( const OUString& _rForName, const css::uno::Reference< css::beans::XPropertySet >& descriptor );
            virtual void dropObject(sal_Int32 _nPos,const OUString& _sElementName);
        public:
            OColumns(   ::cppu::OWeakObject& _rParent,
                        ::osl::Mutex& _rMutex,
                        const TStringVector &_rVector,
                        const WpADOColumns& _rCollection,
                        sal_Bool _bCase,
                        OConnection* _pConnection) : sdbcx::OCollection(_rParent,_bCase,_rMutex,_rVector)
                        ,m_aCollection(_rCollection)
                        ,m_pConnection(_pConnection)
            {
            }

        };
    }
}
#endif // INCLUDED_CONNECTIVITY_SOURCE_INC_ADO_ACOLUMNS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
