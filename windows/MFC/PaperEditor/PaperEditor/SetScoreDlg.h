#pragma once
#include "afxwin.h"
#include "PaperStruct.h"

// CSetScoreDlg 对话框

class CSetScoreDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetScoreDlg)

public:
	CSetScoreDlg(const stuScoreSet & set, const size_t & topicNum,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetScoreDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETSCOREDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioaverage();
	afx_msg void OnBnClickedRadiosingle();
	afx_msg void OnBnClickedRadiobatch();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombosingle();
	afx_msg void OnCbnSelchangeCombobatch();

public:
	//界面保存的分数配置信息
	stuScoreSet m_set;

private:
	//控件变量
	CEdit		m_editAverage;
	CComboBox	m_comboSingle;
	CEdit		m_editSingle;
	CComboBox	m_comboBatch;
	CEdit		m_editBatch;
	//储存单个设置comboBox改变前的位置
	size_t		m_singlePos;
	//储存批量设置comboBox改变前的位置
	size_t		m_BatchPos;
	//题目数量
	size_t		m_topicNum;
	//用于格式化的字符串
	CString		m_str;

private:
	//显示、隐藏指定界面控件
	void ShowWindowControls();
};
