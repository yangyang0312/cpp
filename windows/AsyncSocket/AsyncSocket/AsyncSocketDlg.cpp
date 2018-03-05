
// AsyncSocketDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AsyncSocket.h"
#include "AsyncSocketDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAsyncSocketDlg 对话框



CAsyncSocketDlg::CAsyncSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ASYNCSOCKET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAsyncSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, m_edit);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAsyncSocketDlg::OnPaint()
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
HCURSOR CAsyncSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_MESSAGE_MAP(CAsyncSocketDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAsyncSocketDlg::OnBnClickedOk)
	ON_MESSAGE(WM_SOCKET_MSG, &CAsyncSocketDlg::OnSockMsg)
END_MESSAGE_MAP()

// CAsyncSocketDlg 消息处理程序
BOOL CAsyncSocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	m_listenSock = socket(PF_INET, SOCK_STREAM, 0);
	WSAAsyncSelect(m_listenSock, GetSafeHwnd(), WM_SOCKET_MSG, FD_ACCEPT);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = ADDR_ANY;
	addr.sin_port = htons(9999);
	bind(m_listenSock, (SOCKADDR*)&addr, sizeof(addr));
	listen(m_listenSock, 5);
	m_edit.ShowScrollBar(SB_VERT, TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CAsyncSocketDlg::OnBnClickedOk()
{
	closesocket(m_clientSock);
	closesocket(m_listenSock);
	WSACleanup();
	CDialogEx::OnOK();
}

LRESULT CAsyncSocketDlg::OnSockMsg(WPARAM wParam, LPARAM lParam)
{
	if (WSAGETSELECTERROR(lParam))
		return 0;
	CString msg;
	m_edit.GetWindowText(msg);
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:
	{
		SOCKADDR_IN addr;
		int size = sizeof(addr);
		m_clientSock = accept(m_listenSock, (SOCKADDR*)&addr, &size);
		WSAAsyncSelect(m_clientSock, GetSafeHwnd(), WM_SOCKET_MSG, FD_READ | FD_CLOSE);
		CString s;
		s.Format(_T("客户端地址：%s:%d\r\n"), inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
		msg += s;
	}
		break;
	case FD_READ:
	{
		ZeroMemory(m_buf, sizeof(m_buf));
		recv(m_clientSock, m_buf, sizeof(m_buf), 0);
		msg = msg + "接收到：" + CString(m_buf) + "\r\n";
		CString s = CString("server send:") + CString(m_buf);
		send(m_clientSock, s, s.GetLength(), 0);
	}
		break;
	case FD_CLOSE:
	{
		closesocket(m_clientSock);
		msg += "客户端关闭连接\r\n";
	}
		break;
	default:
		break;
	}
	m_edit.SetWindowText(msg);
	m_edit.LineScroll(m_edit.GetLineCount() - 1, 0);
	return 0;
}