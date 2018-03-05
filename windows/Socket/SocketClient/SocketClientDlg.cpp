
// SocketClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SocketClient.h"
#include "SocketClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSocketClientDlg 对话框



CSocketClientDlg::CSocketClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SOCKETCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITSEND, m_editSend);
	DDX_Control(pDX, IDC_EDITRECV, m_editRecv);
}

BEGIN_MESSAGE_MAP(CSocketClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CSocketClientDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDOK, &CSocketClientDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSocketClientDlg 消息处理程序

BOOL CSocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_editRecv.ShowScrollBar(SB_VERT, TRUE);
	m_editSend.ShowScrollBar(SB_VERT, TRUE);
	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSocketClientDlg::OnPaint()
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
HCURSOR CSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketClientDlg::OnBnClickedSend()
{//创建套接字
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
			return;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		CString s;
		s.Format(_T("func:WSAStartup version not ok,error:%d"), GetLastError());
		OutputDebugString(s);
		WSACleanup();
		return;
	}
	OutputDebugString("CSocketClientDlg StartSendThread OK");
	SOCKADDR_IN sendAddr;
	sendAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	sendAddr.sin_family = AF_INET;
	sendAddr.sin_port = htons(8101);
	CString sendText;
	m_editSend.GetWindowText(sendText);
	SOCKET SendSocket = socket(AF_INET, SOCK_STREAM, 0);//创建了可识别套接字
	CString msg;
	if (SOCKET_ERROR != connect(SendSocket, (SOCKADDR*)&sendAddr, sizeof(SOCKADDR)))
	{
		if (SOCKET_ERROR != send(SendSocket, sendText.GetBuffer(), sendText.GetLength(), 0))
		{
			OutputDebugString("CSocketClientDlg client send ok");
			char recvBuf[4096] = { 0 };
			if (recv(SendSocket, recvBuf, 4096, 0) > 0)
			{
				CString recvText;
				m_editRecv.GetWindowText(recvText);
				recvText = recvText + "client recv: " + CString(recvBuf) + "\r\n";
				m_editRecv.SetWindowText(recvText);
				m_editRecv.LineScroll(m_editRecv.GetLineCount()-1, 0);
			}
			else
			{
				msg.Format("CSocketClientDlg recv error:%d", WSAGetLastError());
				OutputDebugString(msg);
			}
		}
		else
		{
			msg.Format("CSocketClientDlg StartSendThread send error:%d", WSAGetLastError());
			OutputDebugString(msg);
		}
	}
	else
	{
		msg.Format("CSocketClientDlg connect error:%d", WSAGetLastError());
		OutputDebugString(msg);
	}
	closesocket(SendSocket);
	WSACleanup();
	return;
}

void CSocketClientDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
}
