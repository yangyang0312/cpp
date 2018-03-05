
// EnumServiceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EnumService.h"
#include "EnumServiceDlg.h"
#include "afxdialogex.h"
#include <winsvc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEnumServiceDlg 对话框



CEnumServiceDlg::CEnumServiceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ENUMSERVICE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnumServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEnumServiceDlg::OnPaint()
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
HCURSOR CEnumServiceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BEGIN_MESSAGE_MAP(CEnumServiceDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CEnumServiceDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CEnumServiceDlg::OnBnClickedStop)
	ON_BN_CLICKED(ID_EXIT, &CEnumServiceDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_DRIVER, &CEnumServiceDlg::OnBnClickedDriver)
	ON_BN_CLICKED(IDC_WIN32, &CEnumServiceDlg::OnBnClickedWin32)
END_MESSAGE_MAP()

// CEnumServiceDlg 消息处理程序
BOOL CEnumServiceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	((CButton*)GetDlgItem(IDC_WIN32))->SetCheck(TRUE);
	CRect rect;
	m_list.GetWindowRect(&rect);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, _T("服务名"), LVCFMT_LEFT, rect.Width() / 4, 0);
	m_list.InsertColumn(1, _T("描述"), LVCFMT_LEFT, 5*rect.Width() / 8, 1);
	m_list.InsertColumn(2, _T("状态"), LVCFMT_LEFT, rect.Width() / 8, 2);
	ShowServiceStatus(SERVICE_WIN32);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

VOID CEnumServiceDlg::ShowServiceStatus(DWORD type)
{
	m_list.DeleteAllItems();
	SC_HANDLE hSc = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSc)
	{
		DWORD dwCount = 0;
		DWORD dwSize = 0;
		LPENUM_SERVICE_STATUS lpStatus;
		auto ret = EnumServicesStatus(hSc, type, SERVICE_STATE_ALL, NULL, 0, &dwSize, &dwCount, NULL);
		if (!ret && GetLastError() == ERROR_MORE_DATA)
		{
			lpStatus = (LPENUM_SERVICE_STATUS)(new BYTE[dwSize]);
			ret = EnumServicesStatus(hSc, type, SERVICE_STATE_ALL, lpStatus, dwSize, &dwSize, &dwCount, NULL);
			if (ret)
			{
				for (DWORD i = 0;i < dwCount;++i)
				{
					m_list.InsertItem(i, lpStatus[i].lpServiceName);
					m_list.SetItemText(i, 1, lpStatus[i].lpDisplayName);
					CString s;
					switch (lpStatus[i].ServiceStatus.dwCurrentState)
					{
					case SERVICE_RUNNING:
						s = _T("运行");
						break;
					case SERVICE_STOP:
						s = _T("停止");
						break;
					case SERVICE_PAUSED:
						s = _T("暂停");
						break;
					default:
						s = _T("其他");
						break;
					}
					m_list.SetItemText(i, 2, s);
				}
			}
			delete lpStatus;
		}
		CloseServiceHandle(hSc);
	}
}

void CEnumServiceDlg::OnBnClickedStart()
{
	auto pos = m_list.GetFirstSelectedItemPosition();
	if (pos)
	{
		int item = m_list.GetNextSelectedItem(pos);
		if (item > -1)
		{
			SC_HANDLE hSc = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
			if (hSc)
			{
				CString name = m_list.GetItemText(item, 0);
				if (!name.IsEmpty())
				{
					SC_HANDLE hService = OpenService(hSc, name, SERVICE_ALL_ACCESS);
					if (hService)
					{
						if (StartServiceW(hService, 0, NULL))
							m_list.SetItemText(item, 2, _T("运行"));
						else
							AfxMessageBox(CString(_T("启动：")) + name + _T("失败!"));
						CloseServiceHandle(hService);
					}
				}
				CloseServiceHandle(hSc);
			}
		}
	}
}

void CEnumServiceDlg::OnBnClickedStop()
{
	auto pos = m_list.GetFirstSelectedItemPosition();
	if (pos)
	{
		int item = m_list.GetNextSelectedItem(pos);
		if (item > -1)
		{
			SC_HANDLE hSc = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
			if (hSc)
			{
				CString name = m_list.GetItemText(item, 0);
				if (!name.IsEmpty())
				{
					SC_HANDLE hService = OpenService(hSc, name, SERVICE_ALL_ACCESS);
					if (hService)
					{
						SERVICE_STATUS status;
						if (ControlService(hService, SERVICE_CONTROL_STOP, &status))
							m_list.SetItemText(item, 2, _T("停止"));
						else
							AfxMessageBox(CString(_T("停止：")) + name + _T("失败!"));
						CloseServiceHandle(hService);
					}
				}
				CloseServiceHandle(hSc);
			}
		}
	}
}

void CEnumServiceDlg::OnBnClickedExit()
{
	CDialogEx::OnOK();
}

void CEnumServiceDlg::OnBnClickedDriver()
{
	ShowServiceStatus(SERVICE_DRIVER);
}

void CEnumServiceDlg::OnBnClickedWin32()
{
	ShowServiceStatus(SERVICE_WIN32);
}
