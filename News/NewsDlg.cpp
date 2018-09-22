
// NewsDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "News.h"
#include "NewsDlg.h"
#include "afxdialogex.h"
#include "Join_member.h"
#include "Board.h"
#include <mysql.h>
#include <Winsock2.h>

#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "WS2_32.lib")

////mysql������ ���� ��� ����
#define CON_IP "114.201.35.170"//ip�ּ�
#define DB_USER "root"//���� ������ �������̵�
#define DB_PASS "cksals"//DB �н�����
#define DB_NAME "newss"//DB �̸�
#define DB_TABLE "users"//DB ���̺� �̸�

//Query���� ���� ���� ����
char Query1[256];
int Query_Status1;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNewsDlg ��ȭ ����



CNewsDlg::CNewsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NEWS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNewsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ID_LOGIN, ID_Member);
	DDX_Control(pDX, IDC_PASSWORD_LOGIN, PASSWORD_Member);
	DDX_Control(pDX, IDC_Picture, m_imgBg);
}

BEGIN_MESSAGE_MAP(CNewsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CNewsDlg::OnBnClickedButton1)
	//ON_EN_CHANGE(IDC_EDIT1, &CNewsDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CNewsDlg::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CNewsDlg �޽��� ó����

BOOL CNewsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	HBITMAP hBit = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP10));
	m_imgBg.SetBitmap(hBit);
	CRect rt;
	GetClientRect(&rt);
	m_imgBg.SetWindowPos(NULL, 0, 0, rt.Width(), rt.Height(), SWP_SHOWWINDOW);
	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CNewsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CNewsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CNewsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//ȸ�������ϴ� ��ưŬ����
void CNewsDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Join_member dlg; 
	dlg.DoModal();//ȸ������â(Join_member)�� â�� ����
}


void CNewsDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CNewsDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	MYSQL *Connection;
	MYSQL Connect;
	MYSQL_RES *Sql_Result;
	MYSQL_ROW Sql_Row;
	MYSQL_ROW Row;

	//Mysql �ʱ�ȭ�ϴ� �Լ�
	mysql_init(&Connect);

	//Mysql�����ϴ� �Լ�, �����ҽ� Connection�� NULL���� ����. 3306�� ó�� MYSQL�� port�ѹ�
	Connection = mysql_real_connect(&Connect, CON_IP, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (Connection == NULL)
	{
		MessageBox(NULL, _T("DB ���ӿ� �����߽��ϴ�.\n���� ���α׷��� ������ �� �����ϴ�."), MB_OK);
	}


	CString inputID;
	CString inputPWD;

	//�α���â�� ���� ���̵� �н�������� ���� �����鿡 ����
	GetDlgItemText(IDC_ID_LOGIN, inputID);
	GetDlgItemText(IDC_PASSWORD_LOGIN, inputPWD);

	//DB_TABLE�ȿ� �ִ� inputID�� inputPW�� ������ �ִ��� �˻��Ͽ� ����� Query1�� ����
	sprintf_s(Query1, "select * from %s where ID='%s' and PASSWORD='%s'", DB_TABLE, inputID, inputPWD);

	//�������θ� Query_Status1������ ����
	Query_Status1 = mysql_query(Connection, Query1);

	//Query������ ã�� ���(��)�� �Ѳ����� �޾ƿ��� �ڵ�
	Sql_Result = mysql_store_result(Connection);

	//Sql_Result�� ��� ������ �Ѱ��� ROW(��)�� ������ �ڵ�
	Sql_Row = mysql_fetch_row(Sql_Result);

	//Sql_Result�� ��� ������ �������� ����̹Ƿ� �Խ��� â�� ����.
	if (Sql_Result->row_count > 0)
	{
		Board dlg;
		dlg.SetMainListPtr(inputID);
		dlg.DoModal();
	}

	else
	{
		MessageBox(_T("ID�� ��й�ȣ�� ��ġ���� �ʽ��ϴ�."));
	}
}


HBRUSH CNewsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
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

	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}
