
// KillPSDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KillPS.h"
#include "KillPSDlg.h"
#include "afxdialogex.h"
#include "tlhelp32.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKillPSDlg 对话框



CKillPSDlg::CKillPSDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_KILLPS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKillPSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKillPSDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CKillPSDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CKillPSDlg 消息处理程序

BOOL CKillPSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKillPSDlg::OnPaint()
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
HCURSOR CKillPSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//请求获取特权
BOOL CKillPSDlg::SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnable)
{
	OutputDebugString(lpszPrivilege);
	BOOL bRet = FALSE;
	HANDLE hToken = NULL;
	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, ::GetCurrentProcessId());
	if (!::OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		goto __EXIT;
	}
	LUID Luid;
	if (!::LookupPrivilegeValue(NULL, lpszPrivilege, &Luid))
	{
		goto __EXIT;
	}
	TOKEN_PRIVILEGES newPrivilege;
	newPrivilege.PrivilegeCount = 1;
	newPrivilege.Privileges[0].Luid = Luid;
	newPrivilege.Privileges[0].Attributes = //设置特权属性
		bEnable ?
		SE_PRIVILEGE_ENABLED :
		SE_PRIVILEGE_ENABLED_BY_DEFAULT;
	if (!::AdjustTokenPrivileges(hToken, FALSE, &newPrivilege,
		sizeof(TOKEN_PRIVILEGES), NULL, NULL))
	{
		CString s;
		s.Format(_T("AdjustTokenPrivileges error: %u\n"), GetLastError());
		OutputDebugString(s);
		goto __EXIT;
	}
	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)//查看是否真的设置成功了
	{
		OutputDebugString(_T("The token does not have the specified privilege. \n"));
		goto __EXIT;
	}
	bRet = TRUE;
	OutputDebugString(_T("Set OK"));
__EXIT:
	if (hProcess)
	{
		::CloseHandle(hProcess);
	}
	if (hToken)
	{
		::CloseHandle(hToken);
	}
	return bRet;
}

BOOL CKillPSDlg::KillPS(DWORD id)
{
	HANDLE hProcess = NULL, hProcessToken = NULL;
	BOOL IsKilled = FALSE, bRet = FALSE;
	if ((hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id)) != NULL)
	{
		if (TerminateProcess(hProcess, 1))
		{
			return TRUE;
		}
	}
	__try
	{
		SetPrivilege(SE_DEBUG_NAME, TRUE);
		if ((hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id)) == NULL)
		{
			printf("\nOpen Process %d failed:%d", id, GetLastError());
			__leave;
		}
		//printf("\nOpen Process %d ok!",id);
		if (!TerminateProcess(hProcess, 1))
		{
			printf("\nTerminateProcess failed:%d", GetLastError());
			__leave;
		}
		IsKilled = TRUE;
	}
	__finally
	{
		if (hProcessToken != NULL) CloseHandle(hProcessToken);
		if (hProcess != NULL) CloseHandle(hProcess);
	}
	return(IsKilled);
}

void CKillPSDlg::OnBnClickedOk()
{
	CString name;
	GetDlgItemText(IDC_EDIT1, name);
	if (!name.IsEmpty())
	{
		PROCESSENTRY32 pe;
		auto handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(handle, &pe))
		{
			while (TRUE)
			{
				pe.dwSize = sizeof(PROCESSENTRY32);
				if (!Process32Next(handle, &pe))
					break;
				if (CString(pe.szExeFile).CompareNoCase(name) == 0)
				{
					KillPS(pe.th32ProcessID);
				}
			}
		}
		CloseHandle(handle);
	}
	CDialogEx::OnOK();
}
