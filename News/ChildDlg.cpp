// ChildDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "News.h"
#include "ChildDlg.h"
#include "afxdialogex.h"
#include "Board.h"
#include "Board_comment.h"
#include <mysql.h>
#include <Winsock2.h>

#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "WS2_32.lib")

#define CON_IP "114.201.35.170"
#define DB_USER "root"
#define DB_PASS "cksals"
#define DB_NAME "newss"
#define DB_TABLE "news"

CString Board_title;
CString ID5;
CString Comment;
CString URL;
char Query111[256];
int Query_Status111;

// CChildDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CChildDlg, CDialogEx)

CChildDlg::CChildDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{
}

CChildDlg::~CChildDlg()
{
}

void CChildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	SetDlgItemText(IDC_News, Comment);

	DDX_Control(pDX, IDC_EDIT1, URL_info);
	DDX_Control(pDX, IDC_Picture, m_imgBg);
}

//내용을 받아오기 위해 미리 정의해논 함수
void CChildDlg::SetMainListPtr(CString parm_list,CString ID2,CString Comment1)
{
	ID5 = ID2;
	Board_title = parm_list;
	Comment=Comment1;
}

BEGIN_MESSAGE_MAP(CChildDlg, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON2, &CChildDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CHECK2, &CChildDlg::OnBnClickedCheck2)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CChildDlg 메시지 처리기입니다.



void CChildDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Board_comment dlg;
	dlg.SetMainListPtr(Board_title,ID5);
	dlg.DoModal();
}


BOOL CChildDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	MYSQL *Connection;
	MYSQL Connect;
	MYSQL_RES *Sql_Result;
	MYSQL_ROW Sql_Row;
	MYSQL_RES *Sql_Resulttitle;
	MYSQL_ROW Sql_Rowtitle;

	int ROW;
	char* title[5120];
	char* context_news[10000];
	char* search_number[1000];
	char* good_number[1000];
	CString seq_string;
	int order = 1;
	CString Search;

	mysql_init(&Connect);
	Connection = mysql_real_connect(&Connect, CON_IP, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (Connection == NULL)
	{
		MessageBox(NULL, _T("DB 접속에 실패했습니다.\n응용 프로그램을 시작할 수 없습니다."), MB_OK);
	}
	mysql_set_character_set(&Connect, "euckr");

	sprintf_s(Query111, "select * from %s where %s like '%s'", DB_TABLE, "title", Board_title);

	//성공여부를 Query_Status1변수에 저장
	Query_Status111 = mysql_query(Connection, Query111);

	//Query문에서 찾은 결과(값)를 한꺼번에 받아오는 코드
	Sql_Result = mysql_store_result(Connection);
	Sql_Rowtitle = mysql_fetch_row(Sql_Result);

	CString number= Sql_Rowtitle[3];
	CString number2= Sql_Rowtitle[2];
	URL= Sql_Rowtitle[5];
	int number1=_ttoi(number);
	number1++;
	number.Format(_T("%d"), number1);

	sprintf_s(Query111, "UPDATE news SET search_number = '%s' where title='%s'",number, Board_title);

	//성공여부를 Query_Status1변수에 저장
	Query_Status111 = mysql_query(Connection, Query111);
	//AfxMessageBox(_T(mysql_error(Connection)));
	//Query문에서 찾은 결과(값)를 한꺼번에 받아오는 코드
	SetDlgItemText(IDC_EDIT1, URL);

	SetDlgItemText(IDC_EDIT2, number2);

	HBITMAP hBit = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7));
	m_imgBg.SetBitmap(hBit);
	CRect rt;
	GetClientRect(&rt);
	m_imgBg.SetWindowPos(NULL, 0, 0, rt.Width(), rt.Height(), SWP_SHOWWINDOW);
	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CChildDlg::OnBnClickedCheck2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	MYSQL *Connection;
	MYSQL Connect;
	MYSQL_RES *Sql_Result;
	MYSQL_ROW Sql_Row;
	MYSQL_RES *Sql_Resulttitle;
	MYSQL_ROW Sql_Rowtitle;

	int ROW;
	char* title[5120];
	char* context_news[10000];
	char* search_number[1000];
	char* good_number[1000];
	CString seq_string;
	int order = 1;
	CString Search;

	mysql_init(&Connect);
	Connection = mysql_real_connect(&Connect, CON_IP, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (Connection == NULL)
	{
		MessageBox(NULL, _T("DB 접속에 실패했습니다.\n응용 프로그램을 시작할 수 없습니다."), MB_OK);
	}
	mysql_set_character_set(&Connect, "euckr");

	sprintf_s(Query111, "select * from %s where %s like '%s'", DB_TABLE, "title", Board_title);

	//성공여부를 Query_Status1변수에 저장
	Query_Status111 = mysql_query(Connection, Query111);

	//Query문에서 찾은 결과(값)를 한꺼번에 받아오는 코드
	Sql_Result = mysql_store_result(Connection);
	Sql_Rowtitle = mysql_fetch_row(Sql_Result);

	CString number = Sql_Rowtitle[2];


	BOOL chk = IsDlgButtonChecked(IDC_CHECK2);

	if (chk == true) {
		int number1 = _ttoi(number);
		number1++;
		number.Format(_T("%d"), number1);

		sprintf_s(Query111, "UPDATE news SET good_number = '%s' where title='%s'", number, Board_title);

		//성공여부를 Query_Status1변수에 저장
		Query_Status111 = mysql_query(Connection, Query111);


	}
	else if (chk == false) {
		int number1 = _ttoi(number);
		number1--;
		number.Format(_T("%d"), number1);

		sprintf_s(Query111, "UPDATE news SET good_number = '%s' where title='%s'", number, Board_title);

		//성공여부를 Query_Status1변수에 저장
		Query_Status111 = mysql_query(Connection, Query111);
	}

	sprintf_s(Query111, "select * from %s where %s like '%s'", DB_TABLE, "title", Board_title);

	//성공여부를 Query_Status1변수에 저장
	Query_Status111 = mysql_query(Connection, Query111);

	//Query문에서 찾은 결과(값)를 한꺼번에 받아오는 코드
	Sql_Result = mysql_store_result(Connection);
	Sql_Rowtitle = mysql_fetch_row(Sql_Result);

	 number = Sql_Rowtitle[2];

	SetDlgItemText(IDC_EDIT2, number);

}


HBRUSH CChildDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		
	}
	}
	return hbr;
}
