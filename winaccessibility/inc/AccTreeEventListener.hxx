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

#ifndef INCLUDED_WINACCESSIBILITY_INC_ACCTREEEVENTLISTENER_HXX
#define INCLUDED_WINACCESSIBILITY_INC_ACCTREEEVENTLISTENER_HXX

#include <stdio.h>
#include "AccDescendantManagerEventListener.hxx"
#include <com/sun/star/accessibility/XAccessibleEventListener.hpp>
#include <com/sun/star/accessibility/XAccessible.hpp>


/**
 * AccTreeEventListener is inherited from AccDescendantManagerEventListener. It handles
 * the evnets generated by tree controls. The accessible role is: TREE.
 * It defines the procedure of specific event handling related with tree components
 * and provides the detailed support for some related methods.
 */
class AccTreeEventListener: public AccDescendantManagerEventListener
{
public:
    AccTreeEventListener(css::accessibility::XAccessible* pAcc, AccObjectManagerAgent* Agent);
    virtual ~AccTreeEventListener();

    // XAccessibleEventListener
    virtual void SAL_CALL notifyEvent( const css::accessibility::AccessibleEventObject& aEvent ) throw (css::uno::RuntimeException);

    //for active descendant changed event
    virtual void HandleActiveDescendantChangedEvent(
            css::uno::Any oldValue, css::uno::Any newValue);
};

#endif // INCLUDED_WINACCESSIBILITY_INC_ACCTREEEVENTLISTENER_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
