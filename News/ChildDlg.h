#pragma once
#include "afxwin.h"


// CChildDlg ��ȭ �����Դϴ�.

class CChildDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChildDlg)

public:
	CChildDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CChildDlg();
	void CChildDlg::SetMainListPtr(CString parm_list, CString ID2, CString Comment1);
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	CEdit URL_info;
	afx_msg void OnBnClickedCheck2();
	CStatic m_imgBg;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
