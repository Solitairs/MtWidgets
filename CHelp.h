﻿#pragma once
#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "MtWidgets.h"
#include "MtWidgetsDlg.h"
#include "afxdialogex.h"

// CHelp 对话框

class CHelp : public  CDialogEx
{
	DECLARE_DYNAMIC(CHelp)

public:
	CHelp(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHelp();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
