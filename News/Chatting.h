#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Chatting.h"

// Chatting ��ȭ �����Դϴ�.

class Chatting : public CDialogEx
{
	DECLARE_DYNAMIC(Chatting)

public:
	Chatting(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Chatting();
	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	CListCtrl m_List;
	CListBox m_List1;
	
	afx_msg void OnBnClickedButton2();
	CStatic m_imgBg;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
