
// EnumModuleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EnumModule.h"
#include "EnumModuleDlg.h"
#include "afxdialogex.h"
#include "tlhelp32.h"
#include "EnumDllDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEnumModuleDlg 对话框



CEnumModuleDlg::CEnumModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ENUMMODULE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEnumModuleDlg::OnPaint()
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
HCURSOR CEnumModuleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEnumModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CEnumModuleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DLL, &CEnumModuleDlg::OnBnClickedDll)
END_MESSAGE_MAP()

// CEnumModuleDlg 消息处理程序
BOOL CEnumModuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CRect rect;
	m_list.GetWindowRect(&rect);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, _T("进程ID"), LVCFMT_LEFT, rect.Width() / 4, 0);
	m_list.InsertColumn(1, _T("进程名"), LVCFMT_LEFT, 3*rect.Width() / 5, 1);
	PROCESSENTRY32 pe;
	auto handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (handle != INVALID_HANDLE_VALUE)
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(handle, &pe))
			return FALSE;
		CString s;
		int item = 0;
		while (TRUE)
		{
			pe.dwSize = sizeof(PROCESSENTRY32);
			if (!Process32Next(handle, &pe))
				break;
			s.Format(_T("%u"), pe.th32ProcessID);
			m_list.InsertItem(item, s);
			m_list.SetItemText(item, 1, pe.szExeFile);
			++item;
		}
		CloseHandle(handle);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEnumModuleDlg::OnBnClickedDll()
{
	auto pos = m_list.GetFirstSelectedItemPosition();
	if (pos)
	{
		int item = m_list.GetNextSelectedItem(pos);
		if (item > -1)
		{
			CString sPid = m_list.GetItemText(item, 0);
			int pId = _ttoi(sPid);
			if (pId > 0)
			{
				CEnumDllDlg dlg;
				dlg.m_pID = pId;
				dlg.DoModal();
			}
		}
	}
}
