#if !defined(AFX_HMLISTCTRLEXT_H__516D59C3_2F02_47C6_8F4A_D6A78DCDD44A__INCLUDED_)
#define AFX_HMLISTCTRLEXT_H__516D59C3_2F02_47C6_8F4A_D6A78DCDD44A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HMListCtrlExt.h : header file
//

#include <afxtempl.h>

#include "InPlaceEdit.h"
#include "InPlaceComboBox.h"
#define EDITDISABLE_NONE	0
#define EDITDISABLE_ROWS	1
#define EDITDISABLE_COLS	2
#define EDITDISABLE_ROWCOL	3

#define INPLACECTRL_EDIT	4
#define INPLACECTRL_COMBO	5
#define INPLACECTRL_EDIT_COMBO	6

#define EDITDISABLE_ROWS_ARRAY	7
#define EDITDISABLE_COLS_ARRAY	8

#define COMBODATASTATE_SINGLE 9
#define COMBODATASTATE_MULTI  10

/////////////////////////////////////////////////////////////////////////////
// CHMListCtrlExt window

typedef struct _LISTROWCOLOR
{
	int			s_nRow;
	COLORREF	s_Color;
} ListRowColor, *pListRowColor;

class AFX_EXT_CLASS CHMListCtrlExt : public CListCtrl
{
// Construction
public:
	CHMListCtrlExt();
	virtual ~CHMListCtrlExt();

// Attributes
public:

// Operations
public:
	void SetComboCtrlCols(CString strCols,int nLength);
	void SetEditCtrlCols(CString strCols,int nLength);
	void SetComboData(char *pData[],int nState,int nLength);
	void SetComboData(CStringList *pList, int nState);
	void EditDisableRows(CString strRows,int nLength);
	void EditDisableCols(CString strCols,int nLength);
	BOOL GetEnableSortList();
	void SetEnableSortList(BOOL nEnable);
	void SortListCtrl(int nCol);
	void InitListHeader(char *colList[],int *widthList,int nLength, int nHeight);
	void SetInPlaceCtrl(int nCtrl);
	void SetDefaultEditText(CString strInitText);
	void SetEditDisableState(int nState);
	int GetEditDisableCols();
	int GetEditDisableRows();
	int GetEditDisableState();
	void EditDisableRowCol(int nRow,int nCol);
	void EditDisableCols(int nCols);
	void EditDisableRows(int nRows);
	void SetColNum(int nColNum);
	void AddBlankItem();
	CImageList* SetImageList(CImageList* pImageList, int nImageListType);

	void InsertListItem(int nRow, int nCol, LPSTR lpString);
	void InsertListItem(int nRow, int nCol, int nImageIdx, LPSTR lpString);
	void InsertListItem(int nRow, int nCol, int nImageIdx);

	void InsertListItemEx(int nRow, int nCol, const CString& strString);
	void InsertListItemEx(int nRow, int nCol, int nValue);
	void InsertListItemEx(int nRow, int nCol, double dValue, int nRight = 3);

	void SetTextColor(int nRow, COLORREF clrText);
	void SetBKColor(int nRow, COLORREF clrBK);
	void ReleaseTextColor(int nRow);
	void ReleaseBKColor(int nRow);
	void ResetTextColor();
	void ResetBKColor();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHMListCtrlExt)
	//}}AFX_VIRTUAL

protected:
	CInPlaceEdit *m_pEdit;
	CInPlaceComboBox *m_pComboBox;
	int m_nInPlaceCtrl;
	int m_nColNum;
	int m_nEditDisableState;
	int m_nDisableCol;
	int m_nDisableRow;
	BOOL m_bSortOrder;
	CString m_strInitEditText;
	BOOL m_bEnableSortList;
	int *m_pEditDisableCols;
	int *m_pEditDisableRows;
	// Generated message map functions
protected:
	int m_nComboCtrlLength;
	int m_nEditCtrlLength;
	int *m_pComboCtrlCols;
	int *m_pEditCtrlCols;
	CStringList *m_pComboData;
	int m_nLength;
	int m_nComboDataState;
	BOOL m_bSetImageList;

// Implementation
public:
	CList<pListRowColor, pListRowColor>	m_ListColorText;
	CList<pListRowColor, pListRowColor>	m_ListColorBk;

	// Generated message map functions
protected:
	//{{AFX_MSG(CHMListCtrlExt)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HMLISTCTRLEXT_H__516D59C3_2F02_47C6_8F4A_D6A78DCDD44A__INCLUDED_)
