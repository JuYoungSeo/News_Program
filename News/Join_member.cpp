// Join_member.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "News.h"
#include "Join_member.h"
#include "afxdialogex.h"
#include "Resource.h"
#include <Winsock2.h>
#include <mysql.h>

#pragma comment(lib, "libmysql.lib")//mysql������ ���� ����
////mysql������ ���� ��� ����
#define CON_IP "114.201.35.170"//ip�ּ�
#define DB_USER "root"//���� ������ �������̵�
#define DB_PASS "cksals"//DB �н�����
#define DB_NAME "newss"//DB �̸�
#define DB_TABLE "users"//DB ���̺� �̸�

//mysql������ ���� ����
MYSQL *Connection;
MYSQL Connect;
MYSQL_RES *Sql_Result;
MYSQL_ROW Sql_Row;

CString NAME;
CString ID;
CString NICKNAME;
CString PASSWORD;
CString REPASSWORD;

char Query[256];
int Query_Status;

// Join_member ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Join_member, CDialogEx)

Join_member::Join_member(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Join_member::~Join_member()
{
}

void Join_member::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_JM_NAME, Join_Name);
	DDX_Control(pDX, IDC_JM_ID, Join_ID);
	DDX_Control(pDX, IDC_JM_PASSWORD, Join_PASSWORD);
	DDX_Control(pDX, IDC_JM_PASSWORD_OK, Join_PASSWORD_OK);
	DDX_Control(pDX, IDC_JM_NICKNAME, Join_NICKNAME);
	DDX_Control(pDX, IDC_Picture, m_imgBg);
}


BEGIN_MESSAGE_MAP(Join_member, CDialogEx)
	ON_BN_CLICKED(IDOK, &Join_member::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &Join_member::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Join_member �޽��� ó�����Դϴ�.


void Join_member::OnBnClickedOk()//ȸ������â�� Ȯ�ι�ư�� �������� �߻��ϴ� �ڵ�
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//mysql �ʱ�ȭ
	mysql_init(&Connect);
	
	//Mysql�����ϴ� �Լ�, �����ҽ� Connection�� NULL���� ����. 3306�� ó�� MYSQL�� port�ѹ�
	Connection = mysql_real_connect(&Connect, CON_IP, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (Connection == NULL)
	{
		MessageBox(NULL, _T("DB ���ӿ� �����߽��ϴ�.\n���� ���α׷��� ������ �� �����ϴ�."), MB_OK);
	}

	//�ѱ� �������� �����ϴ� �ڵ�
	mysql_set_character_set(&Connect, "euckr");

	//ȸ������â�� �ִ� ���� editbox�� �Է��� ������� ���� �������ٰ� ����
	GetDlgItemText(IDC_JM_NAME, NAME);
	GetDlgItemText(IDC_JM_ID, ID);
	GetDlgItemText(IDC_JM_NICKNAME, NICKNAME);
	GetDlgItemText(IDC_JM_PASSWORD, PASSWORD);
	GetDlgItemText(IDC_JM_PASSWORD_OK, REPASSWORD);

	//ȸ������â�� ������ �����ϰų� ������ ������ �˷��ִ� â�� ������ �ڵ�, ���� ��Ȯ�ϰ� �Է½� ȯ���մϴٶ�� �ڵ尡 ���´�.
	if ((_tcslen(NAME)) == 0 || (_tcslen(ID)) == 0 || (_tcslen(NICKNAME)) == 0 || (_tcslen(PASSWORD)) == 0)
	{
		MessageBox(_T("��� �׸��� �� ä���ּ���."), 0);
	}
	else if (PASSWORD != REPASSWORD)
	{
		MessageBox(_T("��й�ȣ�� ��ġ���� �ʽ��ϴ�."), 0);
	}
	else
	{
		//MYSQL������ ���� DB_TABLE, NAME, ID, NICKNAME, PASSWORD�� ��� " "�ȿ��ִ� %s�� �������� �̹����� Query���� ����.
		//insert�� �ڵ�� values(%s)�� ������ into�ڿ��ִ� %s�� �̸��� ���� MYSQL���� ���̺�� ������ ����ȴ�.
		sprintf_s(Query, "insert into users values('%s', '%s', '%s', '%s')",  NAME, ID, NICKNAME, PASSWORD);

		//Query���� �������θ� �˷��ִ� ����
		Query_Status = mysql_query(Connection, Query);
		if (Query_Status)
		{
			MessageBox(_T("ȸ�������� �Ϸ��ϴ� ���߿� ������ �߻��Ͽ����ϴ�."), _T("�����ͺ��̽� ����"));
		}
		else
		{
			MessageBox(_T("ȸ�������� ȯ���մϴ�"));
			CDialogEx::OnOK();
		}
	}

	//ȸ������â�� �������(�ݰ�) �ϴ� �ڵ�
	CDialogEx::OnOK();
}


void Join_member::OnBnClickedButton1()////ȸ������â�� ���̵� �ߺ�Ȯ�� ��ư�� �������� �߻��ϴ� �ڵ�
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	mysql_init(&Connect);
	Connection = mysql_real_connect(&Connect, CON_IP, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (Connection == NULL)
	{
		MessageBox(NULL, _T("DB ���ӿ� �����߽��ϴ�.\n���� ���α׷��� ������ �� �����ϴ�."), MB_OK);
	}
	mysql_set_character_set(&Connect, "euckr");

	GetDlgItemText(IDC_JM_ID, ID);
	
	//select�� �ڵ�� DB_TABLE�ȿ� �� ID�� �̸��� �ִ��� ã�� ����
	//from�� ��� ���̺�� ������ �Է¹޴°Ű� where�� if�� ���� ���ǹ��� �ǹ��Ѵ�.
	sprintf_s(Query, "select * from %s where ID='%s'", DB_TABLE, ID);

	Query_Status = mysql_query(Connection, Query);

	//Query������ ã�� ����� �Ѳ����� �޾ƿ��� �ڵ�
	Sql_Result = mysql_store_result(Connection);

	//Sql_Result�� ��� ������ �Ѱ��� ROW(��)�� ������ �ڵ�
	Sql_Row = mysql_fetch_row(Sql_Result);

	//���̵� �ߺ��˻�
	if ((_tcslen(ID)) == 0)
	{
		MessageBox(_T("ID�� �Է����ּ���."));
	}

	//���� row_count�� ����� ��쿡�� �ߺ��Ǵ� ID�� �ִ� ���� �����Դٴ� �ǹ�
	else if (Sql_Result->row_count > 0)
	{
		MessageBox(_T("�ߺ��Դϴ�."));
	}
	else
	{
		MessageBox(_T("����Ͻ� �� �ִ� ID �Դϴ�."));
	}
}


BOOL Join_member::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	HBITMAP hBit = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP12));
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


HBRUSH Join_member::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC)
		{
			pDC->SetTextColor(RGB(255, 0, 255));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		if (pWnd->GetDlgCtrlID() == IDC_STATIC2)
		{
			pDC->SetTextColor(RGB(0, 255, 0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
	}
	}

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}
