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

#ifndef INCLUDED_WINACCESSIBILITY_INC_ACCDESCENDANTMANAGEREVENTLISTENER_HXX
#define INCLUDED_WINACCESSIBILITY_INC_ACCDESCENDANTMANAGEREVENTLISTENER_HXX

#include <stdio.h>
#include "AccComponentEventListener.hxx"
#include <com/sun/star/accessibility/XAccessibleEventListener.hpp>
#include <com/sun/star/accessibility/XAccessible.hpp>

/**
 * AccDescendantManagerEventListener is inherited from AccComponentEventListener. It handles
 * the evnets generated by active descendant controls. They are: TREE, LIST, and TABLE.
 * It defines the procedure of specific event handling related with active descendant components
 * and provides the detailed support for some related methods.
 */
class AccDescendantManagerEventListener: public AccComponentEventListener
{

public:
    AccDescendantManagerEventListener(css::accessibility::XAccessible* pAcc, AccObjectManagerAgent* Agent);
    virtual ~AccDescendantManagerEventListener();

    // XAccessibleEventListener
    virtual void SAL_CALL notifyEvent( const css::accessibility::AccessibleEventObject& aEvent ) throw (css::uno::RuntimeException);

    //for selection changed event
    virtual void HandleSelectionChangedEvent(
            css::uno::Any oldValue, css::uno::Any newValue);

    //for child changed event
    virtual void HandleChildChangedEvent(
            css::uno::Any oldValue, css::uno::Any newValue);

    virtual void HandleChildChangedNoFocusEvent(
            css::uno::Any oldValue, css::uno::Any newValue);

    bool NotifyChildEvent(short nWinEvent,const css::uno::Any &Value);

    virtual void HandleSelectionChangedAddEvent(
            const css::uno::Any &oldValue, const css::uno::Any &newValue);
    virtual void HandleSelectionChangedRemoveEvent(
            const css::uno::Any &oldValue, const css::uno::Any &newValue);
    virtual void HandleSelectionChangedWithinEvent(
            const css::uno::Any &oldValue, const css::uno::Any &newValue);
};

#endif // INCLUDED_WINACCESSIBILITY_INC_ACCDESCENDANTMANAGEREVENTLISTENER_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
