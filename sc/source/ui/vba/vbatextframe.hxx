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
#ifndef INCLUDED_SC_SOURCE_UI_VBA_VBATEXTFRAME_HXX
#define INCLUDED_SC_SOURCE_UI_VBA_VBATEXTFRAME_HXX
#include <cppuhelper/implbase.hxx>
#include <ooo/vba/excel/XTextFrame.hpp>
#include <vbahelper/vbahelperinterface.hxx>
#include <vbahelper/vbatextframe.hxx>

//typedef InheritedHelperInterfaceWeakImpl< ov::excel::XTextFrame > ScVbaTextFrame_BASE;
typedef cppu::ImplInheritanceHelper< VbaTextFrame, ov::excel::XTextFrame > ScVbaTextFrame_BASE;

class ScVbaTextFrame : public ScVbaTextFrame_BASE
{
public:
    ScVbaTextFrame( css::uno::Sequence< css::uno::Any > const& aArgs, css::uno::Reference< css::uno::XComponentContext > const& xContext ) throw ( css::lang::IllegalArgumentException );
    virtual ~ScVbaTextFrame() {}
    // Methods
    virtual css::uno::Any SAL_CALL Characters(  ) throw (css::uno::RuntimeException, std::exception) override;
    // XHelperInterface
    virtual OUString getServiceImplName() override;
    virtual css::uno::Sequence<OUString> getServiceNames() override;

};

#endif // INCLUDED_SC_SOURCE_UI_VBA_VBATEXTFRAME_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
