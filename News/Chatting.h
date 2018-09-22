#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Chatting.h"

// Chatting 대화 상자입니다.

class Chatting : public CDialogEx
{
	DECLARE_DYNAMIC(Chatting)

public:
	Chatting(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Chatting();
	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
