
// SocketDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Socket.h"
#include "SocketDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSocketDlg 对话框



CSocketDlg::CSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SOCKET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITSEND, m_editSend);
	DDX_Control(pDX, IDC_EDIT, m_edit);
}

BEGIN_MESSAGE_MAP(CSocketDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CSocketDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CSocketDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDOK, &CSocketDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSocketDlg 消息处理程序

BOOL CSocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_edit.ShowScrollBar(SB_VERT, TRUE);
	m_editSend.ShowScrollBar(SB_VERT, TRUE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSocketDlg::OnPaint()
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
HCURSOR CSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketDlg::OnBnClickedStart()
{
	m_run = TRUE;
	if (!AfxBeginThread(CSocketDlg::StartRecvThread, this, THREAD_PRIORITY_ABOVE_NORMAL))
	{
		OutputDebugString("func:AfxBeginThread StartRecvThread failed");
		return;
	}
}

void CSocketDlg::OnBnClickedStop()
{
	m_run = FALSE;
	SOCKADDR_IN addr;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8101);
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);//因为accept阻塞的，这样能够正常退出监听线程
	CString msg;
	connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR));
	closesocket(sock);
}

UINT CSocketDlg::StartRecvThread(LPVOID para)
{
	//创建套接字
	WORD myVersionRequest;
	WSADATA wsaData;
	myVersionRequest = MAKEWORD(2, 2);
	int err;
	err = WSAStartup(myVersionRequest, &wsaData);
	if (err != 0)
	{
		CString s;
		s.Format(_T("func:WSAStartup failed,error:%d"), GetLastError());
		OutputDebugString(s);
		char cstrNewDosCmd[] = "netsh.exe winsock reset";
		STARTUPINFO si;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		GetStartupInfo(&si);
		si.wShowWindow = SW_HIDE;
		si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
		PROCESS_INFORMATION pi;
		// 启动进程  
		DWORD dwCreationFlag = NORMAL_PRIORITY_CLASS | CREATE_UNICODE_ENVIRONMENT | CREATE_NO_WINDOW;
		BOOL bSuc = CreateProcess(NULL, cstrNewDosCmd, NULL, NULL, TRUE, dwCreationFlag, NULL, NULL, &si, &pi);
		WaitForSingleObject(pi.hProcess, 5000);
		err = WSAStartup(myVersionRequest, &wsaData);
		if (err != 0)
			return 0;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		CString s;
		s.Format(_T("func:WSAStartup version not ok,error:%d"), GetLastError());
		OutputDebugString(s);
		WSACleanup();
		return 0;
	}

	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);//创建了可识别套接字
	SOCKADDR_IN listenAddr;
	listenAddr.sin_family = AF_INET;
	listenAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip地址
	listenAddr.sin_port = htons(8101);//绑定端口
	int flag = 1;
	int len = sizeof(int);
	if (setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&flag, len) == -1)
	{
		CString s;
		s.Format(_T("set reuse recvSock IP:%s port:%d failed ,error:%d"), inet_ntoa(listenAddr.sin_addr), listenAddr.sin_port, WSAGetLastError());
		OutputDebugString(s);
	}
	if (SOCKET_ERROR == bind(listenSocket, (SOCKADDR*)&listenAddr, sizeof(SOCKADDR)))
	{
		CString s;
		s.Format(_T("bind recvSock IP:%s port:%d failed ,error:%d"), inet_ntoa(listenAddr.sin_addr), listenAddr.sin_port, WSAGetLastError());
		OutputDebugString(s);
		closesocket(listenSocket);
		WSACleanup();
		return 0;
	}
	if (SOCKET_ERROR == listen(listenSocket, 5))
	{
		CString s;
		s.Format(_T("listen recvSock IP:%s port:%d failed ,error:%d"), inet_ntoa(listenAddr.sin_addr), listenAddr.sin_port, WSAGetLastError());
		OutputDebugString(s);
		closesocket(listenSocket);
		WSACleanup();
		return 0;
	}
	OutputDebugString("StartRecvThread OK");
	CSocketDlg * pParent = (CSocketDlg *)para;
	SOCKADDR_IN clientsocket;
	int AddrLen = sizeof(SOCKADDR);
	TCHAR recvBuf[4096];
	while (pParent->m_run)
	{
		ZeroMemory(recvBuf, 4096);
		SOCKET serConn = accept(listenSocket, (SOCKADDR*)&clientsocket, &AddrLen);
		if (serConn == INVALID_SOCKET)
		{
			CString msg;
			msg.Format("server sccept error:%d", WSAGetLastError());
			OutputDebugString(msg);
			continue;
		}
		OutputDebugString("server StartRecvThread accept");
		int recvLen = recv(serConn, recvBuf, 4096, 0);
		OutputDebugString(recvBuf);
		if (recvLen < 1)
		{
			CString msg;
			msg.Format("server recv error:%d", WSAGetLastError());
			OutputDebugString(msg);
			closesocket(serConn);//关闭
			continue;
		}
		CString sendText;
		pParent->m_editSend.GetWindowText(sendText);
		SOCKADDR_IN sendAddr;
		sendAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		sendAddr.sin_family = AF_INET;
		sendAddr.sin_port = htons(8102);
		if (SOCKET_ERROR != send(serConn, sendText, sendText.GetLength(), 0))
		{
			OutputDebugString("server send ok");
		}
		else
		{
			OutputDebugString("server send error");
		}
		CString text;
		pParent->m_edit.GetWindowText(text);
		text = text+ "接收到："+CString(recvBuf)+"\r\n"+"发送："+sendText+"\r\n";
		pParent->m_edit.SetWindowText(text);
		pParent->m_edit.LineScroll(pParent->m_edit.GetLineCount() - 1, 0);
		closesocket(serConn);//关闭
	}
	closesocket(listenSocket);
	WSACleanup();
	OutputDebugString("StartRecvThread STOP");
	return 0;
}

void CSocketDlg::OnBnClickedOk()
{
	m_run = FALSE;
	CDialogEx::OnOK();
}
