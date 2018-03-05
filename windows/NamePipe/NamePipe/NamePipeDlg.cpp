
// NamePipeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NamePipe.h"
#include "NamePipeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNamePipeDlg 对话框
volatile BOOL m_run;


CNamePipeDlg::CNamePipeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NAMEPIPE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_run = FALSE;
}

void CNamePipeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNamePipeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CNamePipeDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CNamePipeDlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CNamePipeDlg 消息处理程序

BOOL CNamePipeDlg::OnInitDialog()
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

void CNamePipeDlg::OnPaint()
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
HCURSOR CNamePipeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT CNamePipeDlg::ServerThread(LPVOID para)
{
	DWORD nReadByte = 0, nWriteByte = 0, dwByte = 0;
	TCHAR szBuf[MAX_BUFFER_LEN] = { 0 };
	PIPE_INSTRUCT CurPipeInst = *(PIPE_INSTRUCT*)para;
	OVERLAPPED OverLapStruct = { 0, 0, 0, 0, CurPipeInst.hEvent };
	CString err;
	DWORD curThreadID = GetCurrentThreadId();
	err.Format("func:thread %d begin", curThreadID);
	OutputDebugString(err);
	while (m_run)
	{
		ZeroMemory(szBuf, MAX_BUFFER_LEN);
		ConnectNamedPipe(CurPipeInst.hPipe, &OverLapStruct);
		WaitForSingleObject(CurPipeInst.hEvent, INFINITE);
		OutputDebugString("waited");
		if (!GetOverlappedResult(CurPipeInst.hPipe, &OverLapStruct, &dwByte, true))
		{
			DisconnectNamedPipe(CurPipeInst.hPipe);
			continue;
		}
		if (!ReadFile(CurPipeInst.hPipe, szBuf, MAX_BUFFER_LEN, &nReadByte, NULL))
		{
			err.Format("func:ReadFile failed %d error:%d", GetLastError());
			OutputDebugString(err);
			DisconnectNamedPipe(CurPipeInst.hPipe);
			continue;
		}
		if(nReadByte == 0)
		{
			DisconnectNamedPipe(CurPipeInst.hPipe);
			continue;
		}
		err.Format("func:thread:%d recv:%s", curThreadID, szBuf);
		OutputDebugString(err);
		ZeroMemory(szBuf, MAX_BUFFER_LEN);
		sprintf_s(szBuf, "server %d sendmsg.", curThreadID);
		if (!WriteFile(CurPipeInst.hPipe, szBuf, MAX_BUFFER_LEN, &nWriteByte, NULL))
		{
			err.Format("func:WriteFile failed %d error:%d", GetLastError());
			OutputDebugString(err);
			DisconnectNamedPipe(CurPipeInst.hPipe);
			continue;
		}
		DisconnectNamedPipe(CurPipeInst.hPipe);
	}
	err.Format("func:thread %d exit", curThreadID);
	OutputDebugString(err);
	return 0;
}

void CNamePipeDlg::OnBnClickedStart()
{
	m_run = TRUE;
	CString lpPipeName = "\\\\.\\Pipe\\NamedPipe";
	for (UINT i = 0; i < MAX_THREAD_COUNT; ++i)
	{
		PipeInst[i].hPipe = CreateNamedPipe(lpPipeName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, MAX_THREAD_COUNT, 0, 0, 1000, NULL);
		DWORD error = GetLastError();
		if (PipeInst[i].hPipe == INVALID_HANDLE_VALUE)
		{
			CString err;
			err.Format("func:CreateNamedPipe failed %d error:%d", i, error);
			OutputDebugString(err);
			continue;
		}
		PipeInst[i].hEvent = CreateEvent(NULL, FALSE, FALSE, FALSE);
		error = GetLastError();
		if (!PipeInst[i].hEvent)
		{
			CString err;
			err.Format("func:CreateEvent failed %d error:%d", i, error);
			OutputDebugString(err);
			continue;
		}
		PipeInst[i].hTread = AfxBeginThread(ServerThread, &PipeInst[i], THREAD_PRIORITY_NORMAL);
		error = GetLastError();
		if (!PipeInst[i].hTread)
		{
			CString err;
			err.Format("func:AfxBeginThread failed %d error:%d", i, error);
			OutputDebugString(err);
			continue;
		}
	}
	AfxMessageBox("服务启动成功");
}


void CNamePipeDlg::OnBnClickedStop()
{
	DWORD dwNewMode = PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_NOWAIT;
	m_run = FALSE;
	for (UINT i = 0; i < MAX_THREAD_COUNT; i++)
	{
		SetEvent(PipeInst[i].hEvent);
		CloseHandle(PipeInst[i].hTread);
		CloseHandle(PipeInst[i].hPipe);
	}
	AfxMessageBox("停止启动成功");
}
