
// MtWidgetsDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "MtWidgets.h"
#include "MtWidgetsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <string>


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMtWidgetsDlg 对话框



CMtWidgetsDlg::CMtWidgetsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MTWIDGETS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMtWidgetsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, OpenFile);
	DDX_Control(pDX, IDC_PATH, SHOW_PATH);
	DDX_Control(pDX, IDC_EDIT1, TIME);
	DDX_Control(pDX, IDC_EDIT3, COMMAND);
}

BEGIN_MESSAGE_MAP(CMtWidgetsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMtWidgetsDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CMtWidgetsDlg::OnBnClickedButton4)
//	ON_WM_MOUSEHWHEEL()
ON_WM_MOUSEWHEEL()
ON_STN_CLICKED(SHOW, &CMtWidgetsDlg::OnStnClickedShow)
//ON_WM_MOUSEMOVE()
ON_BN_CLICKED(IDC_BUTTON3, &CMtWidgetsDlg::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BUTTON2, &CMtWidgetsDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON5, &CMtWidgetsDlg::OnBnClickedButton5)
ON_BN_CLICKED(IDC_BUTTON6, &CMtWidgetsDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


LPCTSTR toL(string str) {
	size_t size = str.length();
	wchar_t* buffer = new wchar_t[size+1];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), size+1, buffer, size * sizeof(wchar_t));
	return buffer;
}
// CMtWidgetsDlg 消息处理程序
CDC* pORIDC;
HDC hdc;
BOOL CMtWidgetsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetWindowTextW(toL("Mtmlc微型谱面工具"));
	pORIDC = GetDlgItem(SHOW)->GetDC();
	hdc = pORIDC->GetSafeHdc();
	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMtWidgetsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMtWidgetsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMtWidgetsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMtWidgetsDlg::OnBnClickedButton1()
{
	TCHAR szFilter[] = _T("Mtmlc谱面文件(*.mtmlc)|*.mtmlc|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		MtmlcPath = CT2A(strFilePath.GetBuffer());
		SetDlgItemTextW(IDC_PATH, strFilePath);
		CMtWidgetsDlg::OnBnClickedButton4();
	}
}
void CMtWidgetsDlg::OnBnClickedButton4()
{
	inFile.open(MtmlcPath, ios::in | ios::binary);
	Error = "";
	ReadData(1);
	if (data_i != 1280136269) {
		Error += ("mtmlc格式错误:" + to_string(data_i));
		return;
	}
	MtmlcMean = "##############META##############\n";
	ReadData(1);
	int line_num = data_i;
	MtmlcMean += "判定线数量:" + to_string(data_i) + "\n";
	ReadData(1);
	int note_num = data_i;
	MtmlcMean += "音符数量:" + to_string(data_i) + "\n";
	ReadData(1);
	int command_num = data_i;
	MtmlcMean += "指令数量:" + to_string(data_i) + "\n\n##############LINE##############";
	for (int i = 0; i < line_num; i++)//读取line
	{
		MtmlcMean += "\n判定线" + to_string(i) + ":\n";
		ReadData(2);
		MtmlcMean += "初始高度(y): " + to_string(data_f) + "\n";
		ReadData(2);
		MtmlcMean += "初始透明度: " + to_string(data_f) + "\n";
		ReadData(2);
		MtmlcMean += "初始每秒音符流速: " + to_string(data_f) + "\n";
	}
	MtmlcMean += "\n##############NOTE##############";
	for (UINT ii = 0; ii < note_num; ii++)//读取note
	{
		int  road = 0, deter_ID = 0;
		float begin_time = 0, end_time = 0, begin_road = 0, long_note = 0, devia = 0;
		for (int i = 1; i < 10; i++)
		{
			if (i == 1)
			{
				ReadData(2);
				begin_time = data_f;
			}
			if (i == 2)
			{
				ReadData(2);
				end_time = data_f;
			}
			if (i == 3)
			{
				ReadData(1);
				road = data_i;
			}
			if (i == 4)
			{
				ReadData(2);
				begin_road = data_f;
			}
			if (i == 5)
			{
				ReadData(2);
				devia = data_f;
			}
			if (i == 6)
			{
				ReadData(2);
				long_note = data_f;
			}
			if (i == 7)
			{
				ReadData(1);
				deter_ID = data_i;
			}
			if (i == 8)
			{
				ReadData(1);
				//属性
			}
			if (i == 9)
			{
				MtmlcMean += "\n音符" + to_string(ii) + ":\n";
				MtmlcMean += "起始时间:" + to_string(begin_time) + "\n";
				MtmlcMean += "终止时间:" + to_string(end_time) + "\n";
				MtmlcMean += "判定轨道:" + to_string(road) + "\n";
				MtmlcMean += "初始显示轨道:" + to_string(end_time) + "\n";
				MtmlcMean += "显示位置偏移(+y):" + to_string(devia) + "\n";
				MtmlcMean += "显示长度:" + to_string(long_note) + "\n";
				MtmlcMean += "对应判定线(id):" + to_string(deter_ID) + "\n";
				ReadData(1);
				if (data_i == 0)MtmlcMean += "初始是否激活:False\n";
				else MtmlcMean += "初始是否激活:true\n";

			}
		}
	}
	MtmlcMean += "\n##############CMD##############";
	for (int command_id = 0; command_id < command_num; command_id++) {
		ReadData(2);
		MtmlcMean += "\n\n时间:"+to_string(data_f) + "s\n" + to_string(command_id);
		ReadData(1);
		if (data_i == 0x01)
		{
			ReadData(1);//参数数量，暂时无用
			MtmlcMean += "激活音符:\n";
			ReadData(1);
			MtmlcMean += "ID: " + to_string(data_i);
		}
		else if (data_i == 0x00)
		{
			ReadData(1);//参数数量，暂时无用
			MtmlcMean += "播放音乐:\n";
			ReadData(2);
			MtmlcMean += "音乐起始时间: " + to_string(data_f);
		}
		else if (data_i == 0x02)
		{
			ReadData(1);//参数数量，暂时无用
			MtmlcMean += "更改音符轨道函数( val=kx+b ):\n";
			ReadData(1);
			MtmlcMean += "音符ID: " + to_string(data_i)+"\n";
			ReadData(2);
			MtmlcMean += "k = " + to_string(data_f) + "\n";
			ReadData(2);
			MtmlcMean += "b = " + to_string(data_f);
		}
		else if (data_i == 0x03)
		{
			ReadData(1);//参数数量，暂时无用
			MtmlcMean += "更改音符轨道函数( val=A*sin(wx+q)+b ):\n";
			ReadData(1);
			MtmlcMean += "音符ID: " + to_string(data_i) + "\n";
			ReadData(2);
			MtmlcMean += "A = " + to_string(data_f) + "\n";
			ReadData(2);
			MtmlcMean += "w = " + to_string(data_f) + "\n";
			ReadData(2);
			MtmlcMean += "q = " + to_string(data_f) + "\n";
			ReadData(2);
			MtmlcMean += "b = " + to_string(data_f);
		}
		else if (data_i == 0x11)
		{
			ReadData(1);//参数数量，暂时无用
			MtmlcMean += "更改判定线透明度函数( val=kx+b ):\n";
			ReadData(1);
			MtmlcMean += "判定线ID: " + to_string(data_i) + "\n";
			ReadData(2);
			MtmlcMean += "k = " + to_string(data_f) + "\n";
			ReadData(2);
			MtmlcMean += "b = " + to_string(data_f);
		}
		else if (data_i == 0x12)
		{
			ReadData(1);//参数数量，暂时无用
			MtmlcMean += "更改判定线透明度函数( val=A*sin(wx+q)+b ):\n";
			ReadData(1);
			MtmlcMean += "音符ID: " + to_string(data_i) + "\n";
			ReadData(2);
			MtmlcMean += "A = " + to_string(data_f) + "\n";
			ReadData(2);
			MtmlcMean += "w = " + to_string(data_f) + "\n";
			ReadData(2);
			MtmlcMean += "q = " + to_string(data_f) + "\n";
			ReadData(2);
			MtmlcMean += "b = " + to_string(data_f);
		}
		else if (data_i == 0x13)
		{
			ReadData(1);//参数数量，暂时无用
			MtmlcMean += "更改判定线位置函数( val=kx+b ):\n";
			ReadData(1);
			MtmlcMean += "判定线ID: " + to_string(data_i) + "\n";
			ReadData(2);
			MtmlcMean += "k = " + to_string(data_f) + "\n";
			ReadData(2);
			MtmlcMean += "b = " + to_string(data_f);
		}
		else if (data_i == 0x14)
		{
			ReadData(1);//参数数量，暂时无用
			MtmlcMean += "更改判定线位置函数函数( val=A*sin(wx+q)+b ):\n";
			ReadData(1);
			MtmlcMean += "判定线ID: " + to_string(data_i) + "\n";
			ReadData(2);
			MtmlcMean += "A = " + to_string(data_f) + "\n";
			ReadData(2);
			MtmlcMean += "w = " + to_string(data_f) + "\n";
			ReadData(2);
			MtmlcMean += "q = " + to_string(data_f) + "\n";
			ReadData(2);
			MtmlcMean += "b = " + to_string(data_f);
		}
		else if (data_i == 0x15)
		{
			ReadData(1);//参数数量，暂时无用
			MtmlcMean += "更改音符流动函数( val=kx+b ):\n";
			ReadData(1);
			MtmlcMean += "音符ID: " + to_string(data_i) + "\n";
			ReadData(2);
			MtmlcMean += "k = " + to_string(data_f) + "\n";
			ReadData(2);
			MtmlcMean += "b = " + to_string(data_f);
		}
	}
		inFile.close();
	row = 0;
	high = 0;
	for (int i = 0; i < MtmlcMean.length(); i++) {
		if (MtmlcMean[i] == '\n') {
			high++;
		}
	}
	// READ END
	if (Error == "")SetDlgItemTextW(SHOW, toL(MtmlcMean));
	else SetDlgItemTextW(SHOW, toL(Error));
	GetDlgItem(SHOW)->SetFocus();
}
string textHigh(string text, int y) {
	string temp="", over="";
	int line = 0;
	for (int i = 0; i < text.length(); i++) {
		temp += text[i];
		if (text[i] == '\n') {
			line++;
			if (line >= y)over += temp;
			temp = "";
		}
	}
	over += temp;
	return over;
}
bool inSHOW = false;

void CMtWidgetsDlg::OnStnClickedShow()
{
	//SetFocus();
	// TODO: 在此添加控件通知处理程序代码
}


//void CMtWidgetsDlg::OnMouseMove(UINT nFlags, CPoint point)
//{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//}


BOOL CMtWidgetsDlg::PreTranslateMessage(MSG* pMsg)
{

	UINT btnID;

	//由窗口句柄获得控件ID号，GetWindowLong为获得窗口的ID号。 
	btnID = GetWindowLong(pMsg->hwnd, GWL_ID);

	int zDelta = (short)HIWORD(pMsg->wParam);


	switch (pMsg->message)
	{
	case WM_MOUSEWHEEL:
	{
		if (true)
		{
			if (zDelta < 0) {
				row-=zDelta/120;
				if (row >= high)row = high;
				SetDlgItemTextW(SHOW, toL(textHigh(MtmlcMean, row)));
			}
			else {
				row-= zDelta / 120;
				if (row < 0)row = 0;
				SetDlgItemTextW(SHOW, toL(textHigh(MtmlcMean, row)));
			}
		}
	}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMtWidgetsDlg::OnBnClickedButton3()
{
	TCHAR szFilter[] = _T("保存为(*.McLog)|*.McLog|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{ 
		strFilePath = fileDlg.GetPathName();
		ofstream fss( CT2A(strFilePath.GetBuffer()));
		fss << MtmlcMean;
		fss.close();
		system(("notepad "+(string)CT2A(strFilePath.GetBuffer())).data());
	}
	// TODO: 在此添加控件通知处理程序代码
}
#include<sstream>

template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}

void CMtWidgetsDlg::OnBnClickedButton2()
{
	CString temp,error;
	string stime, command;
	GetDlgItemTextW(IDC_EDIT1, temp);
	stime = CT2A(temp.GetBuffer());
	GetDlgItemTextW(IDC_EDIT3, temp);
	command = CT2A(temp.GetBuffer());
	command += " ";
	SetDlgItemTextW(SHOW, toL(""));
	GetDlgItemTextW(IDC_EDIT3, error);
	try {
		float time = stringToNum<float>(stime);
		string temp;
		temp = "";
		int i = 0;
		for (; command[i] != ' '; i++) {
			temp += command[i];
		}
		i++;
		int mode = stringToNum<int>(temp),datai=0;
		float dataf=0;
		if (mode != 0x00 && mode != 0x01 && mode != 0x02 && mode != 0x03 && mode != 0x11 && mode != 0x12 && mode != 0x013 && mode != 0x14 && mode != 0x15) {
			throw -1;
		}
		temp = "";
		string MessageB = "";
		if (mode == 0x01)
		{
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			temp = "";
			MessageB += "激活音符:\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			datai = stringToNum<int>(temp);
			temp = "";
			MessageB += "ID: " + to_string(datai);
		}
		else if (mode == 0x00)
		{
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			temp = "";
			MessageB += "播放音乐:\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "音乐起始时间: " + to_string(dataf);
		}
		else if (mode == 0x02)
		{
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			temp = "";
			MessageB += "更改音符轨道函数( val=kx+b ):\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			datai = stringToNum<int>(temp);
			temp = "";
			MessageB += "音符ID: " + to_string(datai) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "k = " + to_string(dataf) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "b = " + to_string(dataf);
		}
		else if (mode == 0x03)
		{
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			temp = "";
			MessageB += "更改音符轨道函数( val=A*sin(wx+q)+b ):\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			datai = stringToNum<int>(temp);
			temp = "";
			MessageB += "音符ID: " + to_string(datai) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "A = " + to_string(dataf) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "w = " + to_string(dataf) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "q = " + to_string(dataf) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "b = " + to_string(dataf);
		}
		else if (mode == 0x11)
		{
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			temp = "";
			MessageB += "更改判定线透明度函数( val=kx+b ):\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			datai = stringToNum<int>(temp);
			temp = "";
			MessageB += "判定线ID: " + to_string(datai) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "k = " + to_string(dataf) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "b = " + to_string(dataf);
		}
		else if (mode == 0x12)
		{
		for (; command[i] != ' '; i++) {
				temp += command[i];
			}
		i++;
			temp = "";
			MessageB += "更改判定线透明度函数( val=A*sin(wx+q)+b ):\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			datai = stringToNum<int>(temp);
			temp = "";
			MessageB += "音符ID: " + to_string(datai) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "A = " + to_string(dataf) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "w = " + to_string(dataf) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "q = " + to_string(dataf) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "b = " + to_string(dataf);
		}
		else if (mode == 0x13)
		{
		for (; command[i] != ' '; i++) {
				temp += command[i];
			}
		i++;
			temp = "";
			MessageB += "更改判定线位置函数( val=kx+b ):\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			datai = stringToNum<int>(temp);
			temp = "";
			MessageB += "判定线ID: " + to_string(datai) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "k = " + to_string(dataf) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "b = " + to_string(dataf);
		}
		else if (mode == 0x14)
		{
		for (; command[i] != ' '; i++) {
				temp += command[i];
			}
		i++;
			temp = "";
			MessageB += "更改判定线位置函数函数( val=A*sin(wx+q)+b ):\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			datai = stringToNum<int>(temp);
			temp = "";
			MessageB += "判定线ID: " + to_string(datai) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "A = " + to_string(dataf) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "w = " + to_string(dataf) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "q = " + to_string(dataf) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "b = " + to_string(dataf);
		}
		else if (mode == 0x15)
		{
		for (; command[i] != ' '; i++) {
				temp += command[i];
			}
		i++;
			temp = "";
			MessageB += "更改音符流动函数( val=kx+b ):\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			datai = stringToNum<int>(temp);
			temp = "";
			MessageB += "音符ID: " + to_string(datai) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "k = " + to_string(dataf) + "\n";
			for (; command[i] != ' '; i++) {
				temp += command[i];
			}
			i++;
			dataf = stringToNum<float>(temp);
			temp = "";
			MessageB += "b = " + to_string(dataf);
		}
		buffer = stime+" " + command+" ";
		SetDlgItemTextW(SHOW, toL((string)MessageB+"\n铺面更新已加入缓冲区\n"));
	}
	catch (...) {
		GetDlgItemTextW(IDC_EDIT3, error);
		SetDlgItemTextW(SHOW, toL((string)CT2A(error.GetBuffer()) +"语句插入错误!请检查您的语句是否正确!\n"));
	}
	// TODO: 在此添加控件通知处理程序代码
}

string insert(string& in, string sert, int pos) {
	string front,end;
	for (int i = 0; i < in.length(); i++) {
		if (i < pos)front += in[i];
		else end += in[i];
	}
	return (front + sert + end);
}

void CMtWidgetsDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	CMtWidgetsDlg::OnBnClickedButton2();
	//CDialogEx::OnOK();
}


void CMtWidgetsDlg::OnBnClickedButton5()
{
	TCHAR szFilter[] = _T("保存为(*.Mtmlc)|*.mtmlc|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;
	if (buffer == "")SetDlgItemTextW(SHOW, toL("缓冲区为空!"));
	else {
		// 显示打开文件对话框   
		if (IDOK == fileDlg.DoModal())
		{
			strFilePath = fileDlg.GetPathName();
			inFile.close();
			fstream fss(CT2A(strFilePath.GetBuffer()), ios::binary | ios::out);
			inFile.open(MtmlcPath, ios::in | ios::binary);
			Error = "";
			ReadData(1);
			fss.write(reinterpret_cast<char*>(&data_i), sizeof(&data_i));
			if (data_i != 1280136269) {
				Error += ("mtmlc格式错误:" + to_string(data_i));
				return;
			}
			MtmlcMean = "##############META##############\n";
			ReadData(1);
			fss.write(reinterpret_cast<char*>(&data_i), sizeof(data_i));
			int line_num = data_i;
			MtmlcMean += "判定线数量:" + to_string(data_i) + "\n";
			ReadData(1);
			fss.write(reinterpret_cast<char*>(&data_i), sizeof(data_i));
			int note_num = data_i;
			MtmlcMean += "音符数量:" + to_string(data_i) + "\n";
			ReadData(1);
			int ti;
			ti = data_i + 1;
			fss.write((const char*)(&ti), sizeof(data_i+1));
			int command_num = data_i;
			MtmlcMean += "指令数量:" + to_string(data_i) + "\n\n##############LINE##############";
			for (int i = 0; i < line_num; i++)//读取line
			{
				MtmlcMean += "\n判定线" + to_string(i) + ":\n";
				ReadData(2);
				fss.write((const char*)(&data_f), sizeof(data_f));
				MtmlcMean += "初始高度(y): " + to_string(data_f) + "\n";
				ReadData(2);
				fss.write((const char*)(&data_f), sizeof(data_f));
				MtmlcMean += "初始透明度: " + to_string(data_f) + "\n";
				ReadData(2);
				fss.write((const char*)(&data_f), sizeof(data_f));
				MtmlcMean += "初始每秒音符流速: " + to_string(data_f) + "\n";
			}
			MtmlcMean += "\n##############NOTE##############";
			for (UINT ii = 0; ii < note_num; ii++)//读取note
			{
				int  road = 0, deter_ID = 0;
				float begin_time = 0, end_time = 0, begin_road = 0, long_note = 0, devia = 0;
				for (int i = 1; i < 10; i++)
				{
					if (i == 1)
					{
						ReadData(2);
						begin_time = data_f;
						fss.write((const char*)(&data_f), sizeof(data_f));
					}
					if (i == 2)
					{
						ReadData(2);
						end_time = data_f;
						fss.write((const char*)(&data_f), sizeof(data_f));
					}
					if (i == 3)
					{
						ReadData(1);
						road = data_i;
						fss.write((const char*)(&data_i), sizeof(data_i));
					}
					if (i == 4)
					{
						ReadData(2);
						begin_road = data_f;
						fss.write((const char*)(&data_f), sizeof(data_f));
					}
					if (i == 5)
					{
						ReadData(2);
						devia = data_f;
						fss.write((const char*)(&data_f), sizeof(data_f));
					}
					if (i == 6)
					{
						ReadData(2);
						long_note = data_f;
						fss.write((const char*)(&data_f), sizeof(data_f));
					}
					if (i == 7)
					{
						ReadData(1);
						deter_ID = data_i;
						fss.write((const char*)(&data_i), sizeof(data_i));
					}
					if (i == 8)
					{
						ReadData(1);
						fss.write((const char*)(&data_i), sizeof(data_i));
						//属性
					}
					if (i == 9)
					{
						ReadData(1);
						fss.write((const char*)(&data_i), sizeof(data_i));

					}
				}
			}
			bool needi = true;
			for (int command_id = 0; command_id < command_num; command_id++) {
				ReadData(2);
				int i = 0;
				string temp = "";
				for (; buffer[i] != ' '; i++) {
					temp += buffer[i];
				}
				i++;
				if(data_f>=(stringToNum<float>(temp)) && needi) {
					needi = false;
					float t = stringToNum<float>(temp);
					fss.write((const char*)(&t), sizeof(t));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					data_i = stringToNum<int>(temp);
					fss.write((const char*)(&data_i), sizeof(data_i));
					if (data_i == 0x01)
					{
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						ti = stringToNum<int>(temp);
						fss.write((const char*)(&ti), sizeof(ti));
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						ti = stringToNum<int>(temp);
						fss.write((const char*)(&ti), sizeof(ti));
					}
					else if (data_i == 0x00)
					{
					MessageBoxA(NULL, LPCSTR(to_string(data_i).c_str()), LPCSTR("a"), MB_OK);
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						ti = stringToNum<int>(temp);
						fss.write((const char*)(&ti), sizeof(ti));
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						t = stringToNum<float>(temp);
						fss.write((const char*)(&t), sizeof(t));
					}
					else if (data_i == 0x02)
					{
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						ti = stringToNum<int>(temp);
						fss.write((const char*)(&ti), sizeof(ti));
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						ti = stringToNum<int>(temp);
						fss.write((const char*)(&ti), sizeof(ti));
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						t = stringToNum<float>(temp);
						fss.write((const char*)(&t), sizeof(t));
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						t = stringToNum<float>(temp);
						fss.write((const char*)(&t), sizeof(t));
					}
					else if (data_i == 0x03)
					{
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						ti = stringToNum<int>(temp);
						fss.write((const char*)(&ti), sizeof(ti));
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						ti = stringToNum<int>(temp);
						fss.write((const char*)(&ti), sizeof(ti));
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						t = stringToNum<float>(temp);
						fss.write((const char*)(&t), sizeof(t));
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						t = stringToNum<float>(temp);
						fss.write((const char*)(&t), sizeof(t));
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						t = stringToNum<float>(temp);
						fss.write((const char*)(&t), sizeof(t));
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						t = stringToNum<float>(temp);
						fss.write((const char*)(&t), sizeof(t));
					}
					else if (data_i == 0x11)
					{
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						ti = stringToNum<int>(temp);
						fss.write((const char*)(&ti), sizeof(ti));
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						ti = stringToNum<int>(temp);
						fss.write((const char*)(&ti), sizeof(ti));
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						t = stringToNum<float>(temp);
						fss.write((const char*)(&t), sizeof(t));
						for (; buffer[i] != ' '; i++) {
							temp += buffer[i];
						}
						i++;
						t = stringToNum<float>(temp);
						fss.write((const char*)(&t), sizeof(t));
					}
					else if (data_i == 0x12)
					{
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					ti = stringToNum<int>(temp);
					fss.write((const char*)(&ti), sizeof(ti));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					ti = stringToNum<int>(temp);
					fss.write((const char*)(&ti), sizeof(ti));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					t = stringToNum<float>(temp);
					fss.write((const char*)(&t), sizeof(t));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					t = stringToNum<float>(temp);
					fss.write((const char*)(&t), sizeof(t));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					t = stringToNum<float>(temp);
					fss.write((const char*)(&t), sizeof(t));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					t = stringToNum<float>(temp);
					fss.write((const char*)(&t), sizeof(t));
					}
					else if (data_i == 0x13)
					{
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					ti = stringToNum<int>(temp);
					fss.write((const char*)(&ti), sizeof(ti));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					ti = stringToNum<int>(temp);
					fss.write((const char*)(&ti), sizeof(ti));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					t = stringToNum<float>(temp);
					fss.write((const char*)(&t), sizeof(t));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					t = stringToNum<float>(temp);
					fss.write((const char*)(&t), sizeof(t));
					}
					else if (data_i == 0x14)
					{
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					ti = stringToNum<int>(temp);
					fss.write((const char*)(&ti), sizeof(ti));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					ti = stringToNum<int>(temp);
					fss.write((const char*)(&ti), sizeof(ti));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					t = stringToNum<float>(temp);
					fss.write((const char*)(&t), sizeof(t));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					t = stringToNum<float>(temp);
					fss.write((const char*)(&t), sizeof(t));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					t = stringToNum<float>(temp);
					fss.write((const char*)(&t), sizeof(t));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					t = stringToNum<float>(temp);
					fss.write((const char*)(&t), sizeof(t));
					}
					else if (data_i == 0x15)
					{
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					ti = stringToNum<int>(temp);
					fss.write((const char*)(&ti), sizeof(ti));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					ti = stringToNum<int>(temp);
					fss.write((const char*)(&ti), sizeof(ti));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					t = stringToNum<float>(temp);
					fss.write((const char*)(&t), sizeof(t));
					for (; buffer[i] != ' '; i++) {
						temp += buffer[i];
					}
					i++;
					t = stringToNum<float>(temp);
					fss.write((const char*)(&t), sizeof(t));
					}
				}
				fss.write((const char*)(&data_f), sizeof(data_f));
				MtmlcMean += "\n\n时间:" + to_string(data_f) + "s\n" + to_string(command_id);
				ReadData(1);
				fss.write((const char*)(&data_i), sizeof(data_i));
				if (data_i == 0x01)
				{
					ReadData(1);//参数数量，暂时无用
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(1);
					fss.write((const char*)(&data_i), sizeof(data_i));
				}
				else if (data_i == 0x00)
				{
					ReadData(1);//参数数量，暂时无用
					fss.write((const char*)(&data_i), sizeof(data_i));
					MtmlcMean += "播放音乐:\n";
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
				}
				else if (data_i == 0x02)
				{
					ReadData(1);//参数数量，暂时无用
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(1);
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
				}
				else if (data_i == 0x03)
				{
					ReadData(1);//参数数量，暂时无用
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(1);
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
				}
				else if (data_i == 0x11)
				{
					ReadData(1);//参数数量，暂时无用
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(1);
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
				}
				else if (data_i == 0x12)
				{
					ReadData(1);//参数数量，暂时无用
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(1);
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
				}
				else if (data_i == 0x13)
				{
					ReadData(1);//参数数量，暂时无用
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(1);
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
				}
				else if (data_i == 0x14)
				{
					ReadData(1);//参数数量，暂时无用
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(1);
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
				}
				else if (data_i == 0x15)
				{
					ReadData(1);//参数数量，暂时无用
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(1);
					fss.write((const char*)(&data_i), sizeof(data_i));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
					ReadData(2);
					fss.write((const char*)(&data_f), sizeof(data_f));
				}
			}
			inFile.close();
			fss.close();
		}
	}

	// TODO: 在此添加控件通知处理程序代码
}

#include"CHelp.h"
void CMtWidgetsDlg::OnBnClickedButton6()
{
	CHelp dlg;
	dlg.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}
