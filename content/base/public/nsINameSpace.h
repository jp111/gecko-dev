/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Communicator client code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef nsINameSpace_h___
#define nsINameSpace_h___

#include "nsISupports.h"

class nsIAtom;

#define NS_INAMESPACE_IID \
  { 0x72022492, 0x0fdf, 0x11d9, \
    { 0xa3, 0x76, 0x00, 0x0a, 0x95, 0xdc, 0x23, 0x4c } }

/**
 * A nsINameSpace registers the NameSpace URI with the NameSpaceManager
 * (creating or finding an ID), and manages the relationship between
 * the NameSpace ID and the (optional) Prefix.
 *
 * New NameSpaces are created as a child of an existing NameSpace. Searches
 * for NameSpaces based on prefix search up the chain of nested NameSpaces
 *
 * Each NameSpace keeps a live reference on its parent.
 *
 */
class nsINameSpace : public nsISupports {
public:
  NS_DEFINE_STATIC_IID_ACCESSOR(NS_INAMESPACE_IID)

  // Get data of this name space
  NS_IMETHOD GetNameSpaceID(PRInt32* aID) const = 0;

  // Find name space within self and parents (not children)
  NS_IMETHOD FindNameSpace(nsIAtom* aPrefix, nsINameSpace** aNameSpace) const = 0;
  NS_IMETHOD FindNameSpaceID(nsIAtom* aPrefix, PRInt32* aNameSpaceID) const = 0;
  NS_IMETHOD FindNameSpacePrefix(PRInt32 aNameSpaceID, nsIAtom** aPrefix) const = 0;

  // Create new child name space
  NS_IMETHOD CreateChildNameSpace(nsIAtom* aPrefix, 
                                  const nsAString& aURI,
                                  nsINameSpace** aChildNameSpace) = 0;
};

#endif // nsINameSpace_h___
