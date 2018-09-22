#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Board_comment 대화 상자입니다.

class Board_comment : public CDialogEx
{
	DECLARE_DYNAMIC(Board_comment)

public:
	void SetMainListPtr(CString parm_list, CString ID2);
	Board_comment(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Board_comment();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listinfo2;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_imgBg;
};
