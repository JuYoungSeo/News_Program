// Board_comment.cpp : 구현 파일입니다.
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
// Board_comment 대화 상자입니다.

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


// Board_comment 메시지 처리기입니다.


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


	//리스트 박스 위에 있는 주제들 나열?
	m_listinfo2.InsertColumn(0, TEXT("번호"), LVCFMT_LEFT, 40);

	m_listinfo2.InsertColumn(1, TEXT("닉네임"), LVCFMT_LEFT, 75);

	m_listinfo2.InsertColumn(2, TEXT("댓글내용"), LVCFMT_LEFT, 200);


	mysql_init(&Connect);
	Connection = mysql_real_connect(&Connect, CON_IP, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (Connection == NULL)
	{
		MessageBox(NULL, _T("DB 접속에 실패했습니다.\n응용 프로그램을 시작할 수 없습니다."), MB_OK);
	}
	mysql_set_character_set(&Connect, "euckr");

	//Query문
	sprintf_s(Query0, "select * from %s where %s like '%s'", DB_TABLE, "title", news_context123);

	//성공여부를 Query_Status1변수에 저장
	Query_Status0 = mysql_query(Connection, Query0);

	//Query문에서 찾은 결과(값)를 한꺼번에 받아오는 코드
	Sql_Result = mysql_store_result(Connection);
	Sql_Rowtitle = mysql_fetch_row(Sql_Result);

	Board_idx = Sql_Rowtitle[4];

	sprintf_s(Query0, "select * from %s where %s like '%s'", "comment", "Context_ID", Board_idx);
	Query_Status0 = mysql_query(Connection, Query0);

	//Query문에서 찾은 결과(값)를 한꺼번에 받아오는 코드
	Sql_Result = mysql_store_result(Connection);

	if (Sql_Result->row_count > 0)
	{
		//Sql_Result->row_count값은 검색한 내용이 있는 리스트 수를 의미
		for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
		{
			sprintf_s(Query0, "select * from %s where ROW='%d'", "comment", ROW);
			Query_Status0 = mysql_query(Connection, Query0);
			Sql_Resulttitle = mysql_store_result(Connection);
			Sql_Rowtitle = mysql_fetch_row(Sql_Result);

			//title이란 변수에 Mysql에서 끌어온 1열중 1행을 대입
			title[ROW] = Sql_Rowtitle[0];
			seq_string.Format(_T("%d"), ROW + 1);
			//insertitem함수는 리스트컨트롤에 보일수있게 출력해주는함수
			m_listinfo2.InsertItem(ROW, seq_string);
			//SetItemText는 리스트컨트롤에 보일수 있게 출력해주는 함수이나 행과 열을 이용하여 출력
			m_listinfo2.SetItemText(ROW, 1, title[ROW]);

			//context_news이란 변수에 Mysql에서 끌어온 1열중 2행을 대입
			context_news[ROW] = Sql_Rowtitle[1];
			m_listinfo2.SetItemText(ROW, 2, context_news[ROW]);
		}
	}

	HBITMAP hBit = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP9));
	m_imgBg.SetBitmap(hBit);
	CRect rt;
	GetClientRect(&rt);
	m_imgBg.SetWindowPos(NULL, 0, 0, rt.Width(), rt.Height(), SWP_SHOWWINDOW);
	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void Board_comment::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		MessageBox(NULL, _T("DB 접속에 실패했습니다.\n응용 프로그램을 시작할 수 없습니다."), MB_OK);
	}
	mysql_set_character_set(&Connect, "euckr");

	sprintf_s(Query0, "select * from %s where %s like '%s'", "users", "ID", ID3);

	//성공여부를 Query_Status1변수에 저장
	Query_Status0 = mysql_query(Connection, Query0);

	//Query문에서 찾은 결과(값)를 한꺼번에 받아오는 코드
	Sql_Result = mysql_store_result(Connection);
	Sql_Rowtitle = mysql_fetch_row(Sql_Result);

	Nick = Sql_Rowtitle[2];

	//sprintf_s(Query13, "INSERT INTO comment values('%s', '%s', '%s', '%s')", Nick, Search, Board_idx, Board_idx);
	//sprintf_s(Query13, "insert into comment values('%s', '%s', '%s', '%s')",Nick, Search, Board_idx, Board_idx);
	sprintf_s(Query13, "INSERT INTO comment (NICK,NICK_Comment,Context_ID)values('%s', '%s', '%s')", Nick, Search, Board_idx);
	Query_Status13 = mysql_query(Connection, Query13);

	//AfxMessageBox(_T(mysql_error(Connection)));

	//Query문에서 찾은 결과(값)를 한꺼번에 받아오는 코드
	Sql_Result = mysql_store_result(Connection);

	//리스트콘트롤이 사라졌다가 다시그리면서 데이터 채워넣는 함수
	m_listinfo2.DeleteAllItems();

	//현재 컨트롤에 적힌 값을 변수로 넣어 갱신해주는 함수..
	UpdateData(TRUE);

	sprintf_s(Query0, "select * from %s where %s like '%s'", "comment", "Context_ID", Board_idx);
	Query_Status0 = mysql_query(Connection, Query0);

	//Query문에서 찾은 결과(값)를 한꺼번에 받아오는 코드
	Sql_Result = mysql_store_result(Connection);



	if (Sql_Result->row_count > 0)
	{
		//Sql_Result->row_count값은 검색한 내용이 있는 리스트 수를 의미
		for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
		{
			sprintf_s(Query0, "select * from %s where ROW='%d'", "comment", ROW);
			Query_Status0 = mysql_query(Connection, Query0);
			Sql_Resulttitle = mysql_store_result(Connection);
			Sql_Rowtitle = mysql_fetch_row(Sql_Result);

			//title이란 변수에 Mysql에서 끌어온 1열중 1행을 대입
			title[ROW] = Sql_Rowtitle[0];
			seq_string.Format(_T("%d"), ROW + 1);
			//insertitem함수는 리스트컨트롤에 보일수있게 출력해주는함수
			m_listinfo2.InsertItem(ROW, seq_string);
			//SetItemText는 리스트컨트롤에 보일수 있게 출력해주는 함수이나 행과 열을 이용하여 출력
			m_listinfo2.SetItemText(ROW, 1, title[ROW]);

			//context_news이란 변수에 Mysql에서 끌어온 1열중 2행을 대입
			context_news[ROW] = Sql_Rowtitle[1];
			m_listinfo2.SetItemText(ROW, 2, context_news[ROW]);
		}
	}


	

	/*
	if (Sql_Result->row_count > 0)
	{
		//Sql_Result->row_count값은 검색한 내용이 있는 리스트 수를 의미
		for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
		{
			sprintf_s(Query3, "select * from %s where ROW='%d'", DB_TABLE, ROW);
			Query_Status3 = mysql_query(Connection, Query3);
			Sql_Resulttitle = mysql_store_result(Connection);
			Sql_Rowtitle = mysql_fetch_row(Sql_Result);

			//title이란 변수에 Mysql에서 끌어온 1열중 1행을 대입
			title[ROW] = Sql_Rowtitle[0];
			seq_string.Format(_T("%d"), ROW + 1);
			//insertitem함수는 리스트컨트롤에 보일수있게 출력해주는함수
			m_listinfo2.InsertItem(ROW, seq_string);
			//SetItemText는 리스트컨트롤에 보일수 있게 출력해주는 함수이나 행과 열을 이용하여 출력
			m_listinfo2.SetItemText(ROW, 1, title[ROW]);

			//context_news이란 변수에 Mysql에서 끌어온 1열중 2행을 대입
			context_news[ROW] = Sql_Rowtitle[1];
			m_listinfo2.SetItemText(ROW, 2, context_news[ROW]);

			//search_number이란 변수에 Mysql에서 끌어온 1열중 3행을 대입
			search_number[ROW] = Sql_Rowtitle[2];
			m_listinfo2.SetItemText(ROW, 3, search_number[ROW]);

			//good_number이란 변수에 Mysql에서 끌어온 1열중 4행을 대입
			good_number[ROW] = Sql_Rowtitle[3];
			m_listinfo2.SetItemText(ROW, 4, good_number[ROW]);
		}
	}
	*/
}


void Board_comment::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		MessageBox(NULL, _T("DB 접속에 실패했습니다.\n응용 프로그램을 시작할 수 없습니다."), MB_OK);
	}
	mysql_set_character_set(&Connect, "euckr");

	sprintf_s(Query0, "select * from %s where %s like '%s'", "users", "ID", ID3);

	//성공여부를 Query_Status1변수에 저장
	Query_Status0 = mysql_query(Connection, Query0);

	//Query문에서 찾은 결과(값)를 한꺼번에 받아오는 코드
	Sql_Result = mysql_store_result(Connection);
	Sql_Rowtitle = mysql_fetch_row(Sql_Result);

	Nick = Sql_Rowtitle[2];

	if (pNMItemActivate->iItem >= 0)
	{
		CString news_context123;
		CString idd;
		//더블클릭한 열중 2번째 행? 즉 여기서는 내용을 가져와 news_context123에 넣는다.
		news_context123 = m_listinfo2.GetItemText(pNMItemActivate->iItem, 1);
		idd= m_listinfo2.GetItemText(pNMItemActivate->iItem, 2);
		if (news_context123 == Nick) {
			

			sprintf_s(Query0, "delete from comment where NICK_Comment like '%s'", idd);
			Query_Status0 = mysql_query(Connection, Query0);

			//Query문에서 찾은 결과(값)를 한꺼번에 받아오는 코드
			Sql_Result = mysql_store_result(Connection);



		}
		else {
			AfxMessageBox(_T("본인 댓글만 삭제 가능합니다."));
		}

		//리스트콘트롤이 사라졌다가 다시그리면서 데이터 채워넣는 함수
		m_listinfo2.DeleteAllItems();

		//현재 컨트롤에 적힌 값을 변수로 넣어 갱신해주는 함수..
		UpdateData(TRUE);


		sprintf_s(Query0, "select * from %s where %s like '%s'", "comment", "Context_ID", Board_idx);
		Query_Status0 = mysql_query(Connection, Query0);

		//Query문에서 찾은 결과(값)를 한꺼번에 받아오는 코드
		Sql_Result = mysql_store_result(Connection);




		if (Sql_Result->row_count > 0)
		{
			//Sql_Result->row_count값은 검색한 내용이 있는 리스트 수를 의미
			for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
			{
				sprintf_s(Query0, "select * from %s where ROW='%d'", "comment", ROW);
				Query_Status0 = mysql_query(Connection, Query0);
				Sql_Resulttitle = mysql_store_result(Connection);
				Sql_Rowtitle = mysql_fetch_row(Sql_Result);

				//title이란 변수에 Mysql에서 끌어온 1열중 1행을 대입
				title[ROW] = Sql_Rowtitle[0];
				seq_string.Format(_T("%d"), ROW + 1);
				//insertitem함수는 리스트컨트롤에 보일수있게 출력해주는함수
				m_listinfo2.InsertItem(ROW, seq_string);
				//SetItemText는 리스트컨트롤에 보일수 있게 출력해주는 함수이나 행과 열을 이용하여 출력
				m_listinfo2.SetItemText(ROW, 1, title[ROW]);

				//context_news이란 변수에 Mysql에서 끌어온 1열중 2행을 대입
				context_news[ROW] = Sql_Rowtitle[1];
				m_listinfo2.SetItemText(ROW, 2, context_news[ROW]);
			}
		}


	}
	*pResult = 0;
}
