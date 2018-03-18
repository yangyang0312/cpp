#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CDHtmlDialog。"
#endif 
#include "resource.h"

#include<vector>

#define WM_PARENT_HIDE WM_USER+1
#define WM_ORDERCHANGED WM_USER+2
#define WM_DETAILCHANGED WM_USER+3
#define WM_USERNMECHANGED WM_USER+4
#define WM_STOP WM_USER+5
#include <map>
// HTML 对话框

using namespace std;

typedef struct order_list
{
	CString m_name;//这个装买家名字
	CString m_number;//这个装订单号
	CString m_url;//这个装链接
	CString m_time;//这个装订单生成时间
}order_list;

// typedef struct detail
// {
// 	CString m_reason;
// 	CString m_statu;
// }detail;

class HTML : public CDHtmlDialog
{
	DECLARE_DYNCREATE(HTML)

public:
	HTML(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~HTML();
// 重写
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// 对话框数据
	enum { IDD = IDD_HTML, IDH = IDR_HTML_HTML };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()

	void OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl);
public:
	CString m_user_name;
protected:
public:
	CString m_seller_num_id;
	// 登陆是否成功
	bool m_login_flag;
	// 这个东西冲cookie中获取，需要post出去的
	CString m_tb_token;
};
