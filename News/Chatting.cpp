// Chatting.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#define _WINSOCK_DEPRRECATED_NO_WARNINGS

#include "News.h"
#include "Chatting.h"
#include "afxdialogex.h"

#include <winsock2.h>

Chatting *gg;
SOCKET socket_client;
DWORD WINAPI SendThread(LPVOID lpData);
DWORD WINAPI ReceiveThread(LPVOID lpData);
// Chatting 대화 상자입니다.

IMPLEMENT_DYNAMIC(Chatting, CDialogEx)

Chatting::Chatting(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG6, pParent)
{

}

Chatting::~Chatting()
{
}

void Chatting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_List1);
	DDX_Control(pDX, IDC_Picture, m_imgBg);
}


BEGIN_MESSAGE_MAP(Chatting, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Chatting::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Chatting::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Chatting 메시지 처리기입니다.


BOOL Chatting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HBITMAP hBit = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8));
	m_imgBg.SetBitmap(hBit);
	CRect rt;
	GetClientRect(&rt);
	m_imgBg.SetWindowPos(NULL,0, 0, rt.Width(), rt.Height(), SWP_SHOWWINDOW);
	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	gg = this;
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	WSADATA wsaData;
	int token = WSAStartup(WINSOCK_VERSION, &wsaData);
	char PORT[5], IP[15];

	// 소켓 생성
	SOCKET socket_client = socket(AF_INET, SOCK_STREAM, 0);

	// 소켓 주소 정보
	SOCKADDR_IN servAddr = { 0 };
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(10000); // 포트

									  // 소켓 접속
	if (connect(socket_client, (struct sockaddr *) &servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		closesocket(socket_client);
		printf("서버에 접속 할수 없습니다.");
		return SOCKET_ERROR;
	}

	//CreateThread(NULL, 0, SendThread, (LPVOID)socket_client, 0, NULL);
	CreateThread(NULL, 0, ReceiveThread, (LPVOID)socket_client, 0, NULL);
	// 상태 출력
	DWORD dwTmp;
	char text[1024] = "서버에 접속되었습니다.\n";
	recv(socket_client, text, sizeof(text), 0);
	AfxMessageBox(_T(text));

	

	/*
	while (1)
	{
		char buffer[1024] = { 0 };
		int len = recv(socket_client, buffer, sizeof(buffer), 0);
		if (len <= 0)
		{
			printf("접속 종료.");
			break;
		}

		// 메시지 출력
		//WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), &dwTmp, NULL);
		UpdateData();
		m_List1.AddString(buffer);

	}*/
	//소켓 해제
	//closesocket(socket_client);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
/*
DWORD WINAPI SendThread(LPVOID lpData)
{
	socket_client = (SOCKET)lpData;
	while (1)
	{
		printf("전송할 내용 : ");
		DWORD dwTmp;
		char text[1024] = { 0 };
		ReadFile(GetStdHandle(STD_INPUT_HANDLE), text, 1024, &dwTmp, NULL);
		send(socket_client, text, strlen(text), 0);
	}
	return 0;
}*/

DWORD WINAPI ReceiveThread(LPVOID lpData)
{
	socket_client = (SOCKET)lpData;
	char buffer1[1024] = { 0 };

	while (1)
	{
		char buffer[1024] = { 0 };
		int len = recv(socket_client, buffer, sizeof(buffer), 0);
		if (len <= 0)
		{
			printf("접속 종료.");
			break;
		}

		// 메시지 출력
		//WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), &dwTmp, NULL);
		Chatting *ab = gg;

		ab->m_List1.AddString(buffer);

	}
	closesocket(socket_client);

	return 0;
}

void Chatting::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString text = "";
	GetDlgItemText(IDC_Send_Message, text);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	send(socket_client, text, strlen(text), 0);
	UpdateData();
	int index=  m_List1.AddString(text);
	m_List1.SetCurSel(index);
}


void Chatting::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*
	WSADATA wsaData;
	int token = WSAStartup(WINSOCK_VERSION, &wsaData);
	char PORT[5], IP[15];

	// 소켓 생성
	SOCKET socket_client = socket(AF_INET, SOCK_STREAM, 0);

	// 소켓 주소 정보
	SOCKADDR_IN servAddr = { 0 };
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(10000); // 포트

									  // 소켓 접속
	if (connect(socket_client, (struct sockaddr *) &servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		closesocket(socket_client);
		printf("서버에 접속 할수 없습니다.");
	}

	CreateThread(NULL, 0, SendThread, (LPVOID)socket_client, 0, NULL);
	// 상태 출력
	DWORD dwTmp;
	char text[1024] = "서버에 접속되었습니다.\n";
	//WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), text, strlen(text), &dwTmp, NULL);

	while (1)
	{
		char buffer[1024] = { 0 };
		int len = recv(socket_client, buffer, sizeof(buffer), 0);
		if (len <= 0)
		{
			printf("접속 종료.");
			break;
		}

		// 메시지 출력
		//WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), &dwTmp, NULL);
		UpdateData();
		m_List1.AddString(buffer);

	}
	//소켓 해제
	closesocket(socket_client);
	*/
}


HBRUSH Chatting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
	{
		if (pWnd->GetDlgCtrlID() == IDC_LIST2)
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}

	}
	}
	return hbr;
}
