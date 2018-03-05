
// resendSocketDlg.h : 头文件
//

#pragma once

// 
// #include<stdio.h>
// #include<string.h>
// #include<stdlib.h>
// 
// #define F(X,Y,Z) ((X&Y)|(~X&Z))
// #define G(X,Y,Z) ((X&Z)|(Y&~Z))
// #define H(X,Y,Z) (X^Y^Z)
// #define I(X,Y,Z) (Y^(X|~Z))
// 
// #define R1(A,B,C,D,X,S,T)  B+((A+F(B,C,D)+X+T)<<S|(A+F(B,C,D)+X+T)>>(32-S))
// #define R2(A,B,C,D,X,S,T)  B+((A+G(B,C,D)+X+T)<<S|(A+G(B,C,D)+X+T)>>(32-S))
// #define R3(A,B,C,D,X,S,T)  B+((A+H(B,C,D)+X+T)<<S|(A+H(B,C,D)+X+T)>>(32-S))
// #define R4(A,B,C,D,X,S,T)  B+((A+I(B,C,D)+X+T)<<S|(A+I(B,C,D)+X+T)>>(32-S))

typedef struct PACK 
{
	DWORD thedataflag; //必须是55AA55AA
	//DWORD frame;//帧
	//WORD packnum;//包序号
	BYTE data[1316];//数据
	INT packNum;
	char MD5[33];
	BYTE checksum;//校验和
}PACK,*PPACK;

// CresendSocketDlg 对话框
class CresendSocketDlg : public CDialogEx
{
// 构造
public:
	CresendSocketDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESENDSOCKET_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	static UINT ResendThread(LPVOID lParam);
	void ShowInfo(CString&info);
	HANDLE m_thread;
	volatile BOOL m_run;
protected:
	afx_msg LRESULT OnSendmsg(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButton3();
};
