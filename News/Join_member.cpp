// Join_member.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "News.h"
#include "Join_member.h"
#include "afxdialogex.h"
#include "Resource.h"
#include <Winsock2.h>
#include <mysql.h>

#pragma comment(lib, "libmysql.lib")//mysql연동을 위한 정의
////mysql연동을 위한 상수 정의
#define CON_IP "114.201.35.170"//ip주소
#define DB_USER "root"//접근 가능한 유저아이디
#define DB_PASS "cksals"//DB 패스워드
#define DB_NAME "newss"//DB 이름
#define DB_TABLE "users"//DB 테이블 이름

//mysql연동을 위한 정의
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

// Join_member 대화 상자입니다.

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


// Join_member 메시지 처리기입니다.


void Join_member::OnBnClickedOk()//회원가입창의 확인버튼을 눌렀을시 발생하는 코드
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//mysql 초기화
	mysql_init(&Connect);
	
	//Mysql연결하는 함수, 실패할시 Connection에 NULL값이 들어간다. 3306은 처음 MYSQL깔때 port넘버
	Connection = mysql_real_connect(&Connect, CON_IP, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (Connection == NULL)
	{
		MessageBox(NULL, _T("DB 접속에 실패했습니다.\n응용 프로그램을 시작할 수 없습니다."), MB_OK);
	}

	//한글 깨짐현상 방지하는 코드
	mysql_set_character_set(&Connect, "euckr");

	//회원가입창에 있는 각각 editbox에 입력한 내용들을 각각 변수에다가 저장
	GetDlgItemText(IDC_JM_NAME, NAME);
	GetDlgItemText(IDC_JM_ID, ID);
	GetDlgItemText(IDC_JM_NICKNAME, NICKNAME);
	GetDlgItemText(IDC_JM_PASSWORD, PASSWORD);
	GetDlgItemText(IDC_JM_PASSWORD_OK, REPASSWORD);

	//회원가입창에 정보가 부족하거나 오류가 났을시 알려주는 창이 나오는 코드, 만약 정확하게 입력시 환영합니다라는 코드가 나온다.
	if ((_tcslen(NAME)) == 0 || (_tcslen(ID)) == 0 || (_tcslen(NICKNAME)) == 0 || (_tcslen(PASSWORD)) == 0)
	{
		MessageBox(_T("모든 항목을 다 채워주세요."), 0);
	}
	else if (PASSWORD != REPASSWORD)
	{
		MessageBox(_T("비밀번호가 일치하지 않습니다."), 0);
	}
	else
	{
		//MYSQL쿼리문 각각 DB_TABLE, NAME, ID, NICKNAME, PASSWORD를 가운데 " "안에있는 %s에 대입한후 이문장이 Query문에 들어간다.
		//insert란 코드는 values(%s)의 값들이 into뒤에있는 %s의 이름을 가진 MYSQL안의 테이블로 값들이 저장된다.
		sprintf_s(Query, "insert into users values('%s', '%s', '%s', '%s')",  NAME, ID, NICKNAME, PASSWORD);

		//Query문의 성공여부를 알려주는 변수
		Query_Status = mysql_query(Connection, Query);
		if (Query_Status)
		{
			MessageBox(_T("회원가입을 완료하는 도중에 오류가 발생하였습니다."), _T("데이터베이스 오류"));
		}
		else
		{
			MessageBox(_T("회원가입을 환영합니다"));
			CDialogEx::OnOK();
		}
	}

	//회원가입창을 사라지게(닫게) 하는 코드
	CDialogEx::OnOK();
}


void Join_member::OnBnClickedButton1()////회원가입창의 아이디 중복확인 버튼을 눌렀을시 발생하는 코드
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mysql_init(&Connect);
	Connection = mysql_real_connect(&Connect, CON_IP, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (Connection == NULL)
	{
		MessageBox(NULL, _T("DB 접속에 실패했습니다.\n응용 프로그램을 시작할 수 없습니다."), MB_OK);
	}
	mysql_set_character_set(&Connect, "euckr");

	GetDlgItemText(IDC_JM_ID, ID);
	
	//select란 코드는 DB_TABLE안에 들어가 ID란 이름이 있는지 찾는 구문
	//from은 어디 테이블로 들어갈건지 입력받는거고 where은 if문 같이 조건문을 의미한다.
	sprintf_s(Query, "select * from %s where ID='%s'", DB_TABLE, ID);

	Query_Status = mysql_query(Connection, Query);

	//Query문에서 찾은 결과를 한꺼번에 받아오는 코드
	Sql_Result = mysql_store_result(Connection);

	//Sql_Result의 결과 값들을 한개의 ROW(열)을 얻어오는 코드
	Sql_Row = mysql_fetch_row(Sql_Result);

	//아이디 중복검사
	if ((_tcslen(ID)) == 0)
	{
		MessageBox(_T("ID를 입력해주세요."));
	}

	//만약 row_count가 양수일 경우에는 중복되는 ID가 있는 열을 가져왔다는 의미
	else if (Sql_Result->row_count > 0)
	{
		MessageBox(_T("중복입니다."));
	}
	else
	{
		MessageBox(_T("사용하실 수 있는 ID 입니다."));
	}
}


BOOL Join_member::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	HBITMAP hBit = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP12));
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


HBRUSH Join_member::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
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

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
