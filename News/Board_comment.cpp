// Board_comment.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "News.h"
#include "Board_comment.h"
#include "afxdialogex.h"

#include <mysql.h>
#include <Winsock2.h>

#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "WS2_32.lib")

#define CON_IP "114.201.35.170"
#define DB_USER "root"
#define DB_PASS "cksals"
#define DB_NAME "newss"
#define DB_TABLE "news"

CString ID3;
CString Nick;

char Query0[256];
int Query_Status0;

char Query13[256];
int Query_Status13;
CString Board_idx;

CString news_context123;
// Board_comment ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Board_comment, CDialogEx)

Board_comment::Board_comment(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

}

void Board_comment::SetMainListPtr(CString parm_list, CString ID2)
{
	news_context123 = parm_list;
	ID3 = ID2;
}

Board_comment::~Board_comment()
{
}

void Board_comment::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listinfo2);
	DDX_Control(pDX, IDC_Picture, m_imgBg);
}



BEGIN_MESSAGE_MAP(Board_comment, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Board_comment::OnBnClickedButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &Board_comment::OnNMDblclkList1)
END_MESSAGE_MAP()


// Board_comment �޽��� ó�����Դϴ�.


BOOL Board_comment::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	MYSQL *Connection;
	MYSQL Connect;
	MYSQL_RES *Sql_Result;
	MYSQL_ROW Sql_Row;
	MYSQL_RES *Sql_Resulttitle;
	MYSQL_ROW Sql_Rowtitle;

	int ROW;
	char* title[512];
	char* context_news[10000];
	char* search_number[10];
	char* good_number[10];
	CString seq_string;
	int order = 1;
	CString Search;


	m_listinfo2.SetExtendedStyle(m_listinfo2.GetExtendedStyle() | LVS_EX_GRIDLINES);

	m_listinfo2.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);


	//����Ʈ �ڽ� ���� �ִ� ������ ����?
	m_listinfo2.InsertColumn(0, TEXT("��ȣ"), LVCFMT_LEFT, 40);

	m_listinfo2.InsertColumn(1, TEXT("�г���"), LVCFMT_LEFT, 75);

	m_listinfo2.InsertColumn(2, TEXT("��۳���"), LVCFMT_LEFT, 200);


	mysql_init(&Connect);
	Connection = mysql_real_connect(&Connect, CON_IP, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (Connection == NULL)
	{
		MessageBox(NULL, _T("DB ���ӿ� �����߽��ϴ�.\n���� ���α׷��� ������ �� �����ϴ�."), MB_OK);
	}
	mysql_set_character_set(&Connect, "euckr");

	//Query��
	sprintf_s(Query0, "select * from %s where %s like '%s'", DB_TABLE, "title", news_context123);

	//�������θ� Query_Status1������ ����
	Query_Status0 = mysql_query(Connection, Query0);

	//Query������ ã�� ���(��)�� �Ѳ����� �޾ƿ��� �ڵ�
	Sql_Result = mysql_store_result(Connection);
	Sql_Rowtitle = mysql_fetch_row(Sql_Result);

	Board_idx = Sql_Rowtitle[4];

	sprintf_s(Query0, "select * from %s where %s like '%s'", "comment", "Context_ID", Board_idx);
	Query_Status0 = mysql_query(Connection, Query0);

	//Query������ ã�� ���(��)�� �Ѳ����� �޾ƿ��� �ڵ�
	Sql_Result = mysql_store_result(Connection);

	if (Sql_Result->row_count > 0)
	{
		//Sql_Result->row_count���� �˻��� ������ �ִ� ����Ʈ ���� �ǹ�
		for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
		{
			sprintf_s(Query0, "select * from %s where ROW='%d'", "comment", ROW);
			Query_Status0 = mysql_query(Connection, Query0);
			Sql_Resulttitle = mysql_store_result(Connection);
			Sql_Rowtitle = mysql_fetch_row(Sql_Result);

			//title�̶� ������ Mysql���� ����� 1���� 1���� ����
			title[ROW] = Sql_Rowtitle[0];
			seq_string.Format(_T("%d"), ROW + 1);
			//insertitem�Լ��� ����Ʈ��Ʈ�ѿ� ���ϼ��ְ� ������ִ��Լ�
			m_listinfo2.InsertItem(ROW, seq_string);
			//SetItemText�� ����Ʈ��Ʈ�ѿ� ���ϼ� �ְ� ������ִ� �Լ��̳� ��� ���� �̿��Ͽ� ���
			m_listinfo2.SetItemText(ROW, 1, title[ROW]);

			//context_news�̶� ������ Mysql���� ����� 1���� 2���� ����
			context_news[ROW] = Sql_Rowtitle[1];
			m_listinfo2.SetItemText(ROW, 2, context_news[ROW]);
		}
	}

	HBITMAP hBit = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP9));
	m_imgBg.SetBitmap(hBit);
	CRect rt;
	GetClientRect(&rt);
	m_imgBg.SetWindowPos(NULL, 0, 0, rt.Width(), rt.Height(), SWP_SHOWWINDOW);
	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void Board_comment::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	MYSQL *Connection;
	MYSQL Connect;
	MYSQL_RES *Sql_Result;
	MYSQL_ROW Sql_Row;
	MYSQL_RES *Sql_Resulttitle;
	MYSQL_ROW Sql_Rowtitle;

	int ROW;
	char* title[512];
	char* context_news[10000];
	char* search_number[10];
	char* good_number[10];
	CString seq_string;
	int order = 1;
	CString Search;

	GetDlgItemText(IDC_EDIT1, Search);

	mysql_init(&Connect);
	Connection = mysql_real_connect(&Connect, CON_IP, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (Connection == NULL)
	{
		MessageBox(NULL, _T("DB ���ӿ� �����߽��ϴ�.\n���� ���α׷��� ������ �� �����ϴ�."), MB_OK);
	}
	mysql_set_character_set(&Connect, "euckr");

	sprintf_s(Query0, "select * from %s where %s like '%s'", "users", "ID", ID3);

	//�������θ� Query_Status1������ ����
	Query_Status0 = mysql_query(Connection, Query0);

	//Query������ ã�� ���(��)�� �Ѳ����� �޾ƿ��� �ڵ�
	Sql_Result = mysql_store_result(Connection);
	Sql_Rowtitle = mysql_fetch_row(Sql_Result);

	Nick = Sql_Rowtitle[2];

	//sprintf_s(Query13, "INSERT INTO comment values('%s', '%s', '%s', '%s')", Nick, Search, Board_idx, Board_idx);
	//sprintf_s(Query13, "insert into comment values('%s', '%s', '%s', '%s')",Nick, Search, Board_idx, Board_idx);
	sprintf_s(Query13, "INSERT INTO comment (NICK,NICK_Comment,Context_ID)values('%s', '%s', '%s')", Nick, Search, Board_idx);
	Query_Status13 = mysql_query(Connection, Query13);

	//AfxMessageBox(_T(mysql_error(Connection)));

	//Query������ ã�� ���(��)�� �Ѳ����� �޾ƿ��� �ڵ�
	Sql_Result = mysql_store_result(Connection);

	//����Ʈ��Ʈ���� ������ٰ� �ٽñ׸��鼭 ������ ä���ִ� �Լ�
	m_listinfo2.DeleteAllItems();

	//���� ��Ʈ�ѿ� ���� ���� ������ �־� �������ִ� �Լ�..
	UpdateData(TRUE);

	sprintf_s(Query0, "select * from %s where %s like '%s'", "comment", "Context_ID", Board_idx);
	Query_Status0 = mysql_query(Connection, Query0);

	//Query������ ã�� ���(��)�� �Ѳ����� �޾ƿ��� �ڵ�
	Sql_Result = mysql_store_result(Connection);



	if (Sql_Result->row_count > 0)
	{
		//Sql_Result->row_count���� �˻��� ������ �ִ� ����Ʈ ���� �ǹ�
		for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
		{
			sprintf_s(Query0, "select * from %s where ROW='%d'", "comment", ROW);
			Query_Status0 = mysql_query(Connection, Query0);
			Sql_Resulttitle = mysql_store_result(Connection);
			Sql_Rowtitle = mysql_fetch_row(Sql_Result);

			//title�̶� ������ Mysql���� ����� 1���� 1���� ����
			title[ROW] = Sql_Rowtitle[0];
			seq_string.Format(_T("%d"), ROW + 1);
			//insertitem�Լ��� ����Ʈ��Ʈ�ѿ� ���ϼ��ְ� ������ִ��Լ�
			m_listinfo2.InsertItem(ROW, seq_string);
			//SetItemText�� ����Ʈ��Ʈ�ѿ� ���ϼ� �ְ� ������ִ� �Լ��̳� ��� ���� �̿��Ͽ� ���
			m_listinfo2.SetItemText(ROW, 1, title[ROW]);

			//context_news�̶� ������ Mysql���� ����� 1���� 2���� ����
			context_news[ROW] = Sql_Rowtitle[1];
			m_listinfo2.SetItemText(ROW, 2, context_news[ROW]);
		}
	}


	

	/*
	if (Sql_Result->row_count > 0)
	{
		//Sql_Result->row_count���� �˻��� ������ �ִ� ����Ʈ ���� �ǹ�
		for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
		{
			sprintf_s(Query3, "select * from %s where ROW='%d'", DB_TABLE, ROW);
			Query_Status3 = mysql_query(Connection, Query3);
			Sql_Resulttitle = mysql_store_result(Connection);
			Sql_Rowtitle = mysql_fetch_row(Sql_Result);

			//title�̶� ������ Mysql���� ����� 1���� 1���� ����
			title[ROW] = Sql_Rowtitle[0];
			seq_string.Format(_T("%d"), ROW + 1);
			//insertitem�Լ��� ����Ʈ��Ʈ�ѿ� ���ϼ��ְ� ������ִ��Լ�
			m_listinfo2.InsertItem(ROW, seq_string);
			//SetItemText�� ����Ʈ��Ʈ�ѿ� ���ϼ� �ְ� ������ִ� �Լ��̳� ��� ���� �̿��Ͽ� ���
			m_listinfo2.SetItemText(ROW, 1, title[ROW]);

			//context_news�̶� ������ Mysql���� ����� 1���� 2���� ����
			context_news[ROW] = Sql_Rowtitle[1];
			m_listinfo2.SetItemText(ROW, 2, context_news[ROW]);

			//search_number�̶� ������ Mysql���� ����� 1���� 3���� ����
			search_number[ROW] = Sql_Rowtitle[2];
			m_listinfo2.SetItemText(ROW, 3, search_number[ROW]);

			//good_number�̶� ������ Mysql���� ����� 1���� 4���� ����
			good_number[ROW] = Sql_Rowtitle[3];
			m_listinfo2.SetItemText(ROW, 4, good_number[ROW]);
		}
	}
	*/
}


void Board_comment::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	MYSQL *Connection;
	MYSQL Connect;
	MYSQL_RES *Sql_Result;
	MYSQL_ROW Sql_Row;
	MYSQL_RES *Sql_Resulttitle;
	MYSQL_ROW Sql_Rowtitle;

	int ROW;
	char* title[512];
	char* context_news[10000];
	char* search_number[10];
	char* good_number[10];
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

	sprintf_s(Query0, "select * from %s where %s like '%s'", "users", "ID", ID3);

	//�������θ� Query_Status1������ ����
	Query_Status0 = mysql_query(Connection, Query0);

	//Query������ ã�� ���(��)�� �Ѳ����� �޾ƿ��� �ڵ�
	Sql_Result = mysql_store_result(Connection);
	Sql_Rowtitle = mysql_fetch_row(Sql_Result);

	Nick = Sql_Rowtitle[2];

	if (pNMItemActivate->iItem >= 0)
	{
		CString news_context123;
		CString idd;
		//����Ŭ���� ���� 2��° ��? �� ���⼭�� ������ ������ news_context123�� �ִ´�.
		news_context123 = m_listinfo2.GetItemText(pNMItemActivate->iItem, 1);
		idd= m_listinfo2.GetItemText(pNMItemActivate->iItem, 2);
		if (news_context123 == Nick) {
			

			sprintf_s(Query0, "delete from comment where NICK_Comment like '%s'", idd);
			Query_Status0 = mysql_query(Connection, Query0);

			//Query������ ã�� ���(��)�� �Ѳ����� �޾ƿ��� �ڵ�
			Sql_Result = mysql_store_result(Connection);



		}
		else {
			AfxMessageBox(_T("���� ��۸� ���� �����մϴ�."));
		}

		//����Ʈ��Ʈ���� ������ٰ� �ٽñ׸��鼭 ������ ä���ִ� �Լ�
		m_listinfo2.DeleteAllItems();

		//���� ��Ʈ�ѿ� ���� ���� ������ �־� �������ִ� �Լ�..
		UpdateData(TRUE);


		sprintf_s(Query0, "select * from %s where %s like '%s'", "comment", "Context_ID", Board_idx);
		Query_Status0 = mysql_query(Connection, Query0);

		//Query������ ã�� ���(��)�� �Ѳ����� �޾ƿ��� �ڵ�
		Sql_Result = mysql_store_result(Connection);




		if (Sql_Result->row_count > 0)
		{
			//Sql_Result->row_count���� �˻��� ������ �ִ� ����Ʈ ���� �ǹ�
			for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
			{
				sprintf_s(Query0, "select * from %s where ROW='%d'", "comment", ROW);
				Query_Status0 = mysql_query(Connection, Query0);
				Sql_Resulttitle = mysql_store_result(Connection);
				Sql_Rowtitle = mysql_fetch_row(Sql_Result);

				//title�̶� ������ Mysql���� ����� 1���� 1���� ����
				title[ROW] = Sql_Rowtitle[0];
				seq_string.Format(_T("%d"), ROW + 1);
				//insertitem�Լ��� ����Ʈ��Ʈ�ѿ� ���ϼ��ְ� ������ִ��Լ�
				m_listinfo2.InsertItem(ROW, seq_string);
				//SetItemText�� ����Ʈ��Ʈ�ѿ� ���ϼ� �ְ� ������ִ� �Լ��̳� ��� ���� �̿��Ͽ� ���
				m_listinfo2.SetItemText(ROW, 1, title[ROW]);

				//context_news�̶� ������ Mysql���� ����� 1���� 2���� ����
				context_news[ROW] = Sql_Rowtitle[1];
				m_listinfo2.SetItemText(ROW, 2, context_news[ROW]);
			}
		}


	}
	*pResult = 0;
}
