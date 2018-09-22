// Board.cpp : 구현 파일입니다.
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


// Board 대화 상자입니다.

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


// Board 메시지 처리기입니다.

//처음 이 다이얼로그 창이 나올시 초기화하는 코드
BOOL Board::OnInitDialog()
{
	CDialog::OnInitDialog();

	HBITMAP hBit = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP11));
	m_imgBg.SetBitmap(hBit);
	CRect rt;
	GetClientRect(&rt);
	m_imgBg.SetWindowPos(NULL, 0, 0, rt.Width(), rt.Height(), SWP_SHOWWINDOW);
	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);


	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	//리스트 박스의 속성 정의
	m_listinfo.SetExtendedStyle(m_listinfo.GetExtendedStyle() | LVS_EX_GRIDLINES);

	m_listinfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);


	//리스트 박스 위에 있는 주제들 나열?
	m_listinfo.InsertColumn(0, TEXT("번호"), LVCFMT_LEFT, 60);

	m_listinfo.InsertColumn(1, TEXT("주제"), LVCFMT_LEFT, 575);

	m_listinfo.InsertColumn(2, TEXT("내용 미리보기"), LVCFMT_LEFT, 300);

	m_listinfo.InsertColumn(3, TEXT("추천수"), LVCFMT_LEFT, 80);

	m_listinfo.InsertColumn(4, TEXT("조회수"), LVCFMT_LEFT, 80);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void Board::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

//검색버튼을 누를시 발생하는 코드
void Board::OnBnClickedsearchbutton()//검색
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
			MessageBox(NULL, _T("DB 접속에 실패했습니다.\n응용 프로그램을 시작할 수 없습니다."), MB_OK);
		}
		mysql_set_character_set(&Connect, "euckr");

		

		//Query문
		sprintf_s(Query3, "select * from %s where title like '%%%s%%'", DB_TABLE, Search);
		Query_Status3 = mysql_query(Connection, Query3);
		Sql_Result = mysql_store_result(Connection);
		//Sql_Row = mysql_fetch_row(Sql_Result);
		//리스트콘트롤이 사라졌다가 다시그리면서 데이터 채워넣는 함수
		m_listinfo.DeleteAllItems();

		//현재 컨트롤에 적힌 값을 변수로 넣어 갱신해주는 함수..
		UpdateData(TRUE);


		if (Sql_Result->row_count > 0)
		{
			//Sql_Result->row_count값은 검색한 내용이 있는 리스트 수를 의미
			//for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
			//{
			while((Sql_Rowtitle = mysql_fetch_row(Sql_Result)) != NULL){

				
				//title이란 변수에 Mysql에서 끌어온 1열중 1행을 대입
				title[ROW] = Sql_Rowtitle[0];
				seq_string.Format(_T("%d"), ROW + 1);
				//insertitem함수는 리스트컨트롤에 보일수있게 출력해주는함수
				m_listinfo.InsertItem(ROW, seq_string);
				//SetItemText는 리스트컨트롤에 보일수 있게 출력해주는 함수이나 행과 열을 이용하여 출력
				m_listinfo.SetItemText(ROW, 1, title[ROW]);

				//context_news이란 변수에 Mysql에서 끌어온 1열중 2행을 대입
				context_news[ROW] = Sql_Rowtitle[1];
				m_listinfo.SetItemText(ROW, 2, context_news[ROW]);

				//search_number이란 변수에 Mysql에서 끌어온 1열중 3행을 대입
				search_number[ROW] = Sql_Rowtitle[2];
				m_listinfo.SetItemText(ROW, 3, search_number[ROW]);

				//good_number이란 변수에 Mysql에서 끌어온 1열중 4행을 대입
				good_number[ROW] = Sql_Rowtitle[3];
				m_listinfo.SetItemText(ROW, 4, good_number[ROW]);

				ROW++;
			}
		}
	}

//리스트창에 더블클릭할시 생기는 코드
void Board::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	if (pNMItemActivate->iItem >= 0)
	{
		CString news_context123;
		//더블클릭한 열중 2번째 행? 즉 여기서는 내용을 가져와 news_context123에 넣는다.
		news_context123 = m_listinfo.GetItemText(pNMItemActivate->iItem, 1);
		CString Comment;
		Comment= m_listinfo.GetItemText(pNMItemActivate->iItem, 2);
		CChildDlg dlg;
		//미리 정의해논 SetMainListPtr를 이용하여 신문기사의 내용들을 다음 다이얼로그로 넘긴다.
		dlg.SetMainListPtr(news_context123,ID, Comment);
		dlg.DoModal();
	}
	*pResult = 0;

	*pResult = 0;
}



void Board::OnEnChangeFindnews()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		MessageBox(NULL, _T("DB 접속에 실패했습니다.\n응용 프로그램을 시작할 수 없습니다."), MB_OK);
	}
	mysql_set_character_set(&Connect, "euckr");


	//Query문

	//리스트콘트롤이 사라졌다가 다시그리면서 데이터 채워넣는 함수
	m_listinfo.DeleteAllItems();

	//현재 컨트롤에 적힌 값을 변수로 넣어 갱신해주는 함수..
	UpdateData(TRUE);
	

	GetDlgItemText(IDC_Find_news, Search);

	CString temp;

	this->m_combo.GetLBText(this->m_combo.GetCurSel(), temp);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if ("조회수"== temp) {
		sprintf_s(Query3, "select * from %s where %s like '%%%s%%' ORDER BY search_number DESC", DB_TABLE, "title", Search);
		Query_Status3 = mysql_query(Connection, Query3);
		Sql_Result = mysql_store_result(Connection);

		if (Sql_Result->row_count > 0)
		{
			//Sql_Result->row_count값은 검색한 내용이 있는 리스트 수를 의미
			//for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
			//{
			while ((Sql_Rowtitle = mysql_fetch_row(Sql_Result)) != NULL) {


				//title이란 변수에 Mysql에서 끌어온 1열중 1행을 대입
				title[ROW] = Sql_Rowtitle[0];
				seq_string.Format(_T("%d"), ROW + 1);
				//insertitem함수는 리스트컨트롤에 보일수있게 출력해주는함수
				m_listinfo.InsertItem(ROW, seq_string);
				//SetItemText는 리스트컨트롤에 보일수 있게 출력해주는 함수이나 행과 열을 이용하여 출력
				m_listinfo.SetItemText(ROW, 1, title[ROW]);

				//context_news이란 변수에 Mysql에서 끌어온 1열중 2행을 대입
				context_news[ROW] = Sql_Rowtitle[1];
				m_listinfo.SetItemText(ROW, 2, context_news[ROW]);

				//search_number이란 변수에 Mysql에서 끌어온 1열중 3행을 대입
				search_number[ROW] = Sql_Rowtitle[2];
				m_listinfo.SetItemText(ROW, 3, search_number[ROW]);

				//good_number이란 변수에 Mysql에서 끌어온 1열중 4행을 대입
				good_number[ROW] = Sql_Rowtitle[3];
				m_listinfo.SetItemText(ROW, 4, good_number[ROW]);

				ROW++;
			}
		}
	}
	else if ("추천수" == temp) {
		sprintf_s(Query3, "select * from %s where %s like '%%%s%%' ORDER BY good_number DESC", DB_TABLE, "title", Search);
		Query_Status3 = mysql_query(Connection, Query3);
		Sql_Result = mysql_store_result(Connection);

		if (Sql_Result->row_count > 0)
		{
			//Sql_Result->row_count값은 검색한 내용이 있는 리스트 수를 의미
			//for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
			//{
			while ((Sql_Rowtitle = mysql_fetch_row(Sql_Result)) != NULL) {


				//title이란 변수에 Mysql에서 끌어온 1열중 1행을 대입
				title[ROW] = Sql_Rowtitle[0];
				seq_string.Format(_T("%d"), ROW + 1);
				//insertitem함수는 리스트컨트롤에 보일수있게 출력해주는함수
				m_listinfo.InsertItem(ROW, seq_string);
				//SetItemText는 리스트컨트롤에 보일수 있게 출력해주는 함수이나 행과 열을 이용하여 출력
				m_listinfo.SetItemText(ROW, 1, title[ROW]);

				//context_news이란 변수에 Mysql에서 끌어온 1열중 2행을 대입
				context_news[ROW] = Sql_Rowtitle[1];
				m_listinfo.SetItemText(ROW, 2, context_news[ROW]);

				//search_number이란 변수에 Mysql에서 끌어온 1열중 3행을 대입
				search_number[ROW] = Sql_Rowtitle[2];
				m_listinfo.SetItemText(ROW, 3, search_number[ROW]);

				//good_number이란 변수에 Mysql에서 끌어온 1열중 4행을 대입
				good_number[ROW] = Sql_Rowtitle[3];
				m_listinfo.SetItemText(ROW, 4, good_number[ROW]);

				ROW++;
			}
		}
	}

	else if ("기본" == temp) {
		sprintf_s(Query3, "select * from %s where %s like '%%%s%%'", DB_TABLE, "title", Search);
		Query_Status3 = mysql_query(Connection, Query3);
		Sql_Result = mysql_store_result(Connection);

		if (Sql_Result->row_count > 0)
		{
			//Sql_Result->row_count값은 검색한 내용이 있는 리스트 수를 의미
			//for (ROW = 0; ROW < Sql_Result->row_count; ROW++)
			//{
			while ((Sql_Rowtitle = mysql_fetch_row(Sql_Result)) != NULL) {


				//title이란 변수에 Mysql에서 끌어온 1열중 1행을 대입
				title[ROW] = Sql_Rowtitle[0];
				seq_string.Format(_T("%d"), ROW + 1);
				//insertitem함수는 리스트컨트롤에 보일수있게 출력해주는함수
				m_listinfo.InsertItem(ROW, seq_string);
				//SetItemText는 리스트컨트롤에 보일수 있게 출력해주는 함수이나 행과 열을 이용하여 출력
				m_listinfo.SetItemText(ROW, 1, title[ROW]);

				//context_news이란 변수에 Mysql에서 끌어온 1열중 2행을 대입
				context_news[ROW] = Sql_Rowtitle[1];
				m_listinfo.SetItemText(ROW, 2, context_news[ROW]);

				//search_number이란 변수에 Mysql에서 끌어온 1열중 3행을 대입
				search_number[ROW] = Sql_Rowtitle[2];
				m_listinfo.SetItemText(ROW, 3, search_number[ROW]);

				//good_number이란 변수에 Mysql에서 끌어온 1열중 4행을 대입
				good_number[ROW] = Sql_Rowtitle[3];
				m_listinfo.SetItemText(ROW, 4, good_number[ROW]);

				ROW++;
			}
		}
	}

	

	
}


void Board::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
