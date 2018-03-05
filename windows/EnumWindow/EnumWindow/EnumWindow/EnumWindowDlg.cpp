
// EnumWindowDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EnumWindow.h"
#include "EnumWindowDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEnumWindowDlg 对话框



CEnumWindowDlg::CEnumWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ENUMWINDOW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnumWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEnumWindowDlg::OnPaint()
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
HCURSOR CEnumWindowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BEGIN_MESSAGE_MAP(CEnumWindowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ENUM, &CEnumWindowDlg::OnBnClickedEnum)
	ON_BN_CLICKED(IDC_FIND, &CEnumWindowDlg::OnBnClickedFind)
	ON_BN_CLICKED(IDC_FIND_MSG, &CEnumWindowDlg::OnBnClickedFindMsg)
	ON_BN_CLICKED(ID_EXIT, &CEnumWindowDlg::OnBnClickedExit)
END_MESSAGE_MAP()

BOOL CALLBACK EnumChildWindowsProc(HWND hwnd, LPARAM lParam)
{
	CEnumWindowDlg * pParent = (CEnumWindowDlg*)lParam;
	TCHAR title[MAX_PATH] = { 0 };
	if (GetWindowText(hwnd, title, sizeof(title)) > 0)
	{
		CString s;
		int pos = pParent->m_list.GetItemCount();
		s.Format(_T("%d"), pos);
		pParent->m_list.InsertItem(pos, s);
		s.Format(_T("%p"), hwnd);
		pParent->m_list.SetItemText(pos, 1, s);
		pParent->m_list.SetItemText(pos, 2, CString(title));
	}
	return true;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	CEnumWindowDlg * pParent = (CEnumWindowDlg*)lParam;
	TCHAR title[MAX_PATH] = { 0 };
	if (GetWindowText(hwnd, title, sizeof(title)))
	{
		CString s;
		int pos = pParent->m_list.GetItemCount();
		s.Format(_T("%d"), pos);
		pParent->m_list.InsertItem(pos, s);
		s.Format(_T("%p"), hwnd);
		pParent->m_list.SetItemText(pos, 1, s);
		pParent->m_list.SetItemText(pos, 2, CString(title));
	}
	EnumChildWindows(hwnd, EnumChildWindowsProc, lParam);
	return true;
}

BOOL CEnumWindowDlg::myEnumWindow(HWND hwnd)
{
	TCHAR title[MAX_PATH] = { 0 };
	HWND after = NULL;
	while (after = ::FindWindowEx(hwnd, after, NULL, NULL))
	{
		if (::GetWindowText(after, title, sizeof(title)) > 0)
		{
			CString s;
			int pos = m_list.GetItemCount();
			s.Format(_T("%d"), pos);
			m_list.InsertItem(pos, s);
			s.Format(_T("%p"), after);
			m_list.SetItemText(pos, 1, s);
			m_list.SetItemText(pos, 2, CString(title));
		}
		myEnumWindow(after);
	}
	return true;
}

// CEnumWindowDlg 消息处理程序
BOOL CEnumWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_list.SetExtendedStyle(m_list.GetStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rect;
	GetWindowRect(&rect);
	m_list.InsertColumn(0, _T("序号"), LVCFMT_LEFT, rect.Width() / 8, 0);
	m_list.InsertColumn(1, _T("句柄"), LVCFMT_LEFT, rect.Width() / 4, 1);
	m_list.InsertColumn(2, _T("窗口名"), LVCFMT_LEFT, 5 * rect.Width() / 8, 2);
	((CButton*)GetDlgItem(IDC_ENUM))->SetCheck(TRUE);
	EnumWindows(EnumWindowsProc, (LPARAM)this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEnumWindowDlg::OnBnClickedEnum()
{
	m_list.DeleteAllItems();
	EnumWindows(EnumWindowsProc, (LPARAM)this);
}

void CEnumWindowDlg::OnBnClickedFind()
{
	m_list.DeleteAllItems();
	myEnumWindow(NULL);//使用FindWindowEx枚举窗口
}

void CEnumWindowDlg::OnBnClickedFindMsg()
{
	m_list.DeleteAllItems();
	myEnumWindow(HWND_MESSAGE);//使用FindWindowEx枚举窗口
}

void CEnumWindowDlg::OnBnClickedExit()
{
	CDialogEx::OnOK();
}