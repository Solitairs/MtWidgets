
// MtWidgetsDlg.h: 头文件
//

#pragma once

#include<iostream>
#include <fstream>
using namespace std;
// CMtWidgetsDlg 对话框
class CMtWidgetsDlg : public CDialogEx
{
// 构造
public:
	CMtWidgetsDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MTWIDGETS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton OpenFile;
	CFont cfont;
	CStatic SHOW_PATH;
	fstream inFile;
	string MtmlcPath="", MtmlcMean="",Error,buffer;
	float data_f;
	UINT data_u;
	int data_i,row=0,high=0;
	void ReadData(UINT mode) {
		if (mode == 1) {
			//int
			inFile.read((char*)&data_i, sizeof(data_i));
		}
		else if (mode == 2) {
			//float
			inFile.read((char*)&data_f, sizeof(data_f));
		}
	}
	afx_msg void OnBnClickedButton4();
	afx_msg void OnStnClickedShow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	CEdit TIME;
	CEdit COMMAND;
	virtual void OnOK();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
