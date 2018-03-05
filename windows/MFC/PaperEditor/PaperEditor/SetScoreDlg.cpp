// SetScoreDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PaperEditor.h"
#include "SetScoreDlg.h"
#include "afxdialogex.h"

// CSetScoreDlg 对话框
IMPLEMENT_DYNAMIC(CSetScoreDlg, CDialogEx)

CSetScoreDlg::CSetScoreDlg(const stuScoreSet & set, const size_t & topicNum, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SETSCOREDLG, pParent)
{
	m_set = set;
	m_topicNum = topicNum;
	for (size_t i = m_set.m_vecSigle.size();i < topicNum;++i)//插入足够多的题目分数
		m_set.m_vecSigle.push_back(0.0);
	m_singlePos = 0;
	m_BatchPos = 0;
}

CSetScoreDlg::~CSetScoreDlg()
{
}

void CSetScoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITAVERAGE, m_editAverage);
	DDX_Control(pDX, IDC_COMBOSINGLE, m_comboSingle);
	DDX_Control(pDX, IDC_EDITSINGLE, m_editSingle);
	DDX_Control(pDX, IDC_COMBOBATCH, m_comboBatch);
	DDX_Control(pDX, IDC_EDITBATCH, m_editBatch);
}

BEGIN_MESSAGE_MAP(CSetScoreDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIOAVERAGE, &CSetScoreDlg::OnBnClickedRadioaverage)
	ON_BN_CLICKED(IDC_RADIOSINGLE, &CSetScoreDlg::OnBnClickedRadiosingle)
	ON_BN_CLICKED(IDC_RADIOBATCH, &CSetScoreDlg::OnBnClickedRadiobatch)
	ON_BN_CLICKED(IDOK, &CSetScoreDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBOSINGLE, &CSetScoreDlg::OnCbnSelchangeCombosingle)
	ON_CBN_SELCHANGE(IDC_COMBOBATCH, &CSetScoreDlg::OnCbnSelchangeCombobatch)
END_MESSAGE_MAP()

BOOL CSetScoreDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_str.Format("%.2lf", m_set.m_type == eScoreTypeAverage ? m_set.m_total : 100);	//平均分配总分
	m_editAverage.SetWindowText(m_str);
	m_comboSingle.ResetContent();						//删除所有行
	for (size_t i = 0;i < m_topicNum;++i)				//添加题目
	{
		m_str.Format("第%d题", i + 1);
		m_comboSingle.AddString(m_str);
	}
	if (m_topicNum > 0)									//第一题
	{
		m_str.Format("%.2lf", m_set.m_vecSigle[0]);
		m_editSingle.SetWindowText(m_str);
		m_comboSingle.SetCurSel(0);
	}
	m_comboBatch.SetCurSel(0);							//批量设置
	m_str.Format("%.2lf", m_set.m_batch[0]);
	m_editBatch.SetWindowText(m_str);
	if (m_set.m_type == eScoreTypeAverage)				//点一下按钮
		OnBnClickedRadioaverage();
	else if (m_set.m_type == eScoreTypeSingle)
		OnBnClickedRadiosingle();
	else if (m_set.m_type == eScoreTypeBatch)
		OnBnClickedRadiobatch();

	return TRUE; 
}

void CSetScoreDlg::OnBnClickedRadioaverage()	//平均
{
	m_set.m_type = eScoreTypeAverage;
	ShowWindowControls();
}

void CSetScoreDlg::OnBnClickedRadiosingle()		//单个
{
	m_set.m_type = eScoreTypeSingle;
	ShowWindowControls();
}

void CSetScoreDlg::OnBnClickedRadiobatch()		//批量
{
	m_set.m_type = eScoreTypeBatch;
	ShowWindowControls();
}

void CSetScoreDlg::ShowWindowControls()		//界面控件状态切换
{
	((CButton *)GetDlgItem(IDC_RADIOAVERAGE))->SetCheck(m_set.m_type == eScoreTypeAverage); //radio状态切换
	((CButton *)GetDlgItem(IDC_RADIOSINGLE))->SetCheck(m_set.m_type == eScoreTypeSingle);
	((CButton *)GetDlgItem(IDC_RADIOBATCH))->SetCheck(m_set.m_type == eScoreTypeBatch);
	m_editAverage.EnableWindow(m_set.m_type == eScoreTypeAverage);
	m_comboSingle.EnableWindow(m_set.m_type == eScoreTypeSingle);
	m_editSingle.EnableWindow(m_set.m_type == eScoreTypeSingle);
	m_comboBatch.EnableWindow(m_set.m_type == eScoreTypeBatch);
	m_editBatch.EnableWindow(m_set.m_type == eScoreTypeBatch);
}

void CSetScoreDlg::OnCbnSelchangeCombosingle()
{
	m_editSingle.GetWindowText(m_str);					
	if (m_singlePos < m_topicNum)	 //保存当前值
		m_set.m_vecSigle[m_singlePos] = atof(m_str);	 
	m_singlePos = m_comboSingle.GetCurSel();			 
	if (m_singlePos < m_topicNum)	 //更新新的位置的数据到界面
	{
		m_str.Format("%.2lf", m_set.m_vecSigle[m_singlePos]);
		m_editSingle.SetWindowText(m_str);
	}
}

void CSetScoreDlg::OnCbnSelchangeCombobatch()
{
	m_editBatch.GetWindowText(m_str);
	if (m_BatchPos < 4)				//保存当前值
		m_set.m_batch[m_BatchPos] = atof(m_str);
	m_BatchPos = m_comboBatch.GetCurSel();
	if (m_BatchPos < 4)				//更新新的位置的数据到界面
	{
		m_str.Format("%.2lf", m_set.m_batch[m_BatchPos]);
		m_editBatch.SetWindowText(m_str);
	}
}

void CSetScoreDlg::OnBnClickedOk()				//确定
{
	if (m_set.m_type == eScoreTypeAverage)		//保存各个设置的当前值
	{
		m_editAverage.GetWindowText(m_str);
		m_set.m_total = atof(m_str);
	}
	else if (m_set.m_type == eScoreTypeSingle)
	{
		m_editSingle.GetWindowText(m_str);
		if (m_set.m_vecSigle.size() > m_singlePos)
			m_set.m_vecSigle[m_singlePos] = atof(m_str);
	}
	else if (m_set.m_type == eScoreTypeBatch)
	{
		m_editBatch.GetWindowText(m_str);
		if(m_BatchPos < 4)
			m_set.m_batch[m_BatchPos] = atof(m_str);
	}
	CDialogEx::OnOK();
}
