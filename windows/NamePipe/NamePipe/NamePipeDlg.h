
// NamePipeDlg.h : 头文件
//

#pragma once

typedef struct 
{
	HANDLE	hTread;
	HANDLE	hPipe;
	HANDLE	hEvent;
} PIPE_INSTRUCT;

#define MAX_BUFFER_LEN 4096
#define MAX_THREAD_COUNT 3

extern volatile BOOL m_run;
// CNamePipeDlg 对话框
class CNamePipeDlg : public CDialogEx
{
// 构造
public:
	CNamePipeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NAMEPIPE_DIALOG };
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
	static UINT ServerThread(LPVOID para);
	PIPE_INSTRUCT  PipeInst[MAX_THREAD_COUNT];
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
};
