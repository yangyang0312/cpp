
// RebootDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Reboot.h"
#include "RebootDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRebootDlg 对话框



CRebootDlg::CRebootDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REBOOT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRebootDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRebootDlg::OnPaint()
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
HCURSOR CRebootDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_MESSAGE_MAP(CRebootDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, &CRebootDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_OK, &CRebootDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CRebootDlg 消息处理程序
BOOL CRebootDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	((CButton*)GetDlgItem(IDC_REBOOT))->SetCheck(TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRebootDlg::OnBnClickedExit()
{
	CDialogEx::OnOK();
}

void CRebootDlg::OnBnClickedOk()
{
	UINT flag = 0xFFFF;
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_REBOOT))->GetCheck())
		flag = EWX_REBOOT;
	else if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_SHUTDOWN))->GetCheck())
		flag = EWX_SHUTDOWN;
	else if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_LOGOFF))->GetCheck())
		flag = EWX_LOGOFF;
	if (flag != 0xFFFF)
	{
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;
		// 获得进程令牌
		OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
		// 查询关机特权值
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
		tkp.PrivilegeCount = 1;
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		// 给令牌设置关机特权
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
		if (GetLastError() == ERROR_SUCCESS)
			ExitWindowsEx(flag | EWX_FORCE, 0);
	}
}
