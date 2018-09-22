// Board.cpp : ���� �����Դϴ�.
//
#include "News.h"
#include "NewsDlg.h"
#include "stdafx.h"
#include "News.h"
#include "Board.h"
#include "afxdialogex.h"
#include "ChildDlg.h"
#include "resource.h"
#include "Chatting.h"
#include <mysql.h>
#include <Winsock2.h>

#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "WS2_32.lib")

#define CON_IP "114.201.35.170"
#define DB_USER "root"
#define DB_PASS "cksals"
#define DB_NAME "newss"
#define DB_TABLE "news"

char Query3[256];
int Query_Status3;


// Board ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Board, CDialog)

Board::Board(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG2, pParent)
{

}

Board::~Board()
{
}

void Board::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listinfo);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Control(pDX, IDC_Picture, m_imgBg);
}

void Board::SetMainListPtr(CString parm_list)
{
	ID = parm_list;
}


BEGIN_MESSAGE_MAP(Board, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &Board::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_search_button, &Board::OnBnClickedsearchbutton)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &Board::OnNMDblclkList1)
	ON_EN_CHANGE(IDC_Find_news, &Board::OnEnChangeFindnews)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Board::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &Board::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Board �޽��� ó�����Դϴ�.

//ó�� �� ���̾�α� â�� ���ý� �ʱ�ȭ�ϴ� �ڵ�
BOOL Board::OnInitDialog()
{
	CDialog::OnInitDialog();

	HBITMAP hBit = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP11));
	m_imgBg.SetBitmap(hBit);
	CRect rt;
	GetClientRect(&rt);
	m_imgBg.SetWindowPos(NULL, 0, 0, rt.Width(), rt.Height(), SWP_SHOWWINDOW);
	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);


	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	//����Ʈ �ڽ��� �Ӽ� ����
	m_listinfo.SetExtendedStyle(m_listinfo.GetExtendedStyle() | LVS_EX_GRIDLINES);

	m_listinfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);


	//����Ʈ �ڽ� ���� �ִ� ������ ����?
	m_listinfo.InsertColumn(0, TEXT("��ȣ"), LVCFMT_LEFT, 60);

	m_listinfo.InsertColumn(1, TEXT("����"), LVCFMT_LEFT, 575);

	m_listinfo.InsertColumn(2, TEXT("���� �̸�����"), LVCFMT_LEFT, 300);

	m_listinfo.InsertColumn(3, TEXT("��õ��"), LVCFMT_LEFT, 80);

	m_listinfo.InsertColumn(4, TEXT("��ȸ��"), LVCFMT_LEFT, 80);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void Board::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}

//�˻���ư�� ������ �߻��ϴ� �ڵ�
void Board::OnBnClickedsearchbutton()//�˻�
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	MYSQL *Connection;
	MYSQL Connect;
	MYSQL_RES *Sql_Result;
	MYSQL_ROW Sql_Row;
	MYSQL_RES *Sql_Resulttitle;
	MYSQL_ROW Sql_Rowtitle;

	int ROW=0;
	char* title[1000];
	char* context_news[10000];
	char* search_number[1000];
	char* good_number[1000];
	CString seq_string;
	int order=1;
	CString Search;



	GetDlgItemText(IDC_Find_news, Search);




		mysql_init(&Connect);
		Connection = mysql_real_connect(&Connect, CON_IP, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
		if (Connection == NULL)
		{
			MessageBox(NULL, _T("DB ���ӿ� �����߽��ϴ�.\n���� ���α׷��� ������ �� �����ϴ�."), MB_OK);
		}
		mysql_set_character_set(&Connect, "euckr");

		

		//Query��
		sprintf_s(Query3, "select * from %s where title like '%%%s%%'", DB_TABLE, Search);
		Query_Status3 = mysql_query(Connection, Query3);
		Sql_Result = mysql_store_result(Connection);
		//Sql_Row = mysql_fetch_row(Sql_Result);
		//����Ʈ��Ʈ���� ������ٰ� �ٽñ׸��鼭 ������ ä���ִ� �Լ�
		m_listinfo.DeleteAllItems();

		//���� ��Ʈ�ѿ� ���� ���� ������ �־� �������ִ� �Լ�..
		UpdateData(TRUE);


		if (Sql_Result->row_count > 0)
		{
			//Sql_Result->row_count���� �˻��� ������ �ִ� ����Ʈ ���� �ǹ�
			//for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
			//{
			while((Sql_Rowtitle = mysql_fetch_row(Sql_Result)) != NULL){

				
				//title�̶� ������ Mysql���� ����� 1���� 1���� ����
				title[ROW] = Sql_Rowtitle[0];
				seq_string.Format(_T("%d"), ROW + 1);
				//insertitem�Լ��� ����Ʈ��Ʈ�ѿ� ���ϼ��ְ� ������ִ��Լ�
				m_listinfo.InsertItem(ROW, seq_string);
				//SetItemText�� ����Ʈ��Ʈ�ѿ� ���ϼ� �ְ� ������ִ� �Լ��̳� ��� ���� �̿��Ͽ� ���
				m_listinfo.SetItemText(ROW, 1, title[ROW]);

				//context_news�̶� ������ Mysql���� ����� 1���� 2���� ����
				context_news[ROW] = Sql_Rowtitle[1];
				m_listinfo.SetItemText(ROW, 2, context_news[ROW]);

				//search_number�̶� ������ Mysql���� ����� 1���� 3���� ����
				search_number[ROW] = Sql_Rowtitle[2];
				m_listinfo.SetItemText(ROW, 3, search_number[ROW]);

				//good_number�̶� ������ Mysql���� ����� 1���� 4���� ����
				good_number[ROW] = Sql_Rowtitle[3];
				m_listinfo.SetItemText(ROW, 4, good_number[ROW]);

				ROW++;
			}
		}
	}

//����Ʈâ�� ����Ŭ���ҽ� ����� �ڵ�
void Board::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	if (pNMItemActivate->iItem >= 0)
	{
		CString news_context123;
		//����Ŭ���� ���� 2��° ��? �� ���⼭�� ������ ������ news_context123�� �ִ´�.
		news_context123 = m_listinfo.GetItemText(pNMItemActivate->iItem, 1);
		CString Comment;
		Comment= m_listinfo.GetItemText(pNMItemActivate->iItem, 2);
		CChildDlg dlg;
		//�̸� �����س� SetMainListPtr�� �̿��Ͽ� �Ź������ ������� ���� ���̾�α׷� �ѱ��.
		dlg.SetMainListPtr(news_context123,ID, Comment);
		dlg.DoModal();
	}
	*pResult = 0;

	*pResult = 0;
}



void Board::OnEnChangeFindnews()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}




void Board::OnCbnSelchangeCombo1()
{
	MYSQL *Connection;
	MYSQL Connect;
	MYSQL_RES *Sql_Result;
	MYSQL_ROW Sql_Row;
	MYSQL_RES *Sql_Resulttitle;
	MYSQL_ROW Sql_Rowtitle;

	int ROW=0;
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


	//Query��

	//����Ʈ��Ʈ���� ������ٰ� �ٽñ׸��鼭 ������ ä���ִ� �Լ�
	m_listinfo.DeleteAllItems();

	//���� ��Ʈ�ѿ� ���� ���� ������ �־� �������ִ� �Լ�..
	UpdateData(TRUE);
	

	GetDlgItemText(IDC_Find_news, Search);

	CString temp;

	this->m_combo.GetLBText(this->m_combo.GetCurSel(), temp);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if ("��ȸ��"== temp) {
		sprintf_s(Query3, "select * from %s where %s like '%%%s%%' ORDER BY search_number DESC", DB_TABLE, "title", Search);
		Query_Status3 = mysql_query(Connection, Query3);
		Sql_Result = mysql_store_result(Connection);

		if (Sql_Result->row_count > 0)
		{
			//Sql_Result->row_count���� �˻��� ������ �ִ� ����Ʈ ���� �ǹ�
			//for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
			//{
			while ((Sql_Rowtitle = mysql_fetch_row(Sql_Result)) != NULL) {


				//title�̶� ������ Mysql���� ����� 1���� 1���� ����
				title[ROW] = Sql_Rowtitle[0];
				seq_string.Format(_T("%d"), ROW + 1);
				//insertitem�Լ��� ����Ʈ��Ʈ�ѿ� ���ϼ��ְ� ������ִ��Լ�
				m_listinfo.InsertItem(ROW, seq_string);
				//SetItemText�� ����Ʈ��Ʈ�ѿ� ���ϼ� �ְ� ������ִ� �Լ��̳� ��� ���� �̿��Ͽ� ���
				m_listinfo.SetItemText(ROW, 1, title[ROW]);

				//context_news�̶� ������ Mysql���� ����� 1���� 2���� ����
				context_news[ROW] = Sql_Rowtitle[1];
				m_listinfo.SetItemText(ROW, 2, context_news[ROW]);

				//search_number�̶� ������ Mysql���� ����� 1���� 3���� ����
				search_number[ROW] = Sql_Rowtitle[2];
				m_listinfo.SetItemText(ROW, 3, search_number[ROW]);

				//good_number�̶� ������ Mysql���� ����� 1���� 4���� ����
				good_number[ROW] = Sql_Rowtitle[3];
				m_listinfo.SetItemText(ROW, 4, good_number[ROW]);

				ROW++;
			}
		}
	}
	else if ("��õ��" == temp) {
		sprintf_s(Query3, "select * from %s where %s like '%%%s%%' ORDER BY good_number DESC", DB_TABLE, "title", Search);
		Query_Status3 = mysql_query(Connection, Query3);
		Sql_Result = mysql_store_result(Connection);

		if (Sql_Result->row_count > 0)
		{
			//Sql_Result->row_count���� �˻��� ������ �ִ� ����Ʈ ���� �ǹ�
			//for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
			//{
			while ((Sql_Rowtitle = mysql_fetch_row(Sql_Result)) != NULL) {


				//title�̶� ������ Mysql���� ����� 1���� 1���� ����
				title[ROW] = Sql_Rowtitle[0];
				seq_string.Format(_T("%d"), ROW + 1);
				//insertitem�Լ��� ����Ʈ��Ʈ�ѿ� ���ϼ��ְ� ������ִ��Լ�
				m_listinfo.InsertItem(ROW, seq_string);
				//SetItemText�� ����Ʈ��Ʈ�ѿ� ���ϼ� �ְ� ������ִ� �Լ��̳� ��� ���� �̿��Ͽ� ���
				m_listinfo.SetItemText(ROW, 1, title[ROW]);

				//context_news�̶� ������ Mysql���� ����� 1���� 2���� ����
				context_news[ROW] = Sql_Rowtitle[1];
				m_listinfo.SetItemText(ROW, 2, context_news[ROW]);

				//search_number�̶� ������ Mysql���� ����� 1���� 3���� ����
				search_number[ROW] = Sql_Rowtitle[2];
				m_listinfo.SetItemText(ROW, 3, search_number[ROW]);

				//good_number�̶� ������ Mysql���� ����� 1���� 4���� ����
				good_number[ROW] = Sql_Rowtitle[3];
				m_listinfo.SetItemText(ROW, 4, good_number[ROW]);

				ROW++;
			}
		}
	}

	else if ("�⺻" == temp) {
		sprintf_s(Query3, "select * from %s where %s like '%%%s%%'", DB_TABLE, "title", Search);
		Query_Status3 = mysql_query(Connection, Query3);
		Sql_Result = mysql_store_result(Connection);

		if (Sql_Result->row_count > 0)
		{
			//Sql_Result->row_count���� �˻��� ������ �ִ� ����Ʈ ���� �ǹ�
			//for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
			//{
			while ((Sql_Rowtitle = mysql_fetch_row(Sql_Result)) != NULL) {


				//title�̶� ������ Mysql���� ����� 1���� 1���� ����
				title[ROW] = Sql_Rowtitle[0];
				seq_string.Format(_T("%d"), ROW + 1);
				//insertitem�Լ��� ����Ʈ��Ʈ�ѿ� ���ϼ��ְ� ������ִ��Լ�
				m_listinfo.InsertItem(ROW, seq_string);
				//SetItemText�� ����Ʈ��Ʈ�ѿ� ���ϼ� �ְ� ������ִ� �Լ��̳� ��� ���� �̿��Ͽ� ���
				m_listinfo.SetItemText(ROW, 1, title[ROW]);

				//context_news�̶� ������ Mysql���� ����� 1���� 2���� ����
				context_news[ROW] = Sql_Rowtitle[1];
				m_listinfo.SetItemText(ROW, 2, context_news[ROW]);

				//search_number�̶� ������ Mysql���� ����� 1���� 3���� ����
				search_number[ROW] = Sql_Rowtitle[2];
				m_listinfo.SetItemText(ROW, 3, search_number[ROW]);

				//good_number�̶� ������ Mysql���� ����� 1���� 4���� ����
				good_number[ROW] = Sql_Rowtitle[3];
				m_listinfo.SetItemText(ROW, 4, good_number[ROW]);

				ROW++;
			}
		}
	}

	

	
}


void Board::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Chatting dlg;
	dlg.DoModal();
}


HBRUSH Board::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
	{
		if (pWnd->GetDlgCtrlID() == IDC_search)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		
	}
	}
	return hbr;
}
