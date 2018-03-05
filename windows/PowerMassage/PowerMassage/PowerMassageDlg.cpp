
// PowerMassageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PowerMassage.h"
#include "PowerMassageDlg.h"
#include "afxdialogex.h"
#include <WtsApi32.h>
#pragma comment(lib,"WtsApi32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPowerMassageDlg 对话框

const UINT WMEX_TASKBARCREATED = ::RegisterWindowMessage(TEXT("TaskbarCreated"));

CPowerMassageDlg::CPowerMassageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_POWERMASSAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPowerMassageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPowerMassageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_REGISTERED_MESSAGE(WMEX_TASKBARCREATED, OnRestartExplorer)
END_MESSAGE_MAP()


// CPowerMassageDlg 消息处理程序

BOOL CPowerMassageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	hPowerNotify = RegisterPowerSettingNotification(m_hWnd, &GUID_LIDSWITCH_STATE_CHANGE, DEVICE_NOTIFY_WINDOW_HANDLE);//注册WM_POWERBROADCAST消息
	WTSRegisterSessionNotification(m_hWnd, NOTIFY_FOR_THIS_SESSION);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPowerMassageDlg::OnPaint()
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
HCURSOR CPowerMassageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

typedef HDESK(WINAPI *PFNOPENDESKTOP)(LPSTR, DWORD, BOOL, ACCESS_MASK);
typedef BOOL(WINAPI *PFNCLOSEDESKTOP)(HDESK);
typedef BOOL(WINAPI *PFNSWITCHDESKTOP)(HDESK);
BOOL PP_IsWorkStationLocked()//判断是否处于锁屏界面
{
	BOOL bLocked = FALSE;
	static HMODULE hUser32 = LoadLibrary(_T("user32.dll"));
	if (hUser32) 
	{
		static PFNOPENDESKTOP fnOpenDesktop = (PFNOPENDESKTOP)GetProcAddress(hUser32, "OpenDesktopA");
		static PFNCLOSEDESKTOP fnCloseDesktop = (PFNCLOSEDESKTOP)GetProcAddress(hUser32, "CloseDesktop");
		static PFNSWITCHDESKTOP fnSwitchDesktop = (PFNSWITCHDESKTOP)GetProcAddress(hUser32, "SwitchDesktop");
		if (fnOpenDesktop && fnCloseDesktop && fnSwitchDesktop) 
		{
			HDESK hDesk = fnOpenDesktop("Default", 0, FALSE, DESKTOP_SWITCHDESKTOP);
			if (hDesk) 
			{
				bLocked = !fnSwitchDesktop(hDesk);
				fnCloseDesktop(hDesk);
			}
		}
	}
	return bLocked;
}

LRESULT CPowerMassageDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_QUERYENDSESSION://可判断关机、重启等
	{
		OutputDebugString(_T("WM_QUERYENDSESSION"));
	}
	break;
	case WM_POWERBROADCAST://判断睡眠、休眠等
	{
		OutputDebugString(_T("WM_POWERBROADCAST "));
		if (wParam == PBT_APMSUSPEND)//系统暂停运行
			OutputDebugString(_T("power off"));
		else if ((wParam == PBT_APMRESUMEAUTOMATIC) || (wParam == PBT_APMRESUMESUSPEND))//唤醒
			OutputDebugString(_T("power ON"));
		else
			OutputDebugString(_T("other option"));
	}
	break;
	case WM_DESTROY:
	{
		WTSUnRegisterSessionNotification(m_hWnd);
		UnregisterPowerSettingNotification(hPowerNotify);
	}
	case WM_WTSSESSION_CHANGE://判断登录、注销、锁屏等
	{
		switch (wParam)
		{
		case WTS_CONSOLE_CONNECT:
			OutputDebugString(_T("session login"));
		break;
		case WTS_CONSOLE_DISCONNECT:
			OutputDebugString(_T("session logoff"));
		break;
		case WTS_SESSION_LOCK:
			OutputDebugString(_T("session lock"));
		break;
		default:
			break;
		}
	}
	default:
		break;
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}

LRESULT CPowerMassageDlg::OnRestartExplorer(WPARAM wParam, LPARAM lParam) //判断资源管理器重启
{
	OutputDebugString(_T("RestartExplorer"));
	return TRUE;
}