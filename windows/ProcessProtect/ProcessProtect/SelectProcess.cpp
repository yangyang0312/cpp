// SelectProcess.cpp : 实现文件
//

#include "stdafx.h"
#include "ProcessProtect.h"
#include "SelectProcess.h"
#include "afxdialogex.h"
#include "tlhelp32.h"    
#include <Psapi.h>

// SelectProcess 对话框

IMPLEMENT_DYNAMIC(SelectProcess, CDialogEx)

SelectProcess::SelectProcess(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SELECTPROCESS, pParent)
{
	m_select = -1;
}

SelectProcess::~SelectProcess()
{
	for (size_t i = 0;i < m_vec.size();++i)
		delete m_vec[i];
}

void SelectProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(SelectProcess, CDialogEx)
	ON_BN_CLICKED(IDC_SELECT, &SelectProcess::OnBnClickedSelect)
END_MESSAGE_MAP()

// SelectProcess 消息处理程序
BOOL SelectProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;
	m_list.GetWindowRect(&rect);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, _T("ID"), LVCFMT_LEFT, rect.Width() / 15, 0);
	m_list.InsertColumn(1, _T("句柄"), LVCFMT_LEFT, 2*rect.Width() / 15, 1);
	m_list.InsertColumn(2, _T("进程名"), LVCFMT_LEFT, 3*rect.Width() / 15, 2);
	m_list.InsertColumn(3, _T("路径"), LVCFMT_LEFT, 8*rect.Width() / 15, 3);
	PROCESSENTRY32 pe;
	auto handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(handle, &pe))
		return FALSE;
	while (TRUE)
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32Next(handle, &pe))
			break;
		PPROCESS_STRUCT pProcess = new PROCESS_STRUCT;
		pProcess->PID = pe.th32ProcessID;
		pProcess->hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
		if (INVALID_HANDLE_VALUE == pProcess->hProcess)
		{
			delete pProcess;
			continue;
		}
		if (!GetModuleFileNameEx(pProcess->hProcess, NULL, pProcess->path, sizeof(pProcess->path)))
		{
			delete pProcess;
			continue;
		}
		memcpy_s(pProcess->name, sizeof(pProcess->name), pe.szExeFile, sizeof(pProcess->name));
		m_vec.push_back(pProcess);
	}
	CloseHandle(handle);
	CString s;
	for (size_t i = 0;i < m_vec.size();++i)
	{
		s.Format(_T("%u"), m_vec[i]->PID);
		m_list.InsertItem(i, s);
		s.Format(_T("%p"), m_vec[i]->hProcess);
		m_list.SetItemText(i, 1, s);
		m_list.SetItemText(i, 2, m_vec[i]->name);
		m_list.SetItemText(i, 3, m_vec[i]->path);
	}

	return TRUE;  
}

void SelectProcess::OnBnClickedSelect()
{
	auto pos = m_list.GetFirstSelectedItemPosition();
	if (pos)
		m_select = m_list.GetNextSelectedItem(pos);
	if (m_select >= m_vec.size())
		m_select = -1;
	CDialogEx::OnOK();
}
