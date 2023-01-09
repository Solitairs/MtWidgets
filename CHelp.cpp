// CHelp.cpp: 实现文件
//

#include "pch.h"
#include "MtWidgets.h"
#include "afxdialogex.h"
#include "CHelp.h"


// CHelp 对话框

IMPLEMENT_DYNAMIC(CHelp, CDialogEx)

CHelp::CHelp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CHelp::~CHelp()
{
}

void CHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelp, CDialogEx)
END_MESSAGE_MAP()


// CHelp 消息处理程序


BOOL CHelp::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	string str = "MtWidgets帮助文档";
	size_t size = str.length();
	wchar_t* buffer = new wchar_t[size + 1];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), size + 1, buffer, size * sizeof(wchar_t));
	// TODO:  在此添加额外的初始化
	SetWindowTextW(buffer);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
