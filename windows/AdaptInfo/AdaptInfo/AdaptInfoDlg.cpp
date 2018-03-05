
// AdaptInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AdaptInfo.h"
#include "AdaptInfoDlg.h"
#include "afxdialogex.h"
#include <WS2tcpip.h>
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAdaptInfoDlg 对话框



CAdaptInfoDlg::CAdaptInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADAPTINFO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdaptInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAdaptInfoDlg::OnPaint()
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
HCURSOR CAdaptInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_MESSAGE_MAP(CAdaptInfoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INFO, &CAdaptInfoDlg::OnBnClickedInfo)
	ON_BN_CLICKED(IDC_Adress, &CAdaptInfoDlg::OnBnClickedAdress)
END_MESSAGE_MAP()

// CAdaptInfoDlg 消息处理程序
BOOL CAdaptInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	((CEdit*)GetDlgItem(IDC_EDIT))->ShowScrollBar(SB_VERT);
	((CButton*)GetDlgItem(IDC_INFO))->SetCheck(TRUE);
	ShowAdaptersInfo();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAdaptInfoDlg::ShowAdaptersInfo()
{
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter = NULL;
	DWORD errValue = 0;
	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	pAdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
	if (!pAdapterInfo)//malloc失败
		return;
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) //空间不够，重新分配
	{
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
		if (!pAdapterInfo) //malloc失败
			return;
	}
	CString info;
	if ((errValue = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
	{
		pAdapter = pAdapterInfo;
		while (pAdapter)
		{
			info += CString(_T("Adapter Name:")) + CString(pAdapter->AdapterName) + CString(_T("\r\n"));//名字
			info += CString(_T("Adapter Desc:")) + CString(pAdapter->Description) + CString(_T("\r\n"));//描述
			CString mac;
			mac.Format(_T("%02X%02X%02X%02X%02X%02X"), pAdapter->Address[0], pAdapter->Address[1], \
				pAdapter->Address[2], pAdapter->Address[3], pAdapter->Address[4], pAdapter->Address[5]);
			info += CString(_T("Adapter Mac:")) + mac + CString(_T("\r\n"));//MAC地址
			CString type;
			switch (pAdapter->Type) //类型，列举了几种
			{
			case MIB_IF_TYPE_OTHER:
				type = _T("其他");
				break;
			case MIB_IF_TYPE_ETHERNET:
				type = _T("以太网接口");
				break;
			case IF_TYPE_ISO88025_TOKENRING:
				type = _T("ISO88025令牌环");
				break;
			case MIB_IF_TYPE_PPP:
				type = _T("PPP接口");
				break;
			case MIB_IF_TYPE_LOOPBACK:
				type = _T("软件回路接口");
				break;
			case MIB_IF_TYPE_SLIP:
				type = _T("ATM网络接口");
				break;
			case IF_TYPE_IEEE80211:
				type = _T("无线网络接口");
				break;
			default:
				type = _T("未知接口");
				break;
			}
			info += CString(_T("网卡类型：")) + type + CString(_T("\r\n"));
			info += CString(_T("IP地址：")) + CString(pAdapter->IpAddressList.IpAddress.String) + CString(_T("\r\n"));
			info += CString(_T("子网掩码：")) + CString(pAdapter->IpAddressList.IpMask.String) + CString(_T("\r\n"));
			info += CString(_T("默认网关：")) + CString(pAdapter->GatewayList.IpAddress.String) + CString(_T("\r\n"));
			info += CString(_T("是否DHCP：")) + CString(pAdapter->DhcpEnabled ? _T("是") : _T("否")) + CString(_T("\r\n"));
			info += CString(_T("DHCP地址：")) + CString(pAdapter->DhcpServer.IpAddress.String) + CString(_T("\r\n"));
			//Dns
			IP_PER_ADAPTER_INFO* pPerAdapt = NULL;
			ULONG ulLen = 0;
			int err = GetPerAdapterInfo(pAdapter->Index, pPerAdapt, &ulLen);
			if (err == ERROR_BUFFER_OVERFLOW)
			{
				pPerAdapt = (IP_PER_ADAPTER_INFO*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ulLen);
				err = GetPerAdapterInfo(pAdapter->Index, pPerAdapt, &ulLen);
				if (err == ERROR_SUCCESS)
				{
					IP_ADDR_STRING* pNext = &(pPerAdapt->DnsServerList);
					if (pNext && strcmp(pNext->IpAddress.String, "") != 0)//手动DNS
					{
						info = info + CString(_T("DNS：")) + CString(pNext->IpAddress.String) + _T("\r\n");
						if (pNext->Next)
						{
							pNext = pNext->Next;
							info = info + CString(_T("备用DNS：")) + CString(pNext->IpAddress.String) + _T("\r\n");
						}
					}
				}
				HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, pPerAdapt);
			}
			info += "\r\n";
			pAdapter = pAdapter->Next;
		}
	}
	else
	{
		CString s;
		s.Format(_T("GetAdaptersInfo failed with error: %d\r\n"), errValue);
		info += s;
	}
	if (pAdapterInfo)
		free(pAdapterInfo);
	SetDlgItemText(IDC_EDIT, info);
}

void CAdaptInfoDlg::ShowAdaptersAddresses()
{
	//关于这个标志，查 MSDN 吧。。。
	ULONG flags = GAA_FLAG_INCLUDE_PREFIX | GAA_FLAG_INCLUDE_GATEWAYS;//包括 IPV4 ，IPV6 网关
	ULONG family = AF_UNSPEC;//返回包括 IPV4 和 IPV6 地址
	PIP_ADAPTER_ADDRESSES pAddresses = NULL;
	ULONG outBufLen = 0;
	DWORD dwRetVal = 0;
	PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
	PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
	PIP_ADAPTER_ANYCAST_ADDRESS pAnycast = NULL;
	PIP_ADAPTER_MULTICAST_ADDRESS pMulticast = NULL;
	IP_ADAPTER_DNS_SERVER_ADDRESS *pDnServer = NULL;
	IP_ADAPTER_PREFIX *pPrefix = NULL;
	outBufLen = 15000;
	do
	{
		pAddresses = (IP_ADAPTER_ADDRESSES *)malloc(outBufLen);
		if (pAddresses == NULL)
			return;
		dwRetVal = GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);
		if (dwRetVal == ERROR_BUFFER_OVERFLOW)
		{
			free(pAddresses);
			pAddresses = NULL;
		}
		else
			break;
	} while (dwRetVal == ERROR_BUFFER_OVERFLOW);
	CString info;
	if (dwRetVal == NO_ERROR)
	{
		pCurrAddresses = pAddresses;
		while (pCurrAddresses)
		{
			info += CString(_T("Adapter name:")) + pCurrAddresses->AdapterName + CString(_T("\r\n"));
			info += CString(_T("Description:")) + CString(pCurrAddresses->Description) + CString(_T("\r\n"));
			info += CString(_T("Friendly name:")) + CString(pCurrAddresses->FriendlyName) + CString(_T("\r\n"));
			if (pCurrAddresses->PhysicalAddressLength != 0)
			{
				CString mac;//其实 MAC 地址的长度存在 PhysicalAddressLength 中，最好用它来确定格式化的长度
				mac.Format(_T("%02X%02X%02X%02X%02X%02X"), pCurrAddresses->PhysicalAddress[0], pCurrAddresses->PhysicalAddress[1], \
					pCurrAddresses->PhysicalAddress[2], pCurrAddresses->PhysicalAddress[3], pCurrAddresses->PhysicalAddress[4], \
					pCurrAddresses->PhysicalAddress[5]);
				info += CString(_T("Adapter Mac:")) + mac + CString(_T("\r\n"));//MAC地址
			}
			CString type;
			switch (pCurrAddresses->IfType) //类型，列举了几种
			{
			case MIB_IF_TYPE_ETHERNET:
				type = _T("以太网接口");
				break;
			case MIB_IF_TYPE_PPP:
				type = _T("PPP接口");
				break;
			case MIB_IF_TYPE_LOOPBACK:
				type = _T("软件回路接口");
				break;
			case MIB_IF_TYPE_SLIP:
				type = _T("ATM网络接口");
				break;
			case IF_TYPE_IEEE80211:
				type = _T("无线网络接口");
				break;
			}
			info += CString(_T("网卡类型：")) + type + CString(_T("\r\n"));
			pUnicast = pCurrAddresses->FirstUnicastAddress;
			while (pUnicast)//单播IP
			{
				CHAR IP[130] = { 0 };
				if (AF_INET == pUnicast->Address.lpSockaddr->sa_family)// IPV4 地址，使用 IPV4 转换
					inet_ntop(PF_INET, &((sockaddr_in*)pUnicast->Address.lpSockaddr)->sin_addr, IP, sizeof(IP));
				else if (AF_INET6 == pUnicast->Address.lpSockaddr->sa_family)// IPV6 地址，使用 IPV6 转换
					inet_ntop(PF_INET6, &((sockaddr_in6*)pUnicast->Address.lpSockaddr)->sin6_addr, IP, sizeof(IP));
				info += CString(_T("单播IP：")) + CString(IP) + CString(_T("\r\n"));
				pUnicast = pUnicast->Next;
			}
			if (pCurrAddresses->Dhcpv4Server.lpSockaddr)//DHCP服务器地址
			{
				CHAR dhcp[130] = { 0 };
				if (AF_INET == pCurrAddresses->Dhcpv4Server.lpSockaddr->sa_family)
					inet_ntop(PF_INET, &((sockaddr_in*)pCurrAddresses->Dhcpv4Server.lpSockaddr)->sin_addr, dhcp, sizeof(dhcp));
				else if (AF_INET6 == pCurrAddresses->Dhcpv4Server.lpSockaddr->sa_family)
					inet_ntop(PF_INET6, &((sockaddr_in6*)pCurrAddresses->Dhcpv4Server.lpSockaddr)->sin6_addr, dhcp, sizeof(dhcp));
				info += CString(_T("DHCP地址：")) + CString(dhcp) + CString(_T("\r\n"));
			}
			pDnServer = pCurrAddresses->FirstDnsServerAddress;
			while (pDnServer)//DNS
			{
				CHAR DNS[130] = { 0 };
				if (AF_INET == pDnServer->Address.lpSockaddr->sa_family)
					inet_ntop(PF_INET, &((sockaddr_in*)pDnServer->Address.lpSockaddr)->sin_addr, DNS, sizeof(DNS));
				else if (AF_INET6 == pDnServer->Address.lpSockaddr->sa_family)
					inet_ntop(PF_INET6, &((sockaddr_in6*)pDnServer->Address.lpSockaddr)->sin6_addr, DNS, sizeof(DNS));
				info += CString(_T("DNS：")) + CString(DNS) + CString(_T("\r\n"));
				pDnServer = pDnServer->Next;
			}
			CString MTU;// MTU 
			MTU.Format(_T("MTU：%d\r\n"), pCurrAddresses->Mtu);
			info += MTU;
			CString sendSpeend;//发送速率
			sendSpeend.Format(_T("send speed:%d\r\n"), pCurrAddresses->TransmitLinkSpeed);
			info += sendSpeend;
			CString recvSpeed;//接收速率
			recvSpeed.Format(_T("recv speed:%d\r\n"), pCurrAddresses->ReceiveLinkSpeed);
			info += recvSpeed;
			auto pGetway = pCurrAddresses->FirstGatewayAddress;
			while (pGetway)//网关
			{
				CHAR getway[130] = { 0 };
				if (AF_INET == pGetway->Address.lpSockaddr->sa_family)
					inet_ntop(PF_INET, &((sockaddr_in*)pGetway->Address.lpSockaddr)->sin_addr, getway, sizeof(getway));
				else if (AF_INET6 == pGetway->Address.lpSockaddr->sa_family)
					inet_ntop(PF_INET6, &((sockaddr_in6*)pGetway->Address.lpSockaddr)->sin6_addr, getway, sizeof(getway));
				info += CString(_T("Getway：")) + CString(getway) + CString(_T("\r\n"));
				pGetway = pGetway->Next;
			}
			if (pCurrAddresses->Dhcpv6Server.lpSockaddr)//IPV6DHCP
			{
				CHAR dhcpv6[130] = { 0 };
				if (AF_INET6 == pCurrAddresses->Dhcpv6Server.lpSockaddr->sa_family)
				{
					inet_ntop(PF_INET6, &((sockaddr_in6*)pCurrAddresses->Dhcpv6Server.lpSockaddr)->sin6_addr, dhcpv6, sizeof(dhcpv6));
					info += CString(_T("DHCPV6：")) + CString(dhcpv6) + CString(_T("\r\n"));
				}
			}
			info += CString(_T("\r\n"));
			pCurrAddresses = pCurrAddresses->Next;
		}
	}
	else
	{
		CString s;
		s.Format(_T("GetAdaptersAddresses failed,error code:%d"), GetLastError());
		AfxMessageBox(s);
	}
	if (pAddresses)
		free(pAddresses);
	SetDlgItemText(IDC_EDIT, info);
}

void CAdaptInfoDlg::OnBnClickedInfo()
{
	ShowAdaptersInfo();
}

void CAdaptInfoDlg::OnBnClickedAdress()
{
	ShowAdaptersAddresses();
}