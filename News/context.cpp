// context.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "News.h"
#include "context.h"
#include "afxdialogex.h"


// context 대화 상자입니다.

IMPLEMENT_DYNAMIC(context, CDialogEx)

context::context(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

context::~context()
{
}

void context::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(context, CDialogEx)
END_MESSAGE_MAP()


// context 메시지 처리기입니다.

