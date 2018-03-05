
// KillPSDlg.h : 头文件
//

#pragma once


// CKillPSDlg 对话框
class CKillPSDlg : public CDialogEx
{
// 构造
public:
	CKillPSDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KILLPS_DIALOG };
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
	BOOL KillPS(DWORD id);
	BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnable = TRUE);
};
