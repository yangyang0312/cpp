
// SuspendProcessDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CSuspendProcessDlg 对话框
class CSuspendProcessDlg : public CDialogEx
{
// 构造
public:
	CSuspendProcessDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUSPENDPROCESS_DIALOG };
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
	afx_msg void OnBnClickedSuspend();
	afx_msg void OnBnClickedResume();
	afx_msg void OnBnClickedOk();
	CListCtrl m_list;
private:
	void ControlProcess(BOOL suspend = TRUE)const;
};
