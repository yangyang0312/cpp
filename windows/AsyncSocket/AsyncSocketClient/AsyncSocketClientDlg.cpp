
// AsyncSocketClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AsyncSocketClient.h"
#include "AsyncSocketClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAsyncSocketClientDlg 对话框



CAsyncSocketClientDlg::CAsyncSocketClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ASYNCSOCKETCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAsyncSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITSEND, m_editSend);
	DDX_Control(pDX, IDC_EDIT, m_edit);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAsyncSocketClientDlg::OnPaint()
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
HCURSOR CAsyncSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BEGIN_MESSAGE_MAP(CAsyncSocketClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAsyncSocketClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CONNECT, &CAsyncSocketClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_SEND, &CAsyncSocketClientDlg::OnBnClickedSend)
	ON_MESSAGE(WM_SOCKET_MSG, &CAsyncSocketClientDlg::OnSockMsg)
END_MESSAGE_MAP()

// CAsyncSocketClientDlg 消息处理程序
BOOL CAsyncSocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	m_sock = socket(PF_INET, SOCK_STREAM, 0);
	m_edit.ShowScrollBar(SB_VERT, TRUE);
	m_editSend.ShowScrollBar(SB_VERT, TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAsyncSocketClientDlg::OnBnClickedOk()
{
	closesocket(m_sock);
	WSACleanup();
	CDialogEx::OnOK();
}

void CAsyncSocketClientDlg::OnBnClickedConnect()
{
	CString s;
	GetDlgItemText(IDC_CONNECT, s);
	if (s == "链接")
	{
		m_sock = socket(PF_INET, SOCK_STREAM, 0);
		WSAAsyncSelect(m_sock, GetSafeHwnd(), WM_SOCKET_MSG, FD_CONNECT | FD_CLOSE | FD_READ);
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(9999);
		connect(m_sock,(SOCKADDR*)&addr, (sizeof(addr)));
		CString msg;
		m_edit.GetWindowText(msg);
		msg += "链接服务端\r\n";
		m_edit.SetWindowText(msg);
		SetDlgItemText(IDC_CONNECT, "断开");
	}
	else if (s == "断开")
	{
		closesocket(m_sock);
		SetDlgItemText(IDC_CONNECT, "链接");
		CString msg;
		m_edit.GetWindowText(msg);
		msg += "断开链接\r\n";
		m_edit.SetWindowText(msg);
	}
}

void CAsyncSocketClientDlg::OnBnClickedSend()
{
	CString s;
	m_editSend.GetWindowText(s);
	send(m_sock, s, s.GetLength(), 0);
}

LRESULT CAsyncSocketClientDlg::OnSockMsg(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam))
		return 0;
	CString msg;
	m_edit.GetWindowText(msg);
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_CONNECT:
	{
		msg += "链接成功\r\n";
	}
	break;
	case FD_READ:
	{
		ZeroMemory(m_buf, sizeof(m_buf));
		recv(m_sock, m_buf, sizeof(m_buf), 0);
		msg = msg + "接收到：" + CString(m_buf) + "\r\n";
	}
	break;
	case FD_CLOSE:
	{
		closesocket(m_sock);
		msg += "服务端关闭连接\r\n";
	}
	break;
	default:
		break;
	}
	m_edit.SetWindowText(msg);
	m_edit.LineScroll(m_edit.GetLineCount() - 1, 0);
	return 0;
}