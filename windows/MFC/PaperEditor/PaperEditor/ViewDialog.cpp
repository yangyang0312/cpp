// ViewDialog.cpp : 实现文件
//
#include "stdafx.h"
#include "ViewDialog.h"
#include "../AnalyzeHtm/AnalyzeHtm.h"

// CViewDialog 对话框
IMPLEMENT_DYNCREATE(CViewDialog, CDHtmlDialog)

CViewDialog::CViewDialog(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog((UINT)0,0,pParent)
{
	m_bCanClose = FALSE;
}

CViewDialog::CViewDialog(UINT idDlg,UINT idHtm,const stuPaper &paper,const ePaperViewType & type,const CString & filePath,CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(idDlg,idHtm,pParent)
{
	m_filePath = filePath;
	m_type = type;
	m_pPaper = &paper;
	m_bCanClose = FALSE;
}

CViewDialog::~CViewDialog()
{
}

void CViewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL CViewDialog::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	//允许js调用c++函数
	EnableAutomation();
	SetExternalDispatch(GetIDispatch(TRUE));	//函数传递
	if(m_type == ePaperViewTypePrint || m_type == ePaperViewTypeExcel)			//打印隐藏界面
		SetWindowPos(&wndBottom,0,0,0,0,0);
	else                                        //全屏
		//SetWindowPos(&wndTopMost,0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),0);
		SetWindowPos(&wndTopMost,0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),SWP_NOZORDER);
	if(!m_filePath.IsEmpty())
		Navigate(m_filePath);					//加载
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(CViewDialog, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CViewDialog)
	DHTML_EVENT_ONCLICK(_T("btn_close"),On_btn_close)
	DHTML_EVENT_ONCLICK(_T("btn_submit"),On_btn_submit)
END_DHTML_EVENT_MAP()
//js调用c++代码，函数绑定
BEGIN_DISPATCH_MAP(CViewDialog, CDHtmlDialog)
	DISP_FUNCTION(CViewDialog, "close_window", close_window, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CViewDialog, "set_answer_score", set_answer_score, VT_EMPTY, VTS_VARIANT VTS_VARIANT VTS_VARIANT)
END_DISPATCH_MAP()

VOID CViewDialog::set_answer_score(VARIANT & row, VARIANT & col, VARIANT & value)			//返回答卷分数
{
	CString s;
	s.Format("func:%s row:%d col:%d value:%s", __FUNCTION__, row.intVal, col.intVal, CString(value.bstrVal));
	OutputDebugString(s);
	if (row.intVal == 1)	//目前只保存一个学生的信息
		m_score.push_back(atof(CString(value.bstrVal)));
}
void CViewDialog::close_window()
{	//打印完毕后关闭窗口，不然会阻塞主窗口
	m_bCanClose = TRUE;
	OnOK();
}
// 教师端预览时  点击关闭页面
HRESULT CViewDialog::On_btn_close(IHTMLElement* /*pElement*/)
{
	m_bCanClose = TRUE;
	OnOK();
	return S_OK;
}
//学生考试时  点击提交按钮
HRESULT CViewDialog::On_btn_submit(IHTMLElement* /*pElement*/)
{
	CAnalyzeHtm analyze;
	analyze.GetPaperAnswer(m_answer,*m_pPaper,this);
	m_bCanClose = TRUE;
	OnOK();
	return S_OK;
}
//加载完成  打印
void CViewDialog::OnDocumentComplete(LPDISPATCH pDisp,LPCTSTR szUrl)
{
	CDHtmlDialog::OnDocumentComplete(pDisp,szUrl);
	if(m_type == ePaperViewTypePrint)
	{
		CString url;
		GetCurrentUrl(url);			//获取URL
		if(url.CompareNoCase(m_filePath.Right(m_filePath.GetLength() - 8)) == 0)	//加载完成
		{
			CComPtr<IHTMLElement> sp_name;
			if(GetElementInterface("btn_print",IID_IHTMLElement,(void**)&sp_name) == S_OK)//获取到打印按钮，按一下
				sp_name->click();
		}
	}
}
//屏蔽各种退出方式，只能在点击特定按钮后退出
void CViewDialog::OnOK()
{
	if(m_bCanClose)
		CDHtmlDialog::OnOK();
}
void CViewDialog::OnCancel()
{
}
LRESULT CViewDialog::WindowProc(UINT message,WPARAM wParam,LPARAM lParam)
{
	if(message == WM_USER + 145)		//此消息只是在学生端使用，为了在学生端、教师端、试卷编辑器复用这个对话框，使用了WM_USER + 145，它与学生端定义的WM_SUBMITPAPER值相等
	{
		On_btn_submit(NULL);
		return 0;
	}
	return CDHtmlDialog::WindowProc(message,wParam,lParam);
}
//右键屏蔽
HRESULT STDMETHODCALLTYPE CViewDialog::ShowContextMenu(DWORD dwID,POINT *ppt,IUnknown *pcmdtReserved,IDispatch *pdispReserved)
{
	return S_OK;
}