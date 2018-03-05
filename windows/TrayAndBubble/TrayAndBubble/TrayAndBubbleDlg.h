
// TrayAndBubbleDlg.h : 头文件
//

#pragma once


// CTrayAndBubbleDlg 对话框
class CTrayAndBubbleDlg : public CDialogEx
{
// 构造
public:
	CTrayAndBubbleDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRAYANDBUBBLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	BOOL AddRemoveTray(BOOL flag);
	NOTIFYICONDATA m_tray;
	BOOL ShowBubbleTip(LPCTSTR lpTitle, LPCTSTR lpText, DWORD infoflags);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNotifyicon(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
