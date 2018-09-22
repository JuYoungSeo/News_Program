#pragma once
#include "afxcmn.h"
#include "ChildDlg.h"
#include "afxwin.h"

// Board ��ȭ �����Դϴ�.

class Board : public CDialog
{
	DECLARE_DYNAMIC(Board)

public:
	Board(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	void SetMainListPtr(CString parm_list);
	virtual ~Board();
	CChildDlg *ChildDlg;
	CString ID;
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnItemchangedList3(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listinfo;
//	virtual BOOL OnInitDialog();
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedsearchbutton();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeFindnews();
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_combo;
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_imgBg;
};
