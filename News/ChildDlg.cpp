// ChildDlg.cpp : ���� �����Դϴ�.
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

// CChildDlg ��ȭ �����Դϴ�.

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

//������ �޾ƿ��� ���� �̸� �����س� �Լ�
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


// CChildDlg �޽��� ó�����Դϴ�.



void CChildDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		MessageBox(NULL, _T("DB ���ӿ� �����߽��ϴ�.\n���� ���α׷��� ������ �� �����ϴ�."), MB_OK);
	}
	mysql_set_character_set(&Connect, "euckr");

	sprintf_s(Query111, "select * from %s where %s like '%s'", DB_TABLE, "title", Board_title);

	//�������θ� Query_Status1������ ����
	Query_Status111 = mysql_query(Connection, Query111);

	//Query������ ã�� ���(��)�� �Ѳ����� �޾ƿ��� �ڵ�
	Sql_Result = mysql_store_result(Connection);
	Sql_Rowtitle = mysql_fetch_row(Sql_Result);

	CString number= Sql_Rowtitle[3];
	CString number2= Sql_Rowtitle[2];
	URL= Sql_Rowtitle[5];
	int number1=_ttoi(number);
	number1++;
	number.Format(_T("%d"), number1);

	sprintf_s(Query111, "UPDATE news SET search_number = '%s' where title='%s'",number, Board_title);

	//�������θ� Query_Status1������ ����
	Query_Status111 = mysql_query(Connection, Query111);
	//AfxMessageBox(_T(mysql_error(Connection)));
	//Query������ ã�� ���(��)�� �Ѳ����� �޾ƿ��� �ڵ�
	SetDlgItemText(IDC_EDIT1, URL);

	SetDlgItemText(IDC_EDIT2, number2);

	HBITMAP hBit = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP7));
	m_imgBg.SetBitmap(hBit);
	CRect rt;
	GetClientRect(&rt);
	m_imgBg.SetWindowPos(NULL, 0, 0, rt.Width(), rt.Height(), SWP_SHOWWINDOW);
	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CChildDlg::OnBnClickedCheck2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
		MessageBox(NULL, _T("DB ���ӿ� �����߽��ϴ�.\n���� ���α׷��� ������ �� �����ϴ�."), MB_OK);
	}
	mysql_set_character_set(&Connect, "euckr");

	sprintf_s(Query111, "select * from %s where %s like '%s'", DB_TABLE, "title", Board_title);

	//�������θ� Query_Status1������ ����
	Query_Status111 = mysql_query(Connection, Query111);

	//Query������ ã�� ���(��)�� �Ѳ����� �޾ƿ��� �ڵ�
	Sql_Result = mysql_store_result(Connection);
	Sql_Rowtitle = mysql_fetch_row(Sql_Result);

	CString number = Sql_Rowtitle[2];


	BOOL chk = IsDlgButtonChecked(IDC_CHECK2);

	if (chk == true) {
		int number1 = _ttoi(number);
		number1++;
		number.Format(_T("%d"), number1);

		sprintf_s(Query111, "UPDATE news SET good_number = '%s' where title='%s'", number, Board_title);

		//�������θ� Query_Status1������ ����
		Query_Status111 = mysql_query(Connection, Query111);


	}
	else if (chk == false) {
		int number1 = _ttoi(number);
		number1--;
		number.Format(_T("%d"), number1);

		sprintf_s(Query111, "UPDATE news SET good_number = '%s' where title='%s'", number, Board_title);

		//�������θ� Query_Status1������ ����
		Query_Status111 = mysql_query(Connection, Query111);
	}

	sprintf_s(Query111, "select * from %s where %s like '%s'", DB_TABLE, "title", Board_title);

	//�������θ� Query_Status1������ ����
	Query_Status111 = mysql_query(Connection, Query111);

	//Query������ ã�� ���(��)�� �Ѳ����� �޾ƿ��� �ڵ�
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
