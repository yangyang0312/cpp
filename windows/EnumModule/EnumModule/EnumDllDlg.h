#pragma once
#include "afxcmn.h"
#include "tlhelp32.h"


// CEnumDllDlg 对话框

class CEnumDllDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEnumDllDlg)

public:
	CEnumDllDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEnumDllDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	int m_pID;
};
