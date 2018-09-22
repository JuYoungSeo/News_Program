// Chatting.cpp : ���� �����Դϴ�.
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
// Chatting ��ȭ �����Դϴ�.

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


// Chatting �޽��� ó�����Դϴ�.


BOOL Chatting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HBITMAP hBit = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP8));
	m_imgBg.SetBitmap(hBit);
	CRect rt;
	GetClientRect(&rt);
	m_imgBg.SetWindowPos(NULL,0, 0, rt.Width(), rt.Height(), SWP_SHOWWINDOW);
	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	gg = this;
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	WSADATA wsaData;
	int token = WSAStartup(WINSOCK_VERSION, &wsaData);
	char PORT[5], IP[15];

	// ���� ����
	SOCKET socket_client = socket(AF_INET, SOCK_STREAM, 0);

	// ���� �ּ� ����
	SOCKADDR_IN servAddr = { 0 };
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(10000); // ��Ʈ

									  // ���� ����
	if (connect(socket_client, (struct sockaddr *) &servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		closesocket(socket_client);
		printf("������ ���� �Ҽ� �����ϴ�.");
		return SOCKET_ERROR;
	}

	//CreateThread(NULL, 0, SendThread, (LPVOID)socket_client, 0, NULL);
	CreateThread(NULL, 0, ReceiveThread, (LPVOID)socket_client, 0, NULL);
	// ���� ���
	DWORD dwTmp;
	char text[1024] = "������ ���ӵǾ����ϴ�.\n";
	recv(socket_client, text, sizeof(text), 0);
	AfxMessageBox(_T(text));

	

	/*
	while (1)
	{
		char buffer[1024] = { 0 };
		int len = recv(socket_client, buffer, sizeof(buffer), 0);
		if (len <= 0)
		{
			printf("���� ����.");
			break;
		}

		// �޽��� ���
		//WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), &dwTmp, NULL);
		UpdateData();
		m_List1.AddString(buffer);

	}*/
	//���� ����
	//closesocket(socket_client);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
/*
DWORD WINAPI SendThread(LPVOID lpData)
{
	socket_client = (SOCKET)lpData;
	while (1)
	{
		printf("������ ���� : ");
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
			printf("���� ����.");
			break;
		}

		// �޽��� ���
		//WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), &dwTmp, NULL);
		Chatting *ab = gg;

		ab->m_List1.AddString(buffer);

	}
	closesocket(socket_client);

	return 0;
}

void Chatting::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString text = "";
	GetDlgItemText(IDC_Send_Message, text);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	send(socket_client, text, strlen(text), 0);
	UpdateData();
	int index=  m_List1.AddString(text);
	m_List1.SetCurSel(index);
}


void Chatting::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	/*
	WSADATA wsaData;
	int token = WSAStartup(WINSOCK_VERSION, &wsaData);
	char PORT[5], IP[15];

	// ���� ����
	SOCKET socket_client = socket(AF_INET, SOCK_STREAM, 0);

	// ���� �ּ� ����
	SOCKADDR_IN servAddr = { 0 };
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(10000); // ��Ʈ

									  // ���� ����
	if (connect(socket_client, (struct sockaddr *) &servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		closesocket(socket_client);
		printf("������ ���� �Ҽ� �����ϴ�.");
	}

	CreateThread(NULL, 0, SendThread, (LPVOID)socket_client, 0, NULL);
	// ���� ���
	DWORD dwTmp;
	char text[1024] = "������ ���ӵǾ����ϴ�.\n";
	//WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), text, strlen(text), &dwTmp, NULL);

	while (1)
	{
		char buffer[1024] = { 0 };
		int len = recv(socket_client, buffer, sizeof(buffer), 0);
		if (len <= 0)
		{
			printf("���� ����.");
			break;
		}

		// �޽��� ���
		//WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), &dwTmp, NULL);
		UpdateData();
		m_List1.AddString(buffer);

	}
	//���� ����
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
