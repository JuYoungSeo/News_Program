// context.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "News.h"
#include "context.h"
#include "afxdialogex.h"


// context ��ȭ �����Դϴ�.

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


// context �޽��� ó�����Դϴ�.

