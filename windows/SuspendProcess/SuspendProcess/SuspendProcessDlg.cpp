
// SuspendProcessDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SuspendProcess.h"
#include "SuspendProcessDlg.h"
#include "afxdialogex.h"
#include "tlhelp32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSuspendProcessDlg 对话框



CSuspendProcessDlg::CSuspendProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SUSPENDPROCESS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSuspendProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSuspendProcessDlg::OnPaint()
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
HCURSOR CSuspendProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BEGIN_MESSAGE_MAP(CSuspendProcessDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SUSPEND, &CSuspendProcessDlg::OnBnClickedSuspend)
	ON_BN_CLICKED(IDC_RESUME, &CSuspendProcessDlg::OnBnClickedResume)
	ON_BN_CLICKED(IDOK, &CSuspendProcessDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CSuspendProcessDlg 消息处理程序
BOOL CSuspendProcessDlg::OnInitDialog()
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
	m_list.InsertColumn(1, _T("进程名"), LVCFMT_LEFT, 3 * rect.Width() / 5, 1);
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

void CSuspendProcessDlg::OnBnClickedSuspend()
{
	ControlProcess();
}

void CSuspendProcessDlg::OnBnClickedResume()
{
	ControlProcess(FALSE);
}

void CSuspendProcessDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

void CSuspendProcessDlg::ControlProcess(BOOL suspend)const
{
	auto pos = m_list.GetFirstSelectedItemPosition();
	if (!pos)
		return;
	int item = m_list.GetNextSelectedItem(pos);
	if (item < 0)
		return;
	CString sPid = m_list.GetItemText(item, 0);
	int pId = _ttoi(sPid);
	if (pId <= 0)
		return;
	auto hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, pId);
	if (INVALID_HANDLE_VALUE == hSnap)
		return;
	THREADENTRY32 th32;
	ZeroMemory(&th32, sizeof(th32));
	th32.dwSize = sizeof(th32);
	BOOL ret = Thread32First(hSnap, &th32);
	while (ret)
	{
		if (th32.th32OwnerProcessID == pId)
		{
			auto hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, th32.th32ThreadID);
			if (hThread != INVALID_HANDLE_VALUE)
			{
				if (suspend)
				{
					if (SuspendThread(hThread) != -1)
						OutputDebugString(_T("SuspendThread ok"));
				}
				else
				{
					if (ResumeThread(hThread) != -1)
						OutputDebugString(_T("ResumeThread ok"));
				}
				CloseHandle(hThread);
			}
		}
		ret = Thread32Next(hSnap, &th32);
	}
	CloseHandle(hSnap);
}