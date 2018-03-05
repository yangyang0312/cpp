
// TrayAndBubbleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TrayAndBubble.h"
#include "TrayAndBubbleDlg.h"
#include "afxdialogex.h"
#include "Strsafe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrayAndBubbleDlg 对话框



CTrayAndBubbleDlg::CTrayAndBubbleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TRAYANDBUBBLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrayAndBubbleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTrayAndBubbleDlg::OnPaint()
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
HCURSOR CTrayAndBubbleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BEGIN_MESSAGE_MAP(CTrayAndBubbleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_MESSAGE(WM_NOTIFYICON, &CTrayAndBubbleDlg::OnNotifyicon)
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

// CTrayAndBubbleDlg 消息处理程序
BOOL CTrayAndBubbleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	AddRemoveTray(TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BOOL CTrayAndBubbleDlg::AddRemoveTray(BOOL flag)
{
	if (flag)
	{
		//static const GUID ic_guid = { 0x84d049ff, 0xb769, 0x434e, { 0x9f, 0x53, 0xbc, 0xf2, 0x98, 0x48, 0x25, 0xa9 } };
		// ZeroMemory(&m_tray,sizeof(m_tray));
		m_tray.cbSize = sizeof(NOTIFYICONDATA);
		m_tray.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));// (HICON)LoadImage(AfxGetInstanceHandle(),IDI_TRAY_ICON,IMAGE_ICON,0,0,LR_LOADFROMFILE);;
		m_tray.hWnd = m_hWnd;
		StringCchCopy(m_tray.szTip, sizeof(m_tray.szTip), _T("Test application"));
		m_tray.uCallbackMessage = WM_NOTIFYICON;
		m_tray.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		m_tray.uID = IDI_ICON1;
		//m_tray.uFlags |= NIF_GUID;
		//m_tray.guidItem = ic_guid;
		int count = 30;
		while (count > 0)
		{
			if (Shell_NotifyIcon(NIM_ADD, &m_tray) == FALSE)
			{
				Shell_NotifyIcon(NIM_DELETE, &m_tray);
				Sleep(100);
				count--;
				continue;
			}
			else
				return TRUE;
		}
		return FALSE;
	}
	else
	{//remove
		int count = 10;
		while (count > 0)
		{
			if (Shell_NotifyIcon(NIM_DELETE, &m_tray) == FALSE)
			{
				Sleep(50);
				count--;
				continue;
			}
			else
				return TRUE;
		}
		return FALSE;
	}
}

BOOL CTrayAndBubbleDlg::ShowBubbleTip(LPCTSTR lpTitle, LPCTSTR lpText, DWORD infoflags)
{
	m_tray.cbSize = sizeof(NOTIFYICONDATA);
	m_tray.uFlags |= NIF_INFO;
	m_tray.uTimeout = 10 * 1000;
	m_tray.dwInfoFlags = infoflags;
	m_tray.uVersion = NOTIFYICON_VERSION;
	StringCchCopy(m_tray.szInfoTitle, sizeof(m_tray.szTip), lpTitle);
	StringCchCopy(m_tray.szInfo, sizeof(m_tray.szTip), lpTitle);
	return Shell_NotifyIcon(NIM_MODIFY, &m_tray);
}

afx_msg LRESULT CTrayAndBubbleDlg::OnNotifyicon(WPARAM wParam, LPARAM lParam)
{
	UINT nID = (UINT)wParam;
	UINT uMouseMsg = (UINT)lParam;

	switch (nID) 
	{
	case IDI_ICON1:
	{
		if (uMouseMsg == WM_RBUTTONDOWN)
		{
			AddRemoveTray(FALSE);
			exit(0);
		}
		else if (uMouseMsg == WM_LBUTTONDOWN)
		{
			ShowBubbleTip(_T("ShowBubbleTip Title"), _T("ShowBubbleTip Context."), NIIF_INFO);
		}
	}
		break;
	default:
		return 0;
	}
	return 0;
}
