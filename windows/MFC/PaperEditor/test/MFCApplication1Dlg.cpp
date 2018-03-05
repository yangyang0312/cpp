
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框

BEGIN_DHTML_EVENT_MAP(CMFCApplication1Dlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()


CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(IDD_MFCAPPLICATION1_DIALOG, IDR_HTML_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFCApplication1Dlg,CDHtmlDialog)
	//DISP_FUNCTION(CMFCApplication1Dlg,"TestFunction",TestFunction,VT_EMPTY,VTS_VARIANT VTS_VARIANT)
	DISP_FUNCTION(CMFCApplication1Dlg,"openFunction",openFunction,VT_EMPTY,VTS_VARIANT)
	DISP_FUNCTION(CMFCApplication1Dlg,"saveFunction",saveFunction,VT_EMPTY,VTS_VARIANT)
END_DISPATCH_MAP()


void CMFCApplication1Dlg::openFunction(VARIANT & vs1)
{
	CComVariant v1(vs1);
	v1.ChangeType(VT_BSTR);
	CString s;
	s = s + v1.bstrVal;
	OutputDebugStringW(s);
	TCHAR buf[256] = {0};
	GetCurrentDirectoryW(256,buf);
	CString t = CString(_T("/c start ")) + v1.bstrVal;
	OutputDebugStringW(t);
	SHELLEXECUTEINFO sei;
	ZeroMemory(&sei,sizeof(SHELLEXECUTEINFO));
	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	sei.lpFile = _T("cmd.exe");
	sei.nShow = SW_HIDE;
	sei.lpVerb = _T("open");
	sei.lpParameters = t;
	if(!ShellExecuteEx(&sei))
	{
		CString s;
		s.Format(_T("ShellExecuteEx error,error code:%d"),GetLastError());
		MessageBox(s);
	}
}

void CMFCApplication1Dlg::saveFunction(VARIANT & vs1)
{
	CString fileName(vs1.bstrVal);
	CString szFilter(_T("所有文件(*.*)|*.*||"));
	CFileDialog fileDlg(FALSE,_T("txt"),fileName,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter,this);
	if(IDOK == fileDlg.DoModal())
	{
		CString filePath = fileDlg.GetPathName();
		CopyFile(fileName,filePath,FALSE);//覆盖
	}
}

// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	//
	//IHTMLDocument2 * doc;
	////GetDHtmlDocument(&doc);
	////BSTR content[4096] = {0};
	////doc->toString(content);
	////OutputDebugStringW((WCHAR*)(content));
	//
	//GetDHtmlDocument()
	//
	//IHTMLElement* pBody;
	//hr = pMSHTML->get_body(&pBody);  // pMSHTML是IHtmlDocument2接口指针,例如从CHtmlView中得到的
	//if(SUCCEEDED(hr))
	//{
	//	BSTR bstrText;
	//	hr = pBody->get_innerText(&bstrText);
	//	if(SUCCEEDED(hr))
	//	{
	//		PrintBSTR(bstrText);  // 处理得到的文本
	//		SysFreeString(bstrText);
	//	}
	//	pBody->Release();
	//}

	//IHTMLDocument2* pDocument;
	//IHTMLWindow2* pWindow;
	////获得 html 的 Document 节点
	//HRESULT hr = GetDHtmlDocument(&pDocument);
	////获得 Document 的窗口节点
	//pDocument->get_parentWindow(&pWindow);
	//
	//IHTMLElement * doc;
	//pDocument->get_body(&doc);
	//BSTR content[4096] = {0};
	//doc->toString(content);
	//OutputDebugStringW((WCHAR*)(content));
	//
	//
	//pDocument->Release();
	//pWindow->Release();
	//
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	EnableAutomation();
	SetExternalDispatch(GetIDispatch(TRUE));

	TCHAR buf[256] = {0};
	GetCurrentDirectoryW(256,buf);
	CString path = _T("file:///");
	path = path + buf + _T("/test.htm");
	Navigate(path);
	OutputDebugStringW(path);




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CMFCApplication1Dlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	//OnOK();
	IHTMLElement * sp_name;//用户名
	HRESULT hr_name = S_OK;
	hr_name = this->GetElementInterface(_T("btn_print"),IID_IHTMLElement,(void**)&sp_name);
	if(hr_name != S_OK)
	{
		this->MessageBox(_T("获取登录信息失败，请重新登陆!"));
	}
	else
	{
		sp_name->click();
		IHTMLDocument2 *htmld;
		GetDHtmlDocument(&htmld);

		BSTR tempName;
		BSTR tempName1;
		sp_name->get_outerHTML(&tempName);
		OutputDebugStringW(tempName);
		sp_name->get_innerText(&tempName1);
		OutputDebugStringW(tempName1);

		//IHTMLFramesCollection2 * coll;
		IHTMLElementCollection * coll;
		htmld->get_all(&coll);
		//BSTR b;
		//coll->toString(&b);
		//OutputDebugStringW(b);
		long l;
		coll->get_length(&l);
		//CString s;
		//s.Format(_T("len:%d"), l);
		//OutputDebugStringW(s);
		//VARIANT varIndex, var2;
		//for (int i = 0;i < l;++i)
		//{
		//	OutputDebugStringW(L"wwww");
		//	varIndex.vt = VT_UINT;
		//	varIndex.lVal = 0;
		//	VariantInit(&var2);
		//	IDispatch  * elem;
		//	coll->item(varIndex, var2, &elem);
		//	if (elem)
		//	{
		//		BSTR s;
		//		((IHTMLFormElement *)elem)->get_name(&s);
		//		OutputDebugStringW(s);
		//	}
		//	IHTMLFormElement * form;
		//	elem->QueryInterface<IHTMLFormElement>(&form);
		//	if (form)
		//	{
		//		BSTR s;
		//		form->get_name(&s);
		//		OutputDebugStringW(s);
		//	}
		//}




		//BSTR tempCookies;
		//htmld->get_cookie(&tempCookies);
		//htmld->close();
		//CString tempCookiesCS(tempCookies);
		//int tb_token_start = tempCookiesCS.Find(_T("_tb_token_="));
		//if(/*num_start != -1 &&*/ tb_token_start != -1)
		//{
		//	int tb_token_end = tempCookiesCS.Find(_T(";"),tb_token_start);
		//	if(tb_token_end != -1)
		//	{
		//		m_tb_token = tempCookiesCS.Mid(tb_token_start + 11,tb_token_end - tb_token_start - 11);
		//	}
		//	else
		//		MessageBox(_T("用户信息获取失败,请重试或联系开发人员!"));
		//}
		//else
		//	MessageBox(_T("用户信息获取失败,请重试或联系开发人员!"));
		//::PostMessage(GetParent()->m_hWnd,WM_PARENT_HIDE,0,0);
		//m_user_name = CString(tempName);
		//int name_start = m_user_name.Find(_T("卖家手机端"));
		//int name_end = m_user_name.Find(_T("退出"));
		//if(name_start == -1 || name_end == -1)
		//{
		//	MessageBox(_T("卖家用户名获取失败！"));
		//}
		//else
		//{
		//	m_user_name = m_user_name.Mid(name_start + 6,name_end - name_start - 8);
		//	m_login_flag = true;
		//	MessageBoxTimeout(GetSafeHwnd(),_T("登陆成功!欢迎 ") + m_user_name,_T("登陆成功"),MB_ICONINFORMATION,GetSystemDefaultLangID(),2000);
		//	::PostMessage(GetParent()->m_hWnd,WM_USERNMECHANGED,0,0);
		//}
	}

	return S_OK;
}

HRESULT CMFCApplication1Dlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	//OnCancel();
	SendMessage(WM_IME_NOTIFY,IMN_OPENSTATUSWINDOW,0);
	return S_OK;
}
