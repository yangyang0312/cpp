
// EnumWindowDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CEnumWindowDlg 对话框
class CEnumWindowDlg : public CDialogEx
{
// 构造
public:
	CEnumWindowDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENUMWINDOW_DIALOG };
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
	afx_msg void OnBnClickedEnum();
	afx_msg void OnBnClickedFind();
	BOOL myEnumWindow(HWND hwnd);
	afx_msg void OnBnClickedFindMsg();
	afx_msg void OnBnClickedExit();
};
