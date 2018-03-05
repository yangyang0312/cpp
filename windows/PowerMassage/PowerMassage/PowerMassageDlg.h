
// PowerMassageDlg.h : 头文件
//

#pragma once


// CPowerMassageDlg 对话框
class CPowerMassageDlg : public CDialogEx
{
// 构造
public:
	CPowerMassageDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POWERMASSAGE_DIALOG };
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
	HPOWERNOTIFY hPowerNotify;//WM_POWERBROADCAST
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRestartExplorer(WPARAM wParam, LPARAM lParam);
};
