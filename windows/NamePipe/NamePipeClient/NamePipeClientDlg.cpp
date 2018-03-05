
// NamePipeClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NamePipeClient.h"
#include "NamePipeClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNamePipeClientDlg 对话框



CNamePipeClientDlg::CNamePipeClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NAMEPIPECLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNamePipeClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNamePipeClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CNamePipeClientDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CNamePipeClientDlg 消息处理程序

BOOL CNamePipeClientDlg::OnInitDialog()
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

void CNamePipeClientDlg::OnPaint()
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
HCURSOR CNamePipeClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNamePipeClientDlg::OnBnClickedSend()
{
	// 打开管道
	HANDLE hPipe = CreateFile("\\\\.\\Pipe\\NamedPipe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		//AfxMessageBox("打开管道失败，服务器尚未启动,或者客户端数量过多");
		OutputDebugString("打开管道失败，服务器尚未启动,或者客户端数量过多");
		return;
	}
	DWORD nReadByte = 0, nWriteByte = 0;
	TCHAR buf[MAX_BUFFER_LEN] = { 0 };
	GetDlgItemText(IDC_EDIT1, buf, MAX_BUFFER_LEN);
	if (!WriteFile(hPipe, buf, MAX_BUFFER_LEN, &nWriteByte, NULL))
	{
		CString err;
		err.Format("func:WriteFile failed error:%d", GetLastError());
		OutputDebugString(err);
		CloseHandle(hPipe);
		return;
	}
	if (nWriteByte == 0)
	{
		CString err;
		err.Format("func:nWriteByte ==0 error:%d", GetLastError());
		OutputDebugString(err);
		CloseHandle(hPipe);
		return;
	}
	ZeroMemory(buf, MAX_BUFFER_LEN);
	if (!ReadFile(hPipe, buf, MAX_BUFFER_LEN, &nReadByte, NULL))
	{
		CString err;
		err.Format("func:ReadFile failed error:%d", GetLastError());
		OutputDebugString(err);
		CloseHandle(hPipe);
		return;
	}
	if (nReadByte == 0)
	{
		CString err;
		err.Format("func:nWriteByte ==0 error:%d", GetLastError());
		OutputDebugString(err);
		CloseHandle(hPipe);
		return;
	}
	SetDlgItemText(IDC_EDIT2, buf);
	CloseHandle(hPipe);
}
