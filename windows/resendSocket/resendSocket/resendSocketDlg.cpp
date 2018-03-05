
// resendSocketDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "resendSocket.h"
#include "resendSocketDlg.h"
#include "afxdialogex.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CresendSocketDlg 对话框



CresendSocketDlg::CresendSocketDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RESENDSOCKET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CresendSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CresendSocketDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CresendSocketDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CresendSocketDlg::OnBnClickedButton2)
	ON_MESSAGE(WM_SENDMSG, &CresendSocketDlg::OnSendmsg)
	ON_BN_CLICKED(IDC_BUTTON3, &CresendSocketDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CresendSocketDlg 消息处理程序

BOOL CresendSocketDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_thread = INVALID_HANDLE_VALUE;

	m_run = TRUE;
	if (INVALID_HANDLE_VALUE == m_thread)
	{
		CWinThread *tthread = AfxBeginThread(CresendSocketDlg::ResendThread, this);
		m_thread = tthread->m_hThread;
	}
	else
	{
		m_run = FALSE;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

// void hex(unsigned long int k, char *dst, int&pos)
// {
// 	unsigned long int hex[4];
// 	int i;
// 	for (i = 0;i < 4;i++)
// 	{
// 		hex[i] = k & 0x00ff;
// 		k >>= 8;
// 		sprintf(dst + pos, "%02X", hex[i]);
// 		pos += 2;
// 		//printf("%02X", hex[i]);
// 	}
// }
// 
// void MD5(const char *src, int srcLen, char*dst, int dstLen)
// {
// 	unsigned long int a, b, c, d, a0, b0, c0, d0;
// 	int slen, wlen, i, j = 4;
// 	long int *X, r;
// 
// 	slen = strlen(src);
// 	wlen = (((slen + 8) >> 6) + 1) << 4;
// 	X = (long int *)malloc(sizeof(long int));
// 
// 	for (i = 0;(i * 4) < slen;i++)
// 	{
// 		X[i] = 0;
// 		for (j = 0;(j < 4) && ((i * 4 + j) < slen);j++)
// 		{
// 			switch (j)
// 			{
// 			case 2:  r = src[i * 4 + j] << 8;r <<= 8;break;
// 			case 3:  r = src[i * 4 + j] << 8;r <<= 8;r <<= 8;break;
// 			default: r = src[i * 4 + j] << (j * 8);break;
// 			}
// 			X[i] += r;
// 		}
// 	}
// 
// 	if (j == 4)
// 		X[i++] = 0x80;
// 	else
// 	{
// 		switch (j)
// 		{
// 		case 2:  r = 0x80L << 8;r <<= 8;break;
// 		case 3:  r = 0x80L << 8;r <<= 8;r <<= 8;break;
// 		default: r = 0x80L << (j * 8);break;
// 		}
// 		X[i - 1] += r;
// 	}
// 	for (;i < wlen;i++)
// 		X[i] = 0;
// 	X[wlen - 2] = slen * 8;
// 
// 	a = 0x67452301;
// 	b = 0xefcdab89;
// 	c = 0x98badcfe;
// 	d = 0x10325476;
// 	for (i = 0;i < wlen;i += 16)
// 	{
// 		a0 = a;
// 		b0 = b;
// 		c0 = c;
// 		d0 = d;
// 
// 		a = R1(a, b, c, d, X[i + 0], 7, 0xd76aa478);
// 		d = R1(d, a, b, c, X[i + 1], 12, 0xe8c7b756);
// 		c = R1(c, d, a, b, X[i + 2], 17, 0x242070db);
// 		b = R1(b, c, d, a, X[i + 3], 22, 0xc1bdceee);
// 		a = R1(a, b, c, d, X[i + 4], 7, 0xf57c0faf);
// 		d = R1(d, a, b, c, X[i + 5], 12, 0x4787c62a);
// 		c = R1(c, d, a, b, X[i + 6], 17, 0xa8304613);
// 		b = R1(b, c, d, a, X[i + 7], 22, 0xfd469501);
// 		a = R1(a, b, c, d, X[i + 8], 7, 0x698098d8);
// 		d = R1(d, a, b, c, X[i + 9], 12, 0x8b44f7af);
// 		c = R1(c, d, a, b, X[i + 10], 17, 0xffff5bb1);
// 		b = R1(b, c, d, a, X[i + 11], 22, 0x895cd7be);
// 		a = R1(a, b, c, d, X[i + 12], 7, 0x6b901122);
// 		d = R1(d, a, b, c, X[i + 13], 12, 0xfd987193);
// 		c = R1(c, d, a, b, X[i + 14], 17, 0xa679438e);
// 		b = R1(b, c, d, a, X[i + 15], 22, 0x49b40821);
// 
// 		a = R2(a, b, c, d, X[i + 1], 5, 0xf61e2562);
// 		d = R2(d, a, b, c, X[i + 6], 9, 0xc040b340);
// 		c = R2(c, d, a, b, X[i + 11], 14, 0x265e5a51);
// 		b = R2(b, c, d, a, X[i + 0], 20, 0xe9b6c7aa);
// 		a = R2(a, b, c, d, X[i + 5], 5, 0xd62f105d);
// 		d = R2(d, a, b, c, X[i + 10], 9, 0x2441453);
// 		c = R2(c, d, a, b, X[i + 15], 14, 0xd8a1e681);
// 		b = R2(b, c, d, a, X[i + 4], 20, 0xe7d3fbc8);
// 		a = R2(a, b, c, d, X[i + 9], 5, 0x21e1cde6);
// 		d = R2(d, a, b, c, X[i + 14], 9, 0xc33707d6);
// 		c = R2(c, d, a, b, X[i + 3], 14, 0xf4d50d87);
// 		b = R2(b, c, d, a, X[i + 8], 20, 0x455a14ed);
// 		a = R2(a, b, c, d, X[i + 13], 5, 0xa9e3e905);
// 		d = R2(d, a, b, c, X[i + 2], 9, 0xfcefa3f8);
// 		c = R2(c, d, a, b, X[i + 7], 14, 0x676f02d9);
// 		b = R2(b, c, d, a, X[i + 12], 20, 0x8d2a4c8a);
// 
// 		a = R3(a, b, c, d, X[i + 5], 4, 0xfffa3942);
// 		d = R3(d, a, b, c, X[i + 8], 11, 0x8771f681);
// 		c = R3(c, d, a, b, X[i + 11], 16, 0x6d9d6122);
// 		b = R3(b, c, d, a, X[i + 14], 23, 0xfde5380c);
// 		a = R3(a, b, c, d, X[i + 1], 4, 0xa4beea44);
// 		d = R3(d, a, b, c, X[i + 4], 11, 0x4bdecfa9);
// 		c = R3(c, d, a, b, X[i + 7], 16, 0xf6bb4b60);
// 		b = R3(b, c, d, a, X[i + 10], 23, 0xbebfbc70);
// 		a = R3(a, b, c, d, X[i + 13], 4, 0x289b7ec6);
// 		d = R3(d, a, b, c, X[i + 0], 11, 0xeaa127fa);
// 		c = R3(c, d, a, b, X[i + 3], 16, 0xd4ef3085);
// 		b = R3(b, c, d, a, X[i + 6], 23, 0x4881d05);
// 		a = R3(a, b, c, d, X[i + 9], 4, 0xd9d4d039);
// 		d = R3(d, a, b, c, X[i + 12], 11, 0xe6db99e5);
// 		c = R3(c, d, a, b, X[i + 15], 16, 0x1fa27cf8);
// 		b = R3(b, c, d, a, X[i + 2], 23, 0xc4ac5665);
// 
// 		a = R4(a, b, c, d, X[i + 0], 6, 0xf4292244);
// 		d = R4(d, a, b, c, X[i + 7], 10, 0x432aff97);
// 		c = R4(c, d, a, b, X[i + 14], 15, 0xab9423a7);
// 		b = R4(b, c, d, a, X[i + 5], 21, 0xfc93a039);
// 		a = R4(a, b, c, d, X[i + 12], 6, 0x655b59c3);
// 		d = R4(d, a, b, c, X[i + 3], 10, 0x8f0ccc92);
// 		c = R4(c, d, a, b, X[i + 10], 15, 0xffeff47d);
// 		b = R4(b, c, d, a, X[i + 1], 21, 0x85845dd1);
// 		a = R4(a, b, c, d, X[i + 8], 6, 0x6fa87e4f);
// 		d = R4(d, a, b, c, X[i + 15], 10, 0xfe2ce6e0);
// 		c = R4(c, d, a, b, X[i + 6], 15, 0xa3014314);
// 		b = R4(b, c, d, a, X[i + 13], 21, 0x4e0811a1);
// 		a = R4(a, b, c, d, X[i + 4], 6, 0xf7537e82);
// 		d = R4(d, a, b, c, X[i + 11], 10, 0xbd3af235);
// 		c = R4(c, d, a, b, X[i + 2], 15, 0x2ad7d2bb);
// 		b = R4(b, c, d, a, X[i + 9], 21, 0xeb86d391);
// 
// 		a += a0;
// 		b += b0;
// 		c += c0;
// 		d += d0;
// 	}
// 
// 
// 	int pos = 0;
// 	hex(a, dst, pos);
// 	hex(b, dst, pos);
// 	hex(c, dst, pos);
// 	hex(d, dst, pos);
// 	dst[32] = 0;
// 	free(X);
// }

void CresendSocketDlg::OnPaint()
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


#include<string.h>
#include <stdio.h>   
#include <stdlib.h>   
#include <memory.h>   
#include <math.h>   

typedef unsigned char BYTE;
typedef unsigned int  UINT;
typedef UINT MD5_SUB_ARRAY[16];
typedef UINT MD5_TRANSORM_FUNC(UINT, UINT, UINT);
typedef struct
{
	UINT    a;
	UINT    b;
	UINT    c;
	UINT    d;
	MD5_SUB_ARRAY   sub_array;
}MD5_TRANSFORM_PARAM;

const double    MAX_INT = (double)0xFFFFFFFF + 1.0;

const UINT MD5_TRANSFORM_MATRIX[4][16][3] =
{
	{
		{ 0, 7, 1 },{ 1,12, 2 },{ 2,17, 3 },{ 3,22, 4 },
		{ 4, 7, 5 },{ 5,12, 6 },{ 6,17, 7 },{ 7,22, 8 },
		{ 8, 7, 9 },{ 9,12,10 },{ 10,17,11 },{ 11,22,12 },
		{ 12, 7,13 },{ 13,12,14 },{ 14,17,15 },{ 15,22,16 },
	},
	{
		{ 1, 5,17 },{ 6, 9,18 },{ 11,14,19 },{ 0,20,20 },
		{ 5, 5,21 },{ 10, 9,22 },{ 15,14,23 },{ 4,20,24 },
		{ 9, 5,25 },{ 14, 9,26 },{ 3,14,27 },{ 8,20,28 },
		{ 13, 5,29 },{ 2, 9,30 },{ 7,14,31 },{ 12,20,32 },
	},
	{
		{ 5, 4, 33 },{ 8,11,34 },{ 11,16,35 },{ 14, 23,36 },
		{ 1, 4, 37 },{ 4,11,38 },{ 7,16,39 },{ 10, 23,40 },
		{ 13,4, 41 },{ 0,11,42 },{ 3,16,43 },{ 6, 23,44 },
		{ 9, 4, 45 },{ 12,11,46 },{ 15,16,47 },{ 2, 23,48 },
	},
	{
		{ 0,6,49 },{ 7,10,50 },{ 14,15,51 },{ 5, 21,52 },
		{ 12,6,53 },{ 3,10,54 },{ 10,15,55 },{ 1, 21,56 },
		{ 8,6,57 },{ 15,10,58 },{ 6,15,59 },{ 13, 21,60 },
		{ 4,6,61 },{ 11,10,62 },{ 2,15,63 },{ 9, 21,64 },
	},
};

static UINT MD5_TRANSFORM_ARRAY[65];

void MD5_Init()
{
	int x;
	for (x = 1; x <= 64; x++)
	{
		MD5_TRANSFORM_ARRAY[x] = (UINT)(MAX_INT * fabs(sin(x)));
	}
}

UINT F(UINT x, UINT y, UINT z)
{
	return ((x & y) | ((~x) & z));
}

UINT G(UINT x, UINT y, UINT z)
{
	return ((x & z) | (y & (~z)));
}

UINT H(UINT x, UINT y, UINT z)
{
	return (x ^ y ^ z);
}

UINT I(UINT x, UINT y, UINT z)
{
	return (y ^ (x | (~z)));
}

BYTE* MD5_prepare_data(const BYTE* data, int len, int* new_len)
{
	int rest, fill, size;
	BYTE* new_data;
	UINT  bit_len;

	// (1) 字节补齐   
	rest = len % 56;
	if (rest <= 56) fill = 56 - rest;
	else fill = (64 - rest) + 56;

	new_data = (BYTE*)malloc(len + fill + 8);
	if (NULL == new_data) return NULL;

	if (len > 0)    memcpy(new_data, data, len);
	if (fill > 0)   memset(new_data + len, 0x80, 1);
	if (fill > 1)   memset(new_data + len + 1, 0, fill - 1);

	size = fill + len;

	// (2) 附加数据的比特长度   
	bit_len = len * 8;
	// (64位二进制数表示的)比特长度的低32位   
	memset(new_data + size + 0, (bit_len & 0x000000FF), 1);
	memset(new_data + size + 1, (bit_len & 0x0000FF00) >> 8, 1);
	memset(new_data + size + 2, (bit_len & 0x00FF0000) >> 16, 1);
	memset(new_data + size + 3, (bit_len & 0xFF000000) >> 24, 1);
	// 不考虑比特长度超出32位无符号数表示范围,所以高32位总是0   
	memset(new_data + size + 4, 0, 4);

	*new_len = size + 8;

	return new_data;
}

void MD5_transform(MD5_TRANSFORM_PARAM* param, int ring, MD5_TRANSORM_FUNC func)
{
	UINT a, b, c, d, s, k, i;
	UINT abcd[4];
	UINT *X, *T;
	int index;

	abcd[0] = param->a;
	abcd[1] = param->b;
	abcd[2] = param->c;
	abcd[3] = param->d;
	X = param->sub_array;
	T = MD5_TRANSFORM_ARRAY;

	for (index = 0; index < 16; index++)
	{
		a = abcd[(3 * index + 0) % 4];
		b = abcd[(3 * index + 1) % 4];
		c = abcd[(3 * index + 2) % 4];
		d = abcd[(3 * index + 3) % 4];

		k = MD5_TRANSFORM_MATRIX[ring][index][0];
		s = MD5_TRANSFORM_MATRIX[ring][index][1];
		i = MD5_TRANSFORM_MATRIX[ring][index][2];

		a = a + func(b, c, d) + X[k] + T[i];
		a = (a << s) | (a >> (32 - s)); // 循环左移   
		a = a + b;

		abcd[(3 * index + 0) % 4] = a;
	}

	param->a = abcd[0];
	param->b = abcd[1];
	param->c = abcd[2];
	param->d = abcd[3];
}

int MD5(const BYTE* data, int len, char*dst)
{
	int  x, y, new_len;
	MD5_TRANSFORM_PARAM param;
	UINT AA, BB, CC, DD;
	BYTE* buf;

	MD5_Init();

	buf = MD5_prepare_data(data, len, &new_len);
	if (buf == NULL) return -1;

	AA = 0x67452301;
	BB = 0xefcdab89;
	CC = 0x98badcfe;
	DD = 0x10325476;

	for (x = 0; x < new_len / 64; x++)
	{
		param.a = AA;
		param.b = BB;
		param.c = CC;
		param.d = DD;

		for (y = 0; y < 16; y++)
		{
			param.sub_array[y] = buf[64 * x + 4 * y + 0];
			param.sub_array[y] += buf[64 * x + 4 * y + 1] << 8;
			param.sub_array[y] += buf[64 * x + 4 * y + 2] << 16;
			param.sub_array[y] += buf[64 * x + 4 * y + 3] << 24;
		}
		MD5_transform(&param, 0, F);
		MD5_transform(&param, 1, G);
		MD5_transform(&param, 2, H);
		MD5_transform(&param, 3, I);

		AA += param.a;
		BB += param.b;
		CC += param.c;
		DD += param.d;
	}

	printf("MD5(\"%s\")=", data);

	sprintf(dst, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
		(AA & 0x000000FF),
		(AA & 0x0000FF00) >> 8,
		(AA & 0x00FF0000) >> 16,
		(AA & 0xFF000000) >> 24,
		(BB & 0x000000FF),
		(BB & 0x0000FF00) >> 8,
		(BB & 0x00FF0000) >> 16,
		(BB & 0xFF000000) >> 24,
		(CC & 0x000000FF),
		(CC & 0x0000FF00) >> 8,
		(CC & 0x00FF0000) >> 16,
		(CC & 0xFF000000) >> 24,
		(DD & 0x000000FF),
		(DD & 0x0000FF00) >> 8,
		(DD & 0x00FF0000) >> 16,
		(DD & 0xFF000000) >> 24);

	free(buf);
	buf = NULL;
	return 0;
}


//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CresendSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CresendSocketDlg::OnBnClickedButton1()
{
	m_run = FALSE;
	TerminateThread(m_thread, 0);
	SendMessage(WM_CLOSE, 0, 0);
}


void CresendSocketDlg::OnBnClickedButton2()
{
 	m_run = TRUE;
 	if (INVALID_HANDLE_VALUE == m_thread)
 	{
 		CWinThread *tthread = AfxBeginThread(CresendSocketDlg::ResendThread, this);
 		m_thread = tthread->m_hThread;
 	}
 	else
 	{
 		m_run = FALSE;
 	}
}

UINT CresendSocketDlg::ResendThread(LPVOID lParam)
{
	CresendSocketDlg *pMain = (CresendSocketDlg*)lParam;
	//int port = pMain->GetDlgItemInt(IDC_PORT);
	//CString info;
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
// 		info.Format(_T("WSAStartup failed,error:%d", GetLastError()));
// 		pMain->ShowInfo(info);
		return 0;
	}
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
// 		info.Format(_T("WSAStartup version not ok,error:%d", GetLastError()));
// 		pMain->ShowInfo(info);
		return 0;
	}

	//port = 7201;
	SOCKET recvSock = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN recvAddr;
	recvAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	recvAddr.sin_family = AF_INET;
	recvAddr.sin_port = htons(7201);
	BOOL bBroadcast = TRUE;
	setsockopt(recvSock, SOL_SOCKET, SO_BROADCAST, (const char*)&bBroadcast, sizeof(BOOL));
	if (SOCKET_ERROR == bind(recvSock, (SOCKADDR*)&recvAddr, sizeof(SOCKADDR)))
	{
// 		info.Format(_T("bind recvSock IP:%s port:%d failed ,error:%d"), inet_ntoa(recvAddr.sin_addr), port, WSAGetLastError());
// 		pMain->ShowInfo(info);
		return 0;
	}
// 	info.Format(_T("bind recvSock IP:%s port:%d success.\r\n"), inet_ntoa(recvAddr.sin_addr), port);
// 	pMain->ShowInfo(info);
// 
//  	SOCKET sendSock = socket(AF_INET, SOCK_DGRAM, 0);
//  	SOCKADDR_IN sendAddr;
//  	sendAddr.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");
//  	sendAddr.sin_family = AF_INET;
//  	sendAddr.sin_port = htons(7301);
//  	if (SOCKET_ERROR == bind(sendSock, (SOCKADDR*)&sendAddr, sizeof(SOCKADDR)))
//  	{
//  		info.Format(_T("bind sendSock IP:%s port:%d failed ,error:%d"), inet_ntoa(sendAddr.sin_addr), 7301, WSAGetLastError());
//  		pMain->ShowInfo(info);
//  		return 0;
//  	}
//  	info.Format(_T("bind sendSock IP:%s port:%d success.\r\n"), inet_ntoa(sendAddr.sin_addr), 7301);
//  	pMain->ShowInfo(info);

	SOCKADDR_IN dstAddr;
	dstAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	dstAddr.sin_family = AF_INET;
	dstAddr.sin_port = htons(7401);
// 	CString temp;
// 	temp.Format(_T("dstAddr IP:%s port:%d.\r\n"), inet_ntoa(dstAddr.sin_addr), 7401);
// 	info += temp;
// 	pMain->ShowInfo(info);

	int addrLen = sizeof(SOCKADDR);
	//char recvBuf[2048] = { 0 };
	SOCKADDR_IN recvFromAddr;
	recvFromAddr.sin_family = AF_INET;
	recvFromAddr.sin_addr.S_un.S_addr = INADDR_BROADCAST;
	recvFromAddr.sin_port = htons(7201);

	//std::vector<PPACK> *packBuf = new std::vector<PPACK>();
	SOCKADDR_IN sendAddr;
 	sendAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
 	sendAddr.sin_family = AF_INET;
 	sendAddr.sin_port = htons(7401);
	static int packDataLen = 1316;
	int packLen = sizeof(PACK);
	PACK pack;
	int nSendBuf = 1024 * 1024;
	CString s;
	int ret = setsockopt(recvSock, SOL_SOCKET, SO_RCVBUF, (const char*)&nSendBuf, sizeof(int));
	s.Format("func: setsockopt:%d", ret);
	OutputDebugStringA(s);
	ret = setsockopt(recvSock, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));
	s.Format("func: setsockopt:%d", ret);
	OutputDebugStringA(s);
	int lastPackNum = 0;
	while (pMain->m_run)
	{
		//char *recvBuf = new char[packLen];
		//int recvLen=recvfrom(recvSock, recvBuf, packLen, 0, (SOCKADDR*)&recvFromAddr, &addrLen);
	//	OutputDebugStringA("1\r\n");
		int recvLen = recvfrom(recvSock, (char*)&pack, packLen, 0, (SOCKADDR*)&recvFromAddr, &addrLen);
// 		temp.Format(_T("recv from:%s datalen:%d\r\n"), inet_ntoa(recvFromAddr.sin_addr), recvLen);
// 		info += temp;
// 		pMain->ShowInfo(info);
	//	OutputDebugStringA("2\r\n");

		if ((recvLen == packLen) && (0x55AA55AA == pack.thedataflag))
		{
			BYTE checksum = 0;
			int len = (BYTE*)&pack.checksum - (BYTE*)&pack;
			for (int i = 0;i < len;++i)
				checksum ^= ((BYTE*)&pack)[i];
			if ((checksum == pack.checksum))
			{
				if (pack.MD5[32] != 0)
				{
					OutputDebugStringA("func: pack.MD5[32] != 0");
				}
				else
				{
					char MD5_calc[33] = { 0 };
					MD5((BYTE*)pack.data, packDataLen, MD5_calc);
					if (0 != CString(MD5_calc).CompareNoCase(pack.MD5))
					{
						CString s;
						s.Format("func: MD5 not OK MD5_calc:%s pack.MD5:%s pack:%d", MD5_calc,pack.MD5,pack.packNum);
						OutputDebugStringA(s);
					}
					else
					{
						OutputDebugStringA(CString("func: MD5 OK") + MD5_calc);
					}
				}
				if (pack.packNum - lastPackNum != 1)
				{
					CString s;
					s.Format("func: packNum not OK lastPackNum:%d pack.packNum:%d",lastPackNum, pack.packNum);
					OutputDebugStringA(s);
				}
				if (/*(recvLen>0) && */(SOCKET_ERROR == sendto(recvSock, (char*)pack.data, packDataLen, 0, (SOCKADDR*)&sendAddr, sizeof(sendAddr))))
				{
					CString s;
					s.Format("func: send error:%d packNum:%d", WSAGetLastError(),pack.packNum);
					OutputDebugStringA(s);
				}
				lastPackNum = pack.packNum;
			}
			else
			{
				CString s;
				s.Format("func: checksum:%d pack.checksum:%d pack.packNum：%d", checksum, pack.checksum, pack.packNum);
				OutputDebugStringA(s);
			}
		}
		else
		{
			CString s;
			s.Format("func: recvLen:%d  packLen:%d,pack.thedataflag:%d pack.packNum:%d", recvLen, packLen, pack.thedataflag, pack.packNum);
			OutputDebugStringA(s);
		}

// 		if (/*(recvLen>0) && */(SOCKET_ERROR == sendto(recvSock, recvBuf, recvLen, 0, (SOCKADDR*)&sendAddr, sizeof(sendAddr))))
// 		{
////  			temp.Format(_T("send to:%s port:%d failed, error:%d\r\n"), inet_ntoa(sendAddr.sin_addr), sendAddr.sin_port, WSAGetLastError());
////  			info += temp;
////  			pMain->ShowInfo(info);
// 		}
//  		temp.Format(_T("send to:%s port:%d\r\n"), inet_ntoa(sendAddr.sin_addr), sendAddr.sin_port);
// 		info += temp;
// 		pMain->ShowInfo(info);
	}
	closesocket(recvSock);
	WSACleanup();
	pMain->m_thread = INVALID_HANDLE_VALUE;
	return 0;
}


void CresendSocketDlg::ShowInfo(CString&info)
{
	if (info.GetLength() > 2000)
		info = info.Right(1500);
	SetDlgItemText(IDC_EDIT1, info);
}

afx_msg LRESULT CresendSocketDlg::OnSendmsg(WPARAM wParam, LPARAM lParam)
{
// 	CString info;
// 	GetDlgItemText(IDC_EDIT1, info);
// 	SOCKET sendSock = socket(AF_INET, SOCK_DGRAM, 0);
// 	SOCKADDR_IN sendAddr;
// 	sendAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.253");
// 	sendAddr.sin_family = AF_INET;
// 	sendAddr.sin_port = htons(7301);
// 	if (SOCKET_ERROR == bind(sendSock, (SOCKADDR*)&sendAddr, sizeof(SOCKADDR)))
// 	{
// 		info.Format(_T("bind sendSock IP:%s port:%d failed ,error:%d"), inet_ntoa(sendAddr.sin_addr), 7301, WSAGetLastError());
// 		pMain->ShowInfo(info);
// 		return 0;
// 	}
// 	info.Format(_T("bind sendSock IP:%s port:%d success.\r\n"), inet_ntoa(sendAddr.sin_addr), 7301);
// 	pMain->ShowInfo(info);
// 	sendAddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.253");
// 	sendAddr.sin_family = AF_INET;
// 	sendAddr.sin_port = htons(7401);
// 	if (/*(recvLen>0) && */(SOCKET_ERROR == sendto(recvSock, recvBuf, recvLen, 0, (SOCKADDR*)&sendAddr, sizeof(sendAddr))))
// 	{
// 		temp.Format(_T("send to:%s port:%d failed, error:%d\r\n"), inet_ntoa(sendAddr.sin_addr), sendAddr.sin_port, WSAGetLastError());
// 		info += temp;
// 		pMain->ShowInfo(info);
// 	}
// 	temp.Format(_T("send to:%s port:%d\r\n"), inet_ntoa(sendAddr.sin_addr), sendAddr.sin_port);
// 	info += temp;
// 	pMain->ShowInfo(info);
	return 0;
}


void CresendSocketDlg::OnBnClickedButton3()
{
	CString s;
	GetDlgItemText(IDC_EDIT1, s);
	s.ReleaseBuffer();
	char *src = new char[s.GetLength() + 1];
	strcpy(src, s);
	int srcLen = s.GetLength();
	char dst[33] = { 0 };
	MD5((BYTE*)src, srcLen, dst);
	SetDlgItemText(IDC_EDIT1, dst);
}
