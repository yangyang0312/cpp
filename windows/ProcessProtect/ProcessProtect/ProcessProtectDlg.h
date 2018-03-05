
// ProcessProtectDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CProcessProtectDlg 对话框
class CProcessProtectDlg : public CDialogEx
{
// 构造
public:
	CProcessProtectDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCESSPROTECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedExit();
	PROCESS_STRUCT m_processList[20];
	INT m_listUse;
	HANDLE m_hExit;
	HANDLE m_hAdd;
	static UINT CheckProc(LPVOID param);
protected:
	afx_msg LRESULT OnProcessend(WPARAM wParam, LPARAM lParam);
};
