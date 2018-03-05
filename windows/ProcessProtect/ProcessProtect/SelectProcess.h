#pragma once
#include "afxcmn.h"
#include <vector>


// SelectProcess 对话框

class SelectProcess : public CDialogEx
{
	DECLARE_DYNAMIC(SelectProcess)

public:
	SelectProcess(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SelectProcess();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SELECTPROCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	virtual BOOL OnInitDialog();
	INT m_select;
	std::vector<PPROCESS_STRUCT>m_vec;
	afx_msg void OnBnClickedSelect();
};
