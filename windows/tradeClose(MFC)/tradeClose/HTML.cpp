// HTML.cpp : 实现文件
//

#include "stdafx.h"
//#include "tradeClose.h"
#include <regex>
#include "HTML.h"
#include "autoClose.h"
#include <afxinet.h>
#include <string>
#include <map>
#include <iostream>
#include <thread>
using namespace std;

// HTML 对话框

IMPLEMENT_DYNCREATE(HTML, CDHtmlDialog)

HTML::HTML(CWnd* pParent /*=NULL*/)
: CDHtmlDialog(HTML::IDD, HTML::IDH, pParent)
, m_user_name(_T(""))
, m_seller_num_id(_T(""))
, m_login_flag(false)
, m_tb_token(_T(""))
{
	
}

HTML::~HTML()
{

}

void HTML::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL HTML::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	GetParent()->ShowWindow(SW_HIDE);
	//禁止快速登录
	Navigate(_T("https://login.taobao.com/member/login.jhtml?style=minisimple&disableQuickLogin=true"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(HTML, CDHtmlDialog)

END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(HTML)
	//DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	//DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()

//HTML 消息处理程序

HRESULT HTML::OnButtonOK(IHTMLElement* /*pElement*/)
{
	//OnOK();
	//MessageBox(_T("1111"));
	return S_OK;
}

HRESULT HTML::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	//OnCancel();
	//MessageBox(_T("1111"));
	return S_OK;
}


void HTML::OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl)
{
	CDHtmlDialog::OnDocumentComplete(pDisp, szUrl);
	CString url;
	GetCurrentUrl(url);
	if (url == _T("https://www.taobao.com/") || url == _T("https://www.taobao.com"))
	{
		Navigate(_T("https://login.taobao.com/member/login.jhtml?style=minisimple&disableQuickLogin=true"));
	}
	if (-1 != url.Find(_T("https://i.taobao.com/my_taobao.htm"))  )
	{																	
		ShowWindow(SW_HIDE);
		Navigate(_T("https://mai.taobao.com/seller_admin.htm"));
	}
	if (url == _T("https://mai.taobao.com/seller_admin.htm"))
	//登陆成功跳转到这个链接，直接比较链接来确定是否登陆成功
	{
		ShowWindow(SW_HIDE);
		//隐藏当前窗口，显示mainDlg
		CComPtr<IHTMLElement>sp_name;//用户名
		HRESULT hr_name = S_OK;
		hr_name = this->GetElementInterface(_T("seller-nav"), IID_IHTMLElement, (void**)&sp_name);
		if (hr_name != S_OK)
		{
			this->MessageBox(_T("获取登录信息失败，请重新登陆!"));
		}
		else
		{
			//从cookie中获取user_num_id，user_num_id可以不要，先暂时不获取
			m_seller_num_id = "";
			IHTMLDocument2 *htmld;
			GetDHtmlDocument(&htmld);
			BSTR tempCookies;
			htmld->get_cookie(&tempCookies);
			htmld->close();
			CString tempCookiesCS(tempCookies);
			int tb_token_start = tempCookiesCS.Find(_T("_tb_token_="));
			if (/*num_start != -1 &&*/ tb_token_start != -1)
			{				int tb_token_end = tempCookiesCS.Find(_T(";"), tb_token_start);
				if (tb_token_end != -1)
				{
					m_tb_token = tempCookiesCS.Mid(tb_token_start + 11, tb_token_end - tb_token_start - 11);
				}
				else
					MessageBox(_T("用户信息获取失败,请重试或联系开发人员!"));
			}
			else
				MessageBox(_T("用户信息获取失败,请重试或联系开发人员!"));
			::PostMessage(GetParent()->m_hWnd, WM_PARENT_HIDE, 0, 0);
			BSTR tempName;
			sp_name->get_innerText(&tempName);
			m_user_name = CString(tempName);
			int name_start = m_user_name.Find(_T("卖家手机端"));
			int name_end = m_user_name.Find(_T("退出"));
			if (name_start == -1 || name_end == -1)
			{
				MessageBox(_T("卖家用户名获取失败！"));
			}
			else
			{
				m_user_name = m_user_name.Mid(name_start + 6, name_end - name_start - 8);
				m_login_flag = true;
				MessageBoxTimeout(GetSafeHwnd(), _T("登陆成功!欢迎 ") + m_user_name, _T("登陆成功"), MB_ICONINFORMATION, GetSystemDefaultLangID(), 2000);
				::PostMessage(GetParent()->m_hWnd, WM_USERNMECHANGED, 0, 0);
			}
		}
	}
}