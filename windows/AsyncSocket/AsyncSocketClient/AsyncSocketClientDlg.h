
// AsyncSocketClientDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CAsyncSocketClientDlg 对话框
class CAsyncSocketClientDlg : public CDialogEx
{
// 构造
public:
	CAsyncSocketClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ASYNCSOCKETCLIENT_DIALOG };
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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedSend();
	afx_msg LRESULT OnSockMsg(WPARAM wParam, LPARAM lParam);
	CEdit m_editSend;
	CEdit m_edit;
	SOCKET m_sock;
	CHAR m_buf[2048];
};
