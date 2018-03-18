#include "stdafx.h"
#include "tradeClose.h"
#include "tradeCloseDlg.h"
#include <thread>
#include "autoClose.h"
#include "afxdialogex.h"
#include <map>
#include "HTML.h"
#include <afxinet.h>

using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
END_MESSAGE_MAP()

CtradeCloseDlg::CtradeCloseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtradeCloseDlg::IDD, pParent)
	,m_order_list(_T(""))
	,m_order_list_vector()
	,m_order_list_map()
	, m_detail(_T(""))
	,m_detailCEdit()
	,m_detail_map()
	, m_reason()
	, m_reason_cstring(_T(""))
	, m_search_name(_T(""))
	, m_tb_token(_T(""))
	,m_stop_flag(false)
	,m_count(0)
	, m_user_name(_T(""))
	, m_search_time(30 * 1000)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtradeCloseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USER_NAME, m_user_name);
	//DDX_Text(pDX, IDC_EDIT3, m_detail);//删除这个关联
	DDX_Text(pDX, IDC_EDIT1, m_order_list);
	//DDX_Control(pDX, IDC_COMBO1, m_reason);
	DDX_Control(pDX, IDC_COMBO1, m_reason);
	DDX_Text(pDX, IDC_EDIT2, m_search_name);
	DDX_Control(pDX, IDC_EDIT3, m_detailCEdit);
}

BEGIN_MESSAGE_MAP(CtradeCloseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CtradeCloseDlg::OnBnClickedButton3)
	ON_MESSAGE(WM_PARENT_HIDE, &CtradeCloseDlg::OnParentHide)
	ON_MESSAGE(WM_ORDERCHANGED, &CtradeCloseDlg::OnOrderChanged)
	ON_MESSAGE(WM_STOP, &CtradeCloseDlg::OnStop)
	ON_MESSAGE(WM_DETAILCHANGED, &CtradeCloseDlg::OnDetailChanged)
	ON_MESSAGE(WM_USERNMECHANGED, &CtradeCloseDlg::OnUserNameChanged)
	ON_BN_CLICKED(IDC_BUTTON1, &CtradeCloseDlg::OnBnClickedButton1)
//	ON_BN_CLICKED(IDC_BUTTON2, &CtradeCloseDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	//ON_BN_CLICKED(IDC_CHECK2, &CtradeCloseDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()

// CtradeCloseDlg 消息处理程序

BOOL CtradeCloseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_reason.SetCurSel(0);

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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	this->ShowWindow(SW_HIDE);

	m_html = new HTML;
	m_html->SetParent(this);
	m_html->Create(IDD_HTML);
	m_html->CenterWindow(this);
	m_html->ShowWindow(SW_NORMAL);
	//创建非模态对话框，显示

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtradeCloseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CtradeCloseDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtradeCloseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CtradeCloseDlg::OnBnClickedButton3()
{
	//这个是停止按钮，点击的话不再自动执行关单操作
	m_stop_flag = true;
}

afx_msg LRESULT CtradeCloseDlg::OnParentHide(WPARAM wParam, LPARAM lParam)
{
	ShowWindow(SW_SHOW);
	//m_flag = true;
	return S_OK;
}

afx_msg LRESULT CtradeCloseDlg::OnOrderChanged(WPARAM wParam, LPARAM lParam)
{
	UpdateData(False);
	return S_OK;
}
afx_msg LRESULT CtradeCloseDlg::OnStop(WPARAM wParam, LPARAM lParam)
{
	m_stop_flag = false;
	return S_OK;
}
afx_msg LRESULT CtradeCloseDlg::OnDetailChanged(WPARAM wParam, LPARAM lParam)
{
	m_detailCEdit.SetWindowText(m_detail);
	m_detailCEdit.LineScroll(m_detailCEdit.GetLineCount());
	UpdateData(false);
	return S_OK;
}
afx_msg LRESULT CtradeCloseDlg::OnUserNameChanged(WPARAM wParam, LPARAM lParam)
{
	m_user_name = m_html->m_user_name;
	m_tb_token = m_html->m_tb_token;
	UpdateData(False);
	return S_OK;
}

void CtradeCloseDlg::OnBnClickedButton1()
{
	//SetTimer(TIMER1, m_search_time, NULL);
	UpdateData();
	m_order_list.Empty();
	::PostMessage(this->m_hWnd, WM_ORDERCHANGED, 0, 0);
	m_order_list_map.clear();
	m_order_list_vector.clear();//开始时要清除之前存在的表单

	m_stop_flag = false;
	m_count = 0;
	m_detail_map.clear();
	::PostMessage(this->m_hWnd, WM_ORDERCHANGED, 0, 0);
	m_reason.GetLBText(m_reason.GetCurSel(), m_reason_cstring);//设置关闭原因，默认是第一个

	if (m_html->m_login_flag)//肯定要登陆成功才能操作。提示之
	{
		if (0 !=getOrderList(_T("https://trade.taobao.com/trade/itemlist/list_sold_items.htm")))
		{//要是哪儿确实有表单可以关闭
			m_order_list_vector.clear();//清除之，之后while循环的部分完全关闭他们
			::PostMessage(this->m_hWnd,WM_ORDERCHANGED,0,0);
			m_detail += CString(_T("已检索到可以关闭的订单!\r\n"));
			::PostMessage(this->m_hWnd, WM_DETAILCHANGED, 0, 0);
			while (true)
			{
				if (true == m_stop_flag)
				//按停止键,在teadeClose的地方再检测一下停止键，停止的时候要报告，自动执行多少次，一共关闭多少单
				{
					CString count;
					count.Format(_T("%d"), m_detail_map.size());
					MessageBoxTimeout(this->GetSafeHwnd(), _T("关闭成功，本次关闭订单：") + count + _T(" 个"), _T(""), MB_ICONINFORMATION, GetSystemDefaultLangID(), 5000);
					count = _T("关闭成功，本次关闭订单：") + count + _T(" 个\r\n\r\n\r\n");
					m_detail+=count;
					::PostMessage(this->m_hWnd, WM_DETAILCHANGED, 0, 0);
					break;
				}

				m_order_list_vector.clear();
				if (0 != getOrderList(_T("https://trade.taobao.com/trade/itemlist/list_sold_items.htm")))
				{
					m_detail += CString(_T("正在关闭交易...\r\n"));
					::PostMessage(this->m_hWnd, WM_DETAILCHANGED, 0, 0);
					TradeClose(m_order_list_vector);
					m_order_list_vector.clear();
				}
				else
				{
					CString count;
					count.Format(_T("%d"), m_detail_map.size());
					MessageBoxTimeout(this->GetSafeHwnd(), _T("关闭成功，本次关闭订单：") + count + _T(" 个"), _T(""), MB_ICONINFORMATION, GetSystemDefaultLangID(), 5000);
					count = _T("关闭成功，本次关闭订单：") + count + _T(" 个\r\n\r\n\r\n");
					m_detail += count;
					::PostMessage(this->m_hWnd, WM_DETAILCHANGED, 0, 0);
					break;
				}
			}
		}
		else
		{
			MessageBoxTimeout(this->GetSafeHwnd(), _T("未找到符合搜索条件\"") + m_search_name + _T("\"的订单!"), _T(""), MB_ICONINFORMATION, GetSystemDefaultLangID(), 5000);
			m_detail += CString(_T("未找到符合搜索条件\"")) + m_search_name + _T("\"的订单!\r\n");
			m_detail += CString(_T("原因可能是没有符合条件的订单或者搜索频率过高，如果是搜索频率过高，请到网页手动搜索并输验证码，再重试！\r\n\r\n"));
			::PostMessage(this->m_hWnd,WM_DETAILCHANGED,0,0);
		}
	}
	else
		MessageBox(_T("未登录成功！请退出重试"));
}

void CtradeCloseDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case TIMER1:
		//OnBnClickedButton1();
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CtradeCloseDlg::OnBnClickedCheck2()
{
	// TODO:  在此添加控件通知处理程序代码
}

int  CtradeCloseDlg::getOrderList(CString url)
{
	//取需要post的消息
	m_detail += CString(_T("正在从淘宝获取数据...\r\n"));
	::PostMessage(this->m_hWnd,WM_DETAILCHANGED,0,0);
	int first = url.Find(_T("://")) + 3;
	int count = url.Find(_T(".com")) - first + 4;
	CString m_server = (url.Mid(first, count));
	CString m_action = url.Right(url.GetLength() - first - count - 1);
	
	CString m_msg = CString(_T("event_submit_do_query=1&closeorder_flag=1&isArchive=false&isArchiveDefault=0&user_Type=1&pageNum=0&order=desc&order_Type=orderList&"))
		+ _T("isQueryMore=false&select_shop_name=&isOwnOfficialShop=false&")
		+ _T("sellerNumID=") + m_html->m_seller_num_id
		+ _T("&from_flag=&timeStamp=&sessionID=&authType=1&")
		//把要搜索的关键字插入到auctionTitle
		+ _T("auctionTitle=") + UrlEncode(m_search_name)
		+ _T("&bizOrderTimeBegin=&bizOrderHourBegin=00&bizOrderMinBegin=00&bizOrderTimeEnd=&bizOrderHourEnd=00&bizOrderMinEnd=00&buyerNick=&")
		+ _T("auctionStatus=NOT_PAID&commentStatus=ALL&")
		+ _T("bizOrderId=&logisticsService=ALL&tradeDissension=ALL&auctionType=0&queryBizType=&shopName=All&action=itemlist/QueryAction");
	CString html = SendURLPost(m_server, m_action, m_msg,CString(_T("UTF-8")));
	m_order_list += html;
	m_order_list += m_msg + m_server + m_action;
	int num=htmlToOrder(html, m_order_list_vector);
	::PostMessage(this->m_hWnd, WM_ORDERCHANGED, 0, 0);
	return num;
}

CString CtradeCloseDlg::SendURLPost(CString strServerName, CString strFormActionUrl, CString strPostStr, CString requestType)
{
	string strPostStrS = CStringA(strPostStr);
	strPostStr.ReleaseBuffer();
	CInternetSession mySession;
	CString strHeaders = _T("Content-Type: application/x-www-form-urlencoded;charset="); // 请求头
	strHeaders += requestType;
	CHttpConnection *pConnection = mySession.GetHttpConnection(strServerName);
	CHttpFile *htmlFile = pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST, strFormActionUrl);
	TCHAR sRecv[1024];
	CString strHtml;
	UINT CodePage = 936;//CP_UTF8:65001 CP_ACP:0 //GB3212 936
	if (htmlFile) {
		htmlFile->AddRequestHeaders(strHeaders);
		htmlFile->SendRequestEx(strPostStrS.length());
		htmlFile->Write((LPCTSTR)strPostStrS.c_str(), strPostStrS.length());
		htmlFile->EndRequest();
		while (htmlFile->ReadString(sRecv, 1024)) {
			int nBufferSize = MultiByteToWideChar(CodePage, 0, (LPCSTR)sRecv, -1, NULL, 0);
			wchar_t *pBuffer = new wchar_t[nBufferSize + 1];
			memset(pBuffer, 0, (nBufferSize + 1)*sizeof(wchar_t));
			//字符编码转换，乱码问题
			MultiByteToWideChar(CodePage, 0, (LPCSTR)sRecv, -1, pBuffer, nBufferSize*sizeof(wchar_t));
			strHtml += pBuffer;
			strHtml += "\r\n";
			delete pBuffer;
		}
		htmlFile->Close();
		mySession.Close();
		pConnection->Close();
		return strHtml;
	}
	return CString();
}

int CtradeCloseDlg::htmlToOrder(CString&html, vector<order_list>&order)
{
	string strHtml(CStringA(html).GetBuffer());
	for (auto&i : strHtml)
		if ('\n' == i)
			i = ' ';
	string m_order_begin("<tbody id=\"order");
	string m_order_end("</tbody>");
	//订单查找的位置
	int m_order_pos_begin = -1;
	int m_order_pos_end = 0;
	while ((m_order_pos_begin = strHtml.find(m_order_begin, m_order_pos_end)) != string::npos)
	{
		//从末尾的位置开始查找
		//确定能找到订单开始的部分，才找他的结束位置
		if ((m_order_pos_end = strHtml.find(m_order_end, m_order_pos_begin)) != string::npos)
		{
			string m_order(strHtml.begin() + m_order_pos_begin, strHtml.begin() + m_order_pos_end);
			order_list temp_order;
			string number(m_order.begin() + 16, m_order.begin() + 32);
			//MessageBox(CString(number.c_str()));
			temp_order.m_number = CString(number.c_str());
			//订单号获取成功
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//关闭链接查找部分的处理
			//找到订单号之后，要找关闭交易的链接，
			string url_begin("<div class=\"trade-actions\">");
			string url_end("</div>");
			//关闭交易链接查找的开始位置和结束位置
			int url_pos_begin = m_order.find(url_begin);
			//记录真正关闭交易的链接地址
			string url = "";
			if (string::npos != url_pos_begin)
			{
				//外层的交易状态的位置，里边包含关闭交易的地址，先获取这部分的代码，再在里边找要的地址
				int url_pos_end = string::npos;
				if ((url_pos_end = m_order.find(url_end, url_pos_begin)) != string::npos)
				{
					//链接的初始位置和结束位置
					string url_be("href=\"//");
					string url_en("\"");
					//这是这部分的strHtml代码，里边有关闭交易的地址
					string url_frame(m_order.begin() + url_pos_begin, m_order.begin() + url_pos_end);
					//MessageBox(CString(url_frame.c_str()));
					int url_begin = url_frame.find(url_be);
					if (string::npos != url_begin)
					{
						int url_end = string::npos;
						if ((url_end = url_frame.find(url_en, url_begin + 9)) != string::npos)
						{
							url = string(url_frame.begin() + url_begin + 8, url_frame.begin() + url_end);
							//MessageBox(CString(url.c_str()));
						}
					}
				}
			}
			//关闭链接查找结束
			temp_order.m_url = CString(url.c_str());
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//查找买家名字的部分
			//一个是标签的开始，一个是真正买家名字开始之前的地方，也是标签结束的位置，最后一个是买家名字查找结束的位置
			string m_name_frame_begin("<a class=\"nickname\" href=\"//member1");
			string m_name_begin("\">");
			string m_name_end("</a>");
			int m_name_frame_pos_begin = m_order.find(m_name_frame_begin);
			string name(" ");
			if (string::npos != m_name_frame_pos_begin)
			{
				int m_name_pos_begin = string::npos;
				if ((m_name_pos_begin = m_order.find(m_name_begin, m_name_frame_pos_begin)) != string::npos)
				{
					int m_name_pos_end = string::npos;
					if ((m_name_pos_end = m_order.find(m_name_end, m_name_pos_begin)) != string::npos)
					{
						name = string(m_order.begin() + m_name_pos_begin + 2, m_order.begin() + m_name_pos_end);
					}
				}
			}
			temp_order.m_name = CString(name.c_str());
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//这里要获取订单生成的时间
			string m_time("");
			string m_time_begin("<span class=\"deal-time\">");
			string m_time_end("</span>");
			int m_time_pos_begin = string::npos;
			if ((m_time_pos_begin = m_order.find(m_time_begin)))
			{
				int m_time_pos_end = string::npos;
				if ((m_time_pos_end = m_order.find(m_time_end, m_time_pos_begin)) != string::npos)
				{
					m_time = string(m_order.begin() + m_time_pos_begin + 32, m_order.begin() + m_time_pos_end);
				}
			}
			temp_order.m_time = CString(m_time.c_str());
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			order.push_back(temp_order);
		}
		else
			break;
	}
	//剔除可能不对的订单
	for (auto i = order.begin(); i != order.end();++i)
	{
		if (i->m_url.GetLength() < 10)
			i =order.erase(i);
	}
	return order.size();
}
int CtradeCloseDlg::TradeClose(vector<order_list>order)
{
	for (auto i : order)
	{
		m_detail += CString(_T("正在关闭交易...\r\n"));
		::PostMessage(this->m_hWnd,WM_DETAILCHANGED,0,0);
		CString url(i.m_url);
		int pos = url.Find(_T(".com"));
		CString m_server = (url.Left(pos + 4));
		CString m_action = url.Right(url.GetLength() - pos - 5);
		CString m_msg = CString(_T("_tb_token_="))+m_tb_token + _T("&bizType=200&") + _T("bizOrderId=")
			+ i.m_number + _T("&action=cancelOrderAction.htm&") + _T("event_submit_do_cancel=1")
			+ _T("&J_CloseReason=%ce%b4%bc%b0%ca%b1%b8%b6%bf%ee");
		CString html = SendURLPost(m_server, m_action, m_msg,CString(_T("GBK")));

		m_order_list += m_msg + m_server + m_action;

		auto it_d = m_detail_map.find(i.m_number);
		if (it_d==m_detail_map.end())
		{
			CString detail;
			detail = CString(_T("订单： ")) + i.m_number + _T(" 已关闭\r\n") + _T("关闭原因： ") + m_reason_cstring + _T("\r\n\r\n");
			m_detail_map.insert(make_pair(i.m_number, detail));
			m_detail += detail;
			++m_count;
			::PostMessage(this->m_hWnd, WM_DETAILCHANGED, 0, 0);
		}

		auto it_o = m_order_list_map.find(i.m_number);
		if (it_o==m_order_list_map.end())
		{
			m_order_list_map.insert(make_pair(i.m_number,i));
			CString order;
			order = _T("订单编号:") + i.m_number + _T("  买家昵称:") + i.m_name + _T("  订单生成时间")
				+ i.m_time + _T("地址： ")+i.m_url+_T("\r\n\r\n\r\n");
			m_order_list += order;
			::PostMessage(this->m_hWnd, WM_ORDERCHANGED, 0, 0);
		}
		if (true == m_stop_flag)
			//按停止键,在teadeClose的地方再检测一下停止键，停止的时候要报告，自动执行多少次，一共关闭多少单
		{
			CString count;
			count.Format(_T("%d"), m_detail_map.size());
			MessageBoxTimeout(this->GetSafeHwnd(), _T("关闭成功，本次关闭订单：") + count + _T(" 个"), _T(""), MB_ICONINFORMATION, GetSystemDefaultLangID(), 5000);
			count = _T("关闭成功，本次关闭订单：") + count + _T(" 个\r\n\r\n\r\n");
			m_detail += count;
			::PostMessage(this->m_hWnd, WM_DETAILCHANGED, 0, 0);
			break;
		}
		Sleep(100);
	}
	return 0;
}

CString CtradeCloseDlg::UrlEncode(CString strUnicode)
{
	LPCWSTR unicode = T2CW(strUnicode);
	int len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, 0, 0, 0, 0);
	if (!len)
		return strUnicode;
	char *utf8 = new char[len + 1];
	char *utf8temp = utf8;
	WideCharToMultiByte(CP_UTF8, 0, unicode, -1, utf8, len + 1, 0, 0);
	utf8[len] = NULL;
	CString strTemp, strEncodeData;
	while (*utf8 != '\0') {
		strTemp.Format(_T("%%%2X"), (BYTE)*utf8);
		strEncodeData += strTemp;
		++utf8;
	}
	delete[]utf8temp;
	return CString(strEncodeData);
}