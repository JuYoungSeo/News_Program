#pragma once
#include "afxwin.h"


// Join_member 대화 상자입니다.

class Join_member : public CDialogEx
{
	DECLARE_DYNAMIC(Join_member)

public:
	Join_member(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Join_member();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit Join_Name;
	CEdit Join_ID;
	CEdit Join_PASSWORD;
	CEdit Join_PASSWORD_OK;
	CEdit Join_NICKNAME;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	CStatic m_imgBg;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
