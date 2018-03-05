
// PaperEditorDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "PaperStruct.h"
#include <vector>
#include "afxext.h"

// CPaperEditorDlg 对话框
class CPaperEditorDlg : public CDialogEx
{
// 构造
public:
	CPaperEditorDlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAPEREDITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	//屏蔽enter退出
	virtual void OnOK();
	//屏蔽esc退出
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	//限制窗口大小
	void OnGetMinMaxInfo(MINMAXINFO * lpMMI);

private:
	//控件变量
	CEdit	   m_editTopicTitle;
	CListBox   m_listTopicFile;
	CButton    m_checkA;
	CButton    m_checkB;
	CButton    m_checkC;
	CButton    m_checkD;
	CButton    m_checkE;
	CEdit      m_editA;
	CEdit      m_editB;
	CEdit      m_editC;
	CEdit      m_editD;
	CEdit      m_editE;
	CEdit      m_editAnswer;
	CComboBox  m_comboSelect;
	CEdit	   m_editPaperTitle;
	CListBox   m_listPaperFile;
	CStatic    m_groupPaper;
	CStatic    m_groupContent;
	CStatic    m_groupType;
	//题目类型
	eTopicType m_topicType;
	//试卷结构
	stuPaper   m_paper;
	//保存试卷初始信息，用于新建、打开、关闭试卷时检测内容是否有更新（有更新则提示保存）
	stuPaper   m_tempPaper; 
	//当前浏览题目位置
	int		   m_viewPos;
	//窗口标题
	CString	   m_strWindowTitle;
	//用于保存当前试卷的路径
	CString    m_curPaperPath;
	//当前程序所在路径
	CString    m_currentPath;
	//按钮，贴图用的
	CBitmapButton m_btnNew;
	CBitmapButton m_btnOpen;
	CBitmapButton m_btnSave;
	CBitmapButton m_btnSaveAs;
	CBitmapButton m_btnScore;
	CBitmapButton m_btnFile;
	CBitmapButton m_btnPreview;
	CBitmapButton m_btnPrint;
	CBitmapButton m_btnNewtopic;
	CBitmapButton m_btnInsert;
	CBitmapButton m_btnLast10;
	CBitmapButton m_btnLast;
	CBitmapButton m_btnNext;
	CBitmapButton m_btnNext10;
	CBitmapButton m_btnDelete;
	CBitmapButton m_btnTopicFile;
	CBitmapButton m_btnSeprator;

private:
	//隐藏题目所有控件
	void HideAllTopicControl();
	//限制指定题目的控件
	void ShowTopicControl(const eTopicType & type);
	//tooltip设置
	BOOL SetToolTipText(UINT id, NMHDR *pTTTStruct, LRESULT *pResult);
	//显示指定题目
	void ShowFigureTopic(const stuTopic & topic,const int & pos);
	//保存当前题目
	void SaveCurTopic(const eTopicType & type);
	//检查题目是不是合法
	BOOL CheckTopicValid();
	//清空当前题目
	void CleanTopicContent();
	//打印和预览调用，将当前试卷保存为htm文件，加载htm文件显示
	void ShowHtmDialog(const stuPaper & paper,const ePaperViewType & viewType,const CString & filePath);
	//检查当前试卷是否被修改
	BOOL IsPaperModify();
	//提示用户是否保存当前正在编辑的试卷
	void PromptSave();
	//显示edit的滚动条
	void ShowEditScrollBar();
	//按钮贴图
	void BeautifyButtons();
	//设置试卷分数
	void SetPaperScore();

public:
	afx_msg void OnBnClickedRadioselect();
	afx_msg void OnBnClickedRadioblank();
	afx_msg void OnBnClickedRadioqa();
	afx_msg void OnCbnSelchangeComboselect();
	//调整控件大小
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//按钮回调
	afx_msg void OnBnClickedNew();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedSaveas();
	afx_msg void OnBnClickedScore();
	afx_msg void OnBnClickedAddfile();
	afx_msg void OnBnClickedPreview();
	afx_msg void OnBnClickedPrint();
	afx_msg void OnBnClickedNewtopic();
	afx_msg void OnBnClickedInserttopic();
	afx_msg void OnBnClickedLast10topic();
	afx_msg void OnBnClickedLasttopic();
	afx_msg void OnBnClickedNexttopic();
	afx_msg void OnBnClickedNext10topic();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedAddfiletotopic();
	afx_msg void OnBnClickedSeprator();
	afx_msg void OnCancel();
};
