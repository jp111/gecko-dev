/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "NPL"); you may not use this file except in
 * compliance with the NPL.  You may obtain a copy of the NPL at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the NPL is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
 * for the specific language governing rights and limitations under the
 * NPL.
 *
 * The Initial Developer of this code under the NPL is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation.  All Rights
 * Reserved.
 */
#ifndef nsTableColFrame_h__
#define nsTableColFrame_h__

#include "nscore.h"
#include "nsContainerFrame.h"
#include "nsTableFrame.h"

class nsVoidArray;
class nsTableCellFrame;

// this is used to index arrays of widths in nsColFrame and to group important widths
// for calculations. It is important that the order: min, desired, fixed be maintained
// for each category (con, adj).
// XXX MIN_ADJ, DES_ADJ, PCT_ADJ, DES_PRO can probably go away and be replaced
// by MIN_CON, DES_CON, PCT_CON, DES_CON saving 16 bytes per col frame
#define WIDTH_NOT_SET   -1
#define NUM_WIDTHS       9
#define NUM_MAJOR_WIDTHS 3 // MIN, DES, FIX
#define MIN_CON          0 // minimum width required of the content + padding
#define DES_CON          1 // desired width of the content + padding
#define FIX              2 // fixed width either from the content or cell, col, etc. + padding
#define MIN_ADJ          3 // minimum width + padding due to col spans
#define DES_ADJ          4 // desired width + padding due to col spans
#define FIX_ADJ          5 // fixed width + padding due to col spans
#define PCT              6 // percent width of cell or col 
#define PCT_ADJ          7 // percent width of cell or col from percent colspan
#define MIN_PRO          8 // desired width due to proportional <col>s or cols attribute

enum nsColConstraint {
  eNoConstraint          = 0,
  ePixelConstraint       = 1,      // pixel width 
  ePercentConstraint     = 2,      // percent width
  eProportionConstraint  = 3,      // 1*, 2*, etc. cols attribute assigns 1*
  e0ProportionConstraint = 4       // 0*, means to force to min width
};

class nsTableColFrame : public nsFrame {
public:

  enum {eWIDTH_SOURCE_NONE          =0,   // no cell has contributed to the width style
        eWIDTH_SOURCE_CELL          =1,   // a cell specified a width
        eWIDTH_SOURCE_CELL_WITH_SPAN=2    // a cell implicitly specified a width via colspan
  };

  void InitColFrame(PRInt32 aColIndex);

  /** instantiate a new instance of nsTableColFrame.
    * @param aResult    the new object is returned in this out-param
    * @param aContent   the table object to map
    * @param aParent    the parent of the new frame
    *
    * @return  NS_OK if the frame was properly allocated, otherwise an error code
    */
  friend nsresult 
  NS_NewTableColFrame(nsIFrame** aResult);

  NS_IMETHOD Paint(nsIPresContext& aPresContext,
                   nsIRenderingContext& aRenderingContext,
                   const nsRect& aDirtyRect,
                   nsFramePaintLayer aWhichLayer);

  NS_IMETHOD Reflow(nsIPresContext&          aPresContext,
                    nsHTMLReflowMetrics&     aDesiredSize,
                    const nsHTMLReflowState& aReflowState,
                    nsReflowStatus&          aStatus);

  NS_IMETHOD GetFrameName(nsString& aResult) const;
#ifdef DEBUG
  NS_IMETHOD SizeOf(nsISizeOfHandler* aSizer, PRUint32* aResult) const;
#endif

  /** return the index of the column the col represents.  always >= 0 */
  virtual PRInt32 GetColumnIndex ();

  /** return the number of the columns the col represents.  always >= 0 */
  virtual PRInt32 GetSpan ();

  /** set the index of the column this content object represents.  must be >= 0 */
  virtual void SetColumnIndex (int aColIndex);

  /** convenience method, calls into cellmap */
  nsVoidArray * GetCells();

  nscoord GetWidth(PRUint32 aWidthType);
  void    SetWidth(PRUint32 aWidthType,
                   nscoord  aWidth);
  nscoord GetMinWidth();
  nscoord GetDesWidth();
  nscoord GetFixWidth();
  nscoord GetPctWidth();

  void            SetConstraint(nsColConstraint aConstraint);
  nsColConstraint GetConstraint() const;

  void              SetConstrainingCell(nsTableCellFrame* aCellFrame);
  nsTableCellFrame* GetConstrainingCell() const;

  /** convenience method, calls into cellmap */
  PRInt32 Count() const;

  /** Return true if this col was constructed implicitly due to cells needing a col.
    * Return false if this col was constructed due to content having display type of table-col
    */
  PRBool IsAnonymous();
  void SetIsAnonymous(PRBool aValue);

  void ResetSizingInfo();

  void Dump(PRInt32 aIndent);

protected:

  nsTableColFrame();
  ~nsTableColFrame();

  /** the starting index of the column (starting at 0) that this col object represents */
  PRInt32  mColIndex;

  PRBool  mIsAnonymous;

  // Widths including MIN_CON, DES_CON, FIX_CON, MIN_ADJ, DES_ADJ, FIX_ADJ, PCT, PCT_ADJ, MIN_PRO
  nscoord mWidths[NUM_WIDTHS];
  nscoord mProportion; // proportion for porportional width col
  nsColConstraint mConstraint;
  nsTableCellFrame* mConstrainingCell;
};


inline void nsTableColFrame::InitColFrame(PRInt32 aColIndex)
{
  NS_ASSERTION(0<=aColIndex, "bad col index param");
  mColIndex = aColIndex;
}

inline PRInt32 nsTableColFrame::GetColumnIndex()
{ return mColIndex; }

inline void nsTableColFrame::SetColumnIndex (int aColIndex)
{  mColIndex = aColIndex;}

inline nsColConstraint nsTableColFrame::GetConstraint() const
{ return mConstraint; }

inline void nsTableColFrame::SetConstraint(nsColConstraint aConstraint)
{  mConstraint = aConstraint;}

inline PRBool nsTableColFrame::IsAnonymous()
{ return mIsAnonymous; }

inline void nsTableColFrame::SetIsAnonymous(PRBool aIsAnonymous)
{ mIsAnonymous = aIsAnonymous; }

inline void nsTableColFrame::SetConstrainingCell(nsTableCellFrame* aCellFrame) 
{ mConstrainingCell = aCellFrame; }

inline nsTableCellFrame* nsTableColFrame::GetConstrainingCell() const 
{ return mConstrainingCell; }

#endif

