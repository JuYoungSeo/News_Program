#pragma once


// context ��ȭ �����Դϴ�.

class context : public CDialogEx
{
	DECLARE_DYNAMIC(context)

public:
	context(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~context();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
};
