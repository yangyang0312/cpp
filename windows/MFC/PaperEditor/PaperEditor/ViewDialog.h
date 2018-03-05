#pragma once
#include "PaperStruct.h"
#include <vector>
#ifdef _WIN32_WCE
#error "Windows CE 不支持 CDHtmlDialog。"
#endif 
/*
试卷编辑器、教师端、学生端共用的加载查看htm的类，使用时在各个项目中添加htm需要的dlg和htm，使用时在构造函数中传入ID
*/
// CViewDialog 对话框
class CViewDialog : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CViewDialog)

public:
	CViewDialog(CWnd* pParent = NULL);   // 标准构造函数
	CViewDialog(UINT idDlg,UINT idHtm,const stuPaper &paper,const ePaperViewType & type, const CString & filePath,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CViewDialog();
// 重写
	HRESULT On_btn_close(IHTMLElement *pElement);
	HRESULT On_btn_submit(IHTMLElement* pElement);

	//关闭退出界面
	void close_window();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIEWDIALOG, IDH = IDR_HTML_VIEWDIALOG };
#endif

protected:
	virtual BOOL CanAccessExternal(){ return TRUE; };			//屏蔽“在此页上的ActiveX控件和本页上的其他部分的交互可能不安全,然而调excel还是弹
	//virtual BOOL IsExternalDispatchSafe(){ return TRUE; }		//默认允许activex
	void	OnDocumentComplete(LPDISPATCH pDisp,LPCTSTR szUrl);	//加载完成
	virtual void DoDataExchange(CDataExchange* pDX);			// DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual LRESULT WindowProc(UINT message,WPARAM wParam,LPARAM lParam);	//消息处理
	virtual HRESULT STDMETHODCALLTYPE ShowContextMenu(DWORD dwID,POINT *ppt,IUnknown *pcmdtReserved,IDispatch *pdispReserved);//屏蔽右键

private:
	//加载的htm路径
	CString m_filePath;
	//显示类型，打印的使用要用到
	ePaperViewType m_type;
	//试卷
	const stuPaper * m_pPaper;
	//点击特定按钮后，可以关闭对话框
	BOOL m_bCanClose;

private:
	VOID set_answer_score(VARIANT & row, VARIANT & col, VARIANT & value);			//返回答卷分数

public:
	//答案结构
	stuPaper m_answer;
	//教师给分
	std::vector<double> m_score;

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
	DECLARE_DISPATCH_MAP()
public:
	//屏蔽各种退出方式，只能在点击特定按钮后退出
	virtual void OnOK();
	virtual void OnCancel();
};
