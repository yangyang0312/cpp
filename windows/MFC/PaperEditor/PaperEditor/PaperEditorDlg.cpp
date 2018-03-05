// PaperEditorDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "PaperEditor.h"
#include "PaperEditorDlg.h"
#include "afxdialogex.h"
#include "ViewDialog.h"
#include "../GenerateHtm/GenerateHtm.h"
#include "../LoadSavePaper/LoadSavePaper.h"
#include "SetScoreDlg.h"

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

// CPaperEditorDlg 对话框
CPaperEditorDlg::CPaperEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAPEREDITOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPaperEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_TOPICTITLE,m_editTopicTitle);
	DDX_Control(pDX,IDC_TOPICFILE,m_listTopicFile);
	DDX_Control(pDX,IDC_CHECKA,m_checkA);
	DDX_Control(pDX,IDC_CHECKB,m_checkB);
	DDX_Control(pDX,IDC_CHECKC,m_checkC);
	DDX_Control(pDX,IDC_CHECKD,m_checkD);
	DDX_Control(pDX,IDC_CHECKE,m_checkE);
	DDX_Control(pDX,IDC_ANSA,m_editA);
	DDX_Control(pDX,IDC_ANSB,m_editB);
	DDX_Control(pDX,IDC_ANSC,m_editC);
	DDX_Control(pDX,IDC_ANSD,m_editD);
	DDX_Control(pDX,IDC_ANSE,m_editE);
	DDX_Control(pDX,IDC_ANS,m_editAnswer);
	DDX_Control(pDX,IDC_COMBOSELECT,m_comboSelect);
	DDX_Control(pDX,IDC_PAPERNAME,m_editPaperTitle);
	DDX_Control(pDX,IDC_GROUPEDITPAPER,m_groupPaper);
	DDX_Control(pDX,IDC_GROUPCONTENT,m_groupContent);
	DDX_Control(pDX,IDC_GROUPTYPE,m_groupType);
	DDX_Control(pDX,IDC_PAPERFILE,m_listPaperFile);
}

BEGIN_MESSAGE_MAP(CPaperEditorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_RADIOSELECT,&CPaperEditorDlg::OnBnClickedRadioselect)
	ON_BN_CLICKED(IDC_RADIOBLANK,&CPaperEditorDlg::OnBnClickedRadioblank)
	ON_BN_CLICKED(IDC_RADIOQA,&CPaperEditorDlg::OnBnClickedRadioqa)
	ON_CBN_SELCHANGE(IDC_COMBOSELECT,&CPaperEditorDlg::OnCbnSelchangeComboselect)
	ON_WM_SIZE()
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,SetToolTipText)
	ON_BN_CLICKED(IDC_NEW, &CPaperEditorDlg::OnBnClickedNew)
	ON_BN_CLICKED(IDC_OPEN, &CPaperEditorDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_SAVE, &CPaperEditorDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_SAVEAS, &CPaperEditorDlg::OnBnClickedSaveas)
	ON_BN_CLICKED(IDC_SCORE, &CPaperEditorDlg::OnBnClickedScore)
	ON_BN_CLICKED(IDC_ADDFILE, &CPaperEditorDlg::OnBnClickedAddfile)
	ON_BN_CLICKED(IDC_PREVIEW, &CPaperEditorDlg::OnBnClickedPreview)
	ON_BN_CLICKED(IDC_PRINT, &CPaperEditorDlg::OnBnClickedPrint)
	ON_BN_CLICKED(IDC_NEWTOPIC, &CPaperEditorDlg::OnBnClickedNewtopic)
	ON_BN_CLICKED(IDC_INSERTTOPIC, &CPaperEditorDlg::OnBnClickedInserttopic)
	ON_BN_CLICKED(IDC_LAST10TOPIC, &CPaperEditorDlg::OnBnClickedLast10topic)
	ON_BN_CLICKED(IDC_LASTTOPIC, &CPaperEditorDlg::OnBnClickedLasttopic)
	ON_BN_CLICKED(IDC_NEXTTOPIC, &CPaperEditorDlg::OnBnClickedNexttopic)
	ON_BN_CLICKED(IDC_NEXT10Topic, &CPaperEditorDlg::OnBnClickedNext10topic)
	ON_BN_CLICKED(IDC_DELETE, &CPaperEditorDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_ADDFILETOTOPIC, &CPaperEditorDlg::OnBnClickedAddfiletotopic)
	ON_BN_CLICKED(IDC_SEPRATOR, &CPaperEditorDlg::OnBnClickedSeprator)
END_MESSAGE_MAP()

// CPaperEditorDlg 消息处理程序
BOOL CPaperEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	//设置窗口标题
	m_strWindowTitle = _T("试卷编辑器 -UnTitle");
	SetWindowText(m_strWindowTitle);
	//默认选中四选题
	((CButton *)GetDlgItem(IDC_RADIOSELECT))->SetCheck(TRUE);
	((CComboBox *)GetDlgItem(IDC_COMBOSELECT))->SetCurSel(2);
	m_topicType = eTopicTypeSelect;
	m_listTopicFile.ShowWindow(SW_HIDE);
	EnableToolTips(TRUE);
	m_paper.m_vecTopic.push_back(stuTopic());		//首先插入一个题目
	m_viewPos = 0;
	m_tempPaper = m_paper;							//保存试卷的初始信息
	ShowEditScrollBar();
	BeautifyButtons();
	m_btnSeprator.ShowWindow(SW_HIDE);				//隐藏按钮
	m_btnFile.ShowWindow(SW_HIDE);			
	m_btnTopicFile.ShowWindow(SW_HIDE);
	TCHAR buf[MAX_PATH] = {0};						//获取程序所在路径
	GetCurrentDirectory(MAX_PATH,buf);
	m_currentPath = CString(buf) + "\\";
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
//显示edit的滚动条
void CPaperEditorDlg::ShowEditScrollBar()
{
	m_editTopicTitle.ShowScrollBar(SB_VERT, TRUE);	//显示滚动条
	m_editAnswer.ShowScrollBar(SB_VERT, TRUE);
	m_editA.ShowScrollBar(SB_VERT, TRUE);
	m_editB.ShowScrollBar(SB_VERT, TRUE);
	m_editC.ShowScrollBar(SB_VERT, TRUE);
	m_editD.ShowScrollBar(SB_VERT, TRUE);
	m_editE.ShowScrollBar(SB_VERT, TRUE);
}
//按钮贴图
void CPaperEditorDlg::BeautifyButtons()
{
	m_btnNew.SubclassDlgItem(IDC_NEW, this);
	m_btnOpen.SubclassDlgItem(IDC_OPEN, this);
	m_btnSave.SubclassDlgItem(IDC_SAVE, this);
	m_btnSaveAs.SubclassDlgItem(IDC_SAVEAS, this);
	m_btnScore.SubclassDlgItem(IDC_SCORE, this);
	m_btnFile.SubclassDlgItem(IDC_ADDFILE, this);
	m_btnPreview.SubclassDlgItem(IDC_PREVIEW, this);
	m_btnPrint.SubclassDlgItem(IDC_PRINT, this);
	m_btnNewtopic.SubclassDlgItem(IDC_NEWTOPIC, this);
	m_btnInsert.SubclassDlgItem(IDC_INSERTTOPIC, this);
	m_btnLast10.SubclassDlgItem(IDC_LAST10TOPIC, this);
	m_btnLast.SubclassDlgItem(IDC_LASTTOPIC, this);
	m_btnNext.SubclassDlgItem(IDC_NEXTTOPIC, this);
	m_btnNext10.SubclassDlgItem(IDC_NEXT10Topic, this);
	m_btnDelete.SubclassDlgItem(IDC_DELETE, this);
	m_btnTopicFile.SubclassDlgItem(IDC_ADDFILETOTOPIC, this);
	m_btnSeprator.SubclassDlgItem(IDC_SEPRATOR, this);
	m_btnNew.LoadBitmaps(IDB_NEW, IDB_NEW2);
	m_btnOpen.LoadBitmaps(IDB_OPEN, IDB_OPEN2);
	m_btnSave.LoadBitmaps(IDB_SAVE, IDB_SAVE2);
	m_btnSaveAs.LoadBitmaps(IDB_SAVEAS, IDB_SAVEAS2);
	m_btnScore.LoadBitmaps(IDB_SCORE, IDB_SCORE2);
	m_btnFile.LoadBitmaps(IDB_FILE, IDB_FILE2);
	m_btnPreview.LoadBitmaps(IDB_PREVIEW, IDB_PREVIEW2);
	m_btnPrint.LoadBitmaps(IDB_PRINT, IDB_PRINT2);
	m_btnNewtopic.LoadBitmaps(IDB_NEWTOPIC, IDB_NEWTOPIC2);
	m_btnInsert.LoadBitmaps(IDB_INSERT, IDB_INSERT2);
	m_btnLast10.LoadBitmaps(IDB_LAST10, IDB_LAST102);
	m_btnLast.LoadBitmaps(IDB_LAST, IDB_LAST2);
	m_btnNext.LoadBitmaps(IDB_NEXT, IDB_NEXT2);
	m_btnNext10.LoadBitmaps(IDB_NEXT10, IDB_NEXT102);
	m_btnDelete.LoadBitmaps(IDB_DELETE, IDB_DELETE2);
	m_btnTopicFile.LoadBitmaps(IDB_FILETOPIC, IDB_FILETOPIC2);
	m_btnSeprator.LoadBitmaps(IDB_SEPRATOR, IDB_SEPRATOR2);
}
//屏蔽enter退出
void CPaperEditorDlg::OnOK()
{
}
//屏蔽esc退出
BOOL CPaperEditorDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
void CPaperEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CPaperEditorDlg::OnPaint()
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
HCURSOR CPaperEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//限制窗口最小大小
void CPaperEditorDlg::OnGetMinMaxInfo(MINMAXINFO * lpMMI)
{
	lpMMI->ptMinTrackSize.x = 1017;
	lpMMI->ptMinTrackSize.y = 711;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}
//选择题
void CPaperEditorDlg::OnBnClickedRadioselect()		//如果当前不是选择题、隐藏所有控件再显示
{
	if (m_topicType == eTopicTypeSelect)
		return;
	m_topicType = eTopicTypeSelect;
	m_comboSelect.EnableWindow(TRUE);
	HideAllTopicControl();
	ShowTopicControl(m_topicType);
}
//填空题
void CPaperEditorDlg::OnBnClickedRadioblank()		//如果当前不是填空题、隐藏所有控件再显示
{
	if (m_topicType == eTopicTypeBlank)
		return;
	m_topicType = eTopicTypeBlank;
	m_comboSelect.EnableWindow(FALSE);
	HideAllTopicControl();
	ShowTopicControl(m_topicType);
}
//问答题
void CPaperEditorDlg::OnBnClickedRadioqa()			//如果当前不是问答题、隐藏所有控件再显示
{
	if (m_topicType == eTopicTypeQA)
		return;
	m_topicType = eTopicTypeQA;
	m_comboSelect.EnableWindow(FALSE);
	HideAllTopicControl();
	ShowTopicControl(m_topicType);
}
//选择题数量改变
void CPaperEditorDlg::OnCbnSelchangeComboselect()	//调整要显示的答案个数
{
	ShowTopicControl(eTopicTypeSelect);
}
//隐藏所有控件
void CPaperEditorDlg::HideAllTopicControl()	//隐藏题目那儿的所有控件
{
	m_editTopicTitle.ShowWindow(SW_HIDE);
	m_listTopicFile.ShowWindow(SW_HIDE);
	m_checkA.ShowWindow(SW_HIDE);
	m_checkB.ShowWindow(SW_HIDE);
	m_checkC.ShowWindow(SW_HIDE);
	m_checkD.ShowWindow(SW_HIDE);
	m_checkE.ShowWindow(SW_HIDE);
	m_editA.ShowWindow(SW_HIDE);
	m_editB.ShowWindow(SW_HIDE);
	m_editC.ShowWindow(SW_HIDE);
	m_editD.ShowWindow(SW_HIDE);
	m_editE.ShowWindow(SW_HIDE);
	m_editAnswer.ShowWindow(SW_HIDE);
	m_btnSeprator.ShowWindow(SW_HIDE);
}
//显示指定类型的控件并调整控件大小
void CPaperEditorDlg::ShowTopicControl(const eTopicType & type)
{
	m_editTopicTitle.ShowWindow(SW_SHOW);
	CRect rect;
	GetWindowRect(&rect);
	CPoint point;
	point.x = 203;
	point.y = 191;
	int width = rect.Width() - 232;
	m_editTopicTitle.SetWindowPos(this,point.x,point.y,width,185,SWP_NOZORDER);//题目位置
	switch(type)
	{
	case eTopicTypeSelect:
	{
		int height = (int)((rect.Height() - point.y - 185 - 65)/5.0);
		point.x += 51;
		point.y += 188;
		//修改选项位置，并显示和隐藏选项
		m_editA.SetWindowPos(this, point.x, point.y, width - 51, height, SWP_NOZORDER);
		m_checkA.SetWindowPos(this, point.x - 35, point.y + 16, 0,0, SWP_NOZORDER | SWP_NOSIZE);
		point.y = point.y + height + 3;
		m_editB.SetWindowPos(this, point.x, point.y, width - 51, height, SWP_NOZORDER);
		m_checkB.SetWindowPos(this, point.x - 35, point.y + 16, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		point.y = point.y + height + 3;
		m_editC.SetWindowPos(this, point.x, point.y, width - 51, height, SWP_NOZORDER);
		m_checkC.SetWindowPos(this, point.x - 35, point.y + 16, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		point.y = point.y + height + 3;
		m_editD.SetWindowPos(this, point.x, point.y, width - 51, height, SWP_NOZORDER);
		m_checkD.SetWindowPos(this, point.x - 35, point.y + 16, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		point.y = point.y + height + 3;
		m_editE.SetWindowPos(this, point.x, point.y, width - 51, height, SWP_NOZORDER);
		m_checkE.SetWindowPos(this, point.x - 35, point.y + 16, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		int curSel = m_comboSelect.GetCurSel();
		m_checkA.ShowWindow(SW_SHOW);
		m_editA.ShowWindow(SW_SHOW);
		m_checkB.ShowWindow(SW_SHOW);
		m_editB.ShowWindow(SW_SHOW);
		m_checkC.ShowWindow(curSel > 0 ? SW_SHOW : SW_HIDE);
		m_editC.ShowWindow(curSel > 0 ? SW_SHOW : SW_HIDE);
		m_checkD.ShowWindow(curSel > 1 ? SW_SHOW : SW_HIDE);
		m_editD.ShowWindow(curSel > 1 ? SW_SHOW : SW_HIDE);
		m_checkE.ShowWindow(curSel > 2 ? SW_SHOW : SW_HIDE);
		m_editE.ShowWindow(curSel > 2 ? SW_SHOW : SW_HIDE);
		break;
	}
	case eTopicTypeBlank:
	{
		m_editAnswer.SetWindowPos(this, 0, 0, width, 60, SWP_NOZORDER | SWP_NOMOVE);
		m_btnSeprator.SetWindowPos(this, rect.Width() - 133, 454,0,0, SWP_NOZORDER | SWP_NOSIZE);
		m_editAnswer.ShowWindow(SW_SHOW);
		m_btnSeprator.ShowWindow(SW_SHOW);
		break;
	}
	case eTopicTypeQA:
	{
		m_editAnswer.SetWindowPos(this, 0,0,width,180, SWP_NOZORDER | SWP_NOMOVE);
		m_editAnswer.ShowWindow(SW_SHOW);
		break;
	}
	default:
		break;
	}
}
//大小改变调整控件
void CPaperEditorDlg::OnSize(UINT nType,int cx,int cy)
{
	CDialogEx::OnSize(nType,cx,cy);
	if(nType == SIZE_MINIMIZED)//最小化
		return;
	if(m_groupContent.m_hWnd != NULL)			  //修改组框位置
	{	
		m_groupPaper.SetWindowPos(this,4,88,cx - 8,cy - 91,SWP_NOZORDER);
		m_groupType.SetWindowPos(this,9,179,187,cy - 187,SWP_NOZORDER);
		m_groupContent.SetWindowPos(this,198,179,cx - 206,cy - 187,SWP_NOZORDER);
		ShowTopicControl(m_topicType);
	}
}
//tooltip设置
BOOL CPaperEditorDlg::SetToolTipText(UINT id, NMHDR *pTTTStruct, LRESULT *pResult)
{
	TOOLTIPTEXT * pTTT = (TOOLTIPTEXT *)pTTTStruct;
	UINT nID = pTTTStruct->idFrom;				  //得到相应窗口ID，有可能是HWND   
	nID = ::GetDlgCtrlID((HWND)nID);			  //从HWND得到ID值
	if (nID && (pTTT->uFlags & TTF_IDISHWND))     //表明nID是否为HWND
	{
		switch (nID)							  //根据ID复制tooltip字符串
		{
		case IDC_NEW:
			strcpy_s(pTTT->lpszText, 80, _T("新建试卷"));
			break;
		case IDC_OPEN:
			strcpy_s(pTTT->lpszText, 80, _T("打开已保存的试卷"));
			break;
		case IDC_SAVE:
			strcpy_s(pTTT->lpszText, 80, _T("保存当前试卷"));
			break;
		case IDC_SAVEAS:
			strcpy_s(pTTT->lpszText, 80, _T("将当前试卷另存"));
			break;
		case IDC_SCORE:
			strcpy_s(pTTT->lpszText, 80, _T("配置试卷分数"));
			break;
		case IDC_ADDFILE:
			strcpy_s(pTTT->lpszText, 80, _T("附件文件到试卷"));
			break;
		case IDC_PREVIEW:
			strcpy_s(pTTT->lpszText, 80, _T("预览试卷"));
			break;
		case IDC_PRINT:
			strcpy_s(pTTT->lpszText, 80, _T("打印试卷"));
			break;
		case IDC_NEWTOPIC:
			strcpy_s(pTTT->lpszText, 80, _T("在题目末尾新增题目"));
			break;
		case IDC_INSERTTOPIC:
			strcpy_s(pTTT->lpszText, 80, _T("在当前题目前插入新题目"));
			break;
		case IDC_DELETE:
			strcpy_s(pTTT->lpszText, 80, _T("删除当前题目"));
			break;
		case IDC_ADDFILETOTOPIC:
			strcpy_s(pTTT->lpszText, 80, _T("附加文件到当前题目"));
			break;
		case IDC_COMBOSELECT:
			strcpy_s(pTTT->lpszText, 80, _T("选择题选项数量"));
			break;
		case IDC_LAST10TOPIC:
			strcpy_s(pTTT->lpszText, 80, _T("后退十题"));
			break;
		case IDC_LASTTOPIC:
			strcpy_s(pTTT->lpszText, 80, _T("后退一题"));
			break;
		case IDC_NEXTTOPIC:
			strcpy_s(pTTT->lpszText, 80, _T("前进一题"));
			break;
		case IDC_NEXT10Topic:
			strcpy_s(pTTT->lpszText, 80, _T("前进十题"));
			break;
		case IDC_PAPERTITLE:
			strcpy_s(pTTT->lpszText, 80, _T("输入试卷名称"));
			break;
		case IDC_TOPICTITLE:
			strcpy_s(pTTT->lpszText, 80, _T("输入题目内容"));
			break;
		case IDC_CHECKA:
			strcpy_s(pTTT->lpszText, 80, _T("选项A"));
			break;
		case IDC_CHECKB:
			strcpy_s(pTTT->lpszText, 80, _T("选项B"));
			break;
		case IDC_CHECKC:
			strcpy_s(pTTT->lpszText, 80, _T("选项C"));
			break;
		case IDC_CHECKD:
			strcpy_s(pTTT->lpszText, 80, _T("选项D"));
			break;
		case IDC_CHECKE:
			strcpy_s(pTTT->lpszText, 80, _T("选项E"));
			break;
		case IDC_ANS:
			strcpy_s(pTTT->lpszText, 80, _T("输入问题答案"));
			break;
		case IDC_ANSA:
			strcpy_s(pTTT->lpszText, 80, _T("输入答案A的内容"));
			break;
		case IDC_ANSB:
			strcpy_s(pTTT->lpszText, 80, _T("输入答案B的内容"));
			break;
		case IDC_ANSC:
			strcpy_s(pTTT->lpszText, 80, _T("输入答案C的内容"));
			break;
		case IDC_ANSD:
			strcpy_s(pTTT->lpszText, 80, _T("输入答案D的内容"));
			break;
		case IDC_ANSE:
			strcpy_s(pTTT->lpszText, 80, _T("输入答案E的内容"));
			break;
		case IDC_SEPRATOR:
			strcpy_s(pTTT->lpszText, 80, _T("在填空题答案中插入分隔符@"));
			break;
		case IDC_TOPICFILE:
			strcpy_s(pTTT->lpszText, 80, _T("题目附加文件，可选中附件右键移除"));
			break;
		case IDC_PAPERFILE:
			strcpy_s(pTTT->lpszText, 80, _T("试卷附加文件，可选中附件右键移除"));
			break;
		default:
			break;
		}
		return TRUE;
	}
	return FALSE;
}
//显示指定问题，修改界面显示
void CPaperEditorDlg::ShowFigureTopic(const stuTopic & topic,const int & pos)	
{
	m_editTopicTitle.SetWindowText(topic.m_title);
	CString s;
	s.Format("问题%d",pos + 1);
	SetDlgItemText(IDC_STATICQUESTION,s);
	m_viewPos = pos;
	((CButton *)GetDlgItem(IDC_RADIOSELECT))->SetCheck(topic.m_type == eTopicTypeSelect);	//切换题型状态
	((CButton *)GetDlgItem(IDC_RADIOBLANK))->SetCheck(topic.m_type == eTopicTypeBlank);
	((CButton *)GetDlgItem(IDC_RADIOQA))->SetCheck(topic.m_type == eTopicTypeQA);
	m_topicType = eTopicTypeNone;
	switch (topic.m_type)
	{
	case eTopicTypeSelect:
	{
		m_comboSelect.SetCurSel(topic.m_selectNum - 2);
		m_checkA.SetCheck(topic.m_checkA);
		m_checkB.SetCheck(topic.m_checkB);
		m_checkC.SetCheck(topic.m_checkC);
		m_checkD.SetCheck(topic.m_checkD);
		m_checkE.SetCheck(topic.m_checkE);
		m_editA.SetWindowText(topic.m_ansA);
		m_editB.SetWindowText(topic.m_ansB);
		m_editC.SetWindowText(topic.m_ansC);
		m_editD.SetWindowText(topic.m_ansD);
		m_editE.SetWindowText(topic.m_ansE);
		OnBnClickedRadioselect();
		break;
	}
	case eTopicTypeBlank:
	{
		OnBnClickedRadioblank();
		m_editAnswer.SetWindowText(topic.m_ans);
		break;
	}
	case eTopicTypeQA:
	{
		OnBnClickedRadioqa();
		m_editAnswer.SetWindowText(topic.m_ans);
		break;
	}
	default:
		break;
	}
}
//新建试卷
void CPaperEditorDlg::OnBnClickedNew()
{
    if(IsPaperModify())								//若当前存在未完成编辑的试卷，提示用户保存
		PromptSave();
	m_paper = stuPaper();							//放弃当前试卷内容
	m_paper.m_vecTopic.push_back(stuTopic());		//插入一个题目	
	m_editPaperTitle.SetWindowText("");
	m_strWindowTitle = _T("试卷编辑器 -UnTitle"); 	//更新窗口标题
	SetWindowText(m_strWindowTitle);
	m_curPaperPath = "";							//新建试卷，保存路径设置为空
	((CComboBox *)GetDlgItem(IDC_COMBOSELECT))->SetCurSel(2);
	((CButton *)GetDlgItem(IDC_RADIOBLANK))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_RADIOQA))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_RADIOSELECT))->SetCheck(TRUE);  //更新为初始状态
	m_topicType = eTopicTypeNone;					//确保重新加载显示
	CleanTopicContent();
	ShowFigureTopic(m_paper.m_vecTopic[0], 0);
	m_tempPaper = m_paper;							//更新m_tempPaper信息为初始信息
}
//打开试卷
void CPaperEditorDlg::OnBnClickedOpen()
{
    if(IsPaperModify())								//若当前存在未完成编辑的试卷，提示用户保存
		PromptSave();								//若当前试卷是新建试卷，则点保存弹路径浏览框，否则不弹
	CFileDialog openFileDlg(TRUE, ".exm","",OFN_HIDEREADONLY | OFN_READONLY, "Exam files(*.exm)|*.exm||", NULL);
	openFileDlg.m_ofn.lpstrTitle = "打开";
	if (openFileDlg.DoModal() == IDOK)
	{
		CString filePath = openFileDlg.GetPathName();
		m_paper = stuPaper();
		CLoadSavePaper loader;
		if(loader.LoadPaper(m_paper,ePaperTypePaper,filePath))				//解析文件内容，并将题目显示在试卷编辑器中，浏览界面默认停在第一道题
		{
			CleanTopicContent();								//清空当前界面问题内容
			m_curPaperPath = filePath;
			m_strWindowTitle = _T("试卷编辑器 ") + m_curPaperPath;//打开成功，修改窗口标题为试卷路径及名称
			SetWindowText(m_strWindowTitle);
			m_editPaperTitle.SetWindowText(m_paper.m_paperTitle);//更新试卷名
			if (m_paper.m_vecTopic.size() < 1)
				m_paper.m_vecTopic.push_back(stuTopic());
			m_topicType = eTopicTypeNone;						//确保重新加载显示
			ShowFigureTopic(m_paper.m_vecTopic[0], 0);
			m_tempPaper = m_paper;								//更新m_tempPaper信息为初始信息
		}
		else
			AfxMessageBox(_T("打开试卷失败！"));
	}
}
//保存试卷
void CPaperEditorDlg::OnBnClickedSave()
{
	SaveCurTopic(m_topicType);								//保存、检查
	if (!CheckTopicValid())
		return;										//分配分数
	CString tempPath = m_curPaperPath;
	if (m_curPaperPath.IsEmpty())							//选择保存路径
	{
		CFileDialog openFileDlg(FALSE, ".exm", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Exam files(*.exm)| *.exm||", NULL);
		openFileDlg.m_ofn.lpstrTitle = "保存";
		if (openFileDlg.DoModal() == IDOK)
			tempPath = openFileDlg.GetPathName();
	}
	if (tempPath.IsEmpty())							//选择保存路径时取消
		return;
	CLoadSavePaper saver;
	if (saver.SavePaper(m_paper,ePaperTypePaper,tempPath))
	{
		m_curPaperPath = tempPath;
		m_strWindowTitle = _T("试卷编辑器 ") + m_curPaperPath;
		SetWindowText(m_strWindowTitle);
		m_tempPaper = m_paper;
		AfxMessageBox("保存成功！");
	}
	else
		AfxMessageBox("保存失败，文件无法打开.");
}
//另存试卷
void CPaperEditorDlg::OnBnClickedSaveas()
{
	SaveCurTopic(m_topicType);								//保存、检查
	if (!CheckTopicValid())
		return;									//分配分数
	CFileDialog openFileDlg(FALSE, ".exm", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Exam files(*.exm)| *.exm||", NULL);
	openFileDlg.m_ofn.lpstrTitle = "另存为";
	CString tempPath = m_curPaperPath;
	if (openFileDlg.DoModal() == IDOK)
		tempPath = openFileDlg.GetPathName();
	if (tempPath.IsEmpty())							//选择保存路径时取消
		return;
	CLoadSavePaper saver;
	if (saver.SavePaper(m_paper, ePaperTypePaper, tempPath))
	{
		m_curPaperPath = tempPath;
		m_strWindowTitle = _T("试卷编辑器 ") + m_curPaperPath;
		SetWindowText(m_strWindowTitle);
		m_tempPaper = m_paper;
		AfxMessageBox("保存成功！");
	}
	else
		AfxMessageBox("保存失败，文件无法打开.");
}
//分数配置
void CPaperEditorDlg::OnBnClickedScore()
{
	CSetScoreDlg  dlgScore(m_paper.m_scoreSet, m_paper.m_vecTopic.size(), this);
	if (dlgScore.DoModal() == IDOK)
	{
		m_paper.m_scoreSet = dlgScore.m_set;
		SetPaperScore();
	}
}
//附加文件到试卷  //未使用
void CPaperEditorDlg::OnBnClickedAddfile()
{
	////Author&Time:sunx@2017-12-05
	////1-According window select files
	//BOOL isOpen = TRUE;//Save-TRUE Open-FALSE  
	//CString defaultDir = _T("");//Default file path
	//CString fileName = _T("");//Default file name  
	//CString filter = _T("All Files(*.*)| *.*||");//File type  
	//CFileDialog openFileDlg(isOpen, defaultDir, fileName, 
	//	OFN_ENABLESIZING |//Use mouse to change file picture size
	//	OFN_HIDEREADONLY
	//	, filter, NULL);
	//openFileDlg.GetOFN().lpstrInitialDir = _T("");
	//INT_PTR result = openFileDlg.DoModal();
	//CString filePath = defaultDir + "\\" + fileName;
	//if (result == IDOK)
	//{
	//	filePath = openFileDlg.GetPathName();
	//}
	//
	////2-Add file path to struct
	//m_paper.m_paperFiles.push_back(filePath);
}
//打印和预览调用，将当前试卷保存为htm文件，加载htm文件显示
void CPaperEditorDlg::ShowHtmDialog(const stuPaper & paper,const ePaperViewType & viewType,const CString & filePath)
{
	SaveCurTopic(m_topicType);
	SetPaperScore();								//分配分数
	CGenerateHtm htm;
	if(htm.GeneratePaperToHtm(m_paper,filePath,viewType))
	{
		CViewDialog dlg(IDD_VIEWDIALOG,IDR_HTML_VIEWDIALOG,paper, viewType, CString("file:///") + filePath, this);
		dlg.DoModal();
	}
}
//预览
void CPaperEditorDlg::OnBnClickedPreview()
{
	ShowHtmDialog(m_paper,ePaperViewTypeView,m_currentPath + "test1.htm");
}
//打印
void CPaperEditorDlg::OnBnClickedPrint()
{
	HKEY hkey;
	CString keyPath = "Software\\Microsoft\\Internet Explorer\\PageSetup";		//打印之前设置IE打印时不打印页眉  页脚打印页号
	if(ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER,keyPath,0,KEY_WRITE,&hkey))
	{
		LRESULT r = RegSetValueEx(hkey,"header",0,REG_SZ,(LPBYTE)"",0);			//清空页眉
		LRESULT r1 = RegSetValueEx(hkey,"footer",0,REG_SZ,(LPBYTE)"&b&p/&P",8);	//页脚 类似：1/4
		RegFlushKey(hkey);
		RegCloseKey(hkey);
	}
	ShowHtmDialog(m_paper,ePaperViewTypePrint,m_currentPath + "test1.htm");
}
//新建题目
void CPaperEditorDlg::OnBnClickedNewtopic()			//保存、检查合法性、插入到末尾、清空界面
{
	SaveCurTopic(m_topicType);
	if (CheckTopicValid())
	{
		m_paper.m_vecTopic.push_back(stuTopic());
		m_viewPos = m_paper.m_vecTopic.size() - 1;
		m_paper.m_vecTopic[m_viewPos].m_type = m_topicType;
		if (m_topicType == eTopicTypeSelect)
			m_paper.m_vecTopic[m_viewPos].m_selectNum = m_comboSelect.GetCurSel() + 2;
		ShowFigureTopic(m_paper.m_vecTopic[m_viewPos],m_viewPos);
		CleanTopicContent();
	}
}
//插入题目
void CPaperEditorDlg::OnBnClickedInserttopic()		//保存、检查合法性、插入到当前位置、清空界面
{
	SaveCurTopic(m_topicType);
	if(CheckTopicValid())
	{
		std::vector<stuTopic>::iterator it = m_paper.m_vecTopic.begin() + m_viewPos;
		m_paper.m_vecTopic.insert(it, stuTopic());
		m_paper.m_vecTopic[m_viewPos].m_type = m_topicType;
		if (m_topicType == eTopicTypeSelect)
			m_paper.m_vecTopic[m_viewPos].m_selectNum = m_comboSelect.GetCurSel() + 2;
		ShowFigureTopic(m_paper.m_vecTopic[m_viewPos], m_viewPos);
		CleanTopicContent();
	}
}
//后退10题
void CPaperEditorDlg::OnBnClickedLast10topic()		//保存当前的、再跳转显示
{
	SaveCurTopic(m_topicType);
	m_viewPos -= 10;
	m_viewPos = m_viewPos > 0 ? m_viewPos : 0;
	CleanTopicContent();
	ShowFigureTopic(m_paper.m_vecTopic[m_viewPos],m_viewPos);
}
//上一题
void CPaperEditorDlg::OnBnClickedLasttopic()		//保存当前的、再跳转显示
{
	SaveCurTopic(m_topicType);
	m_viewPos -= 1;
	m_viewPos = m_viewPos > 0 ? m_viewPos : 0;
	CleanTopicContent();
	ShowFigureTopic(m_paper.m_vecTopic[m_viewPos],m_viewPos);
}
//下一题
void CPaperEditorDlg::OnBnClickedNexttopic()		//保存当前的、再跳转显示
{
	SaveCurTopic(m_topicType);
	m_viewPos += 1;
	m_viewPos = m_viewPos > (int)m_paper.m_vecTopic.size() - 1 ? m_paper.m_vecTopic.size() - 1 : m_viewPos;
	CleanTopicContent();
	ShowFigureTopic(m_paper.m_vecTopic[m_viewPos],m_viewPos);
}
//前进10题
void CPaperEditorDlg::OnBnClickedNext10topic()		//保存当前的、再跳转显示
{
	SaveCurTopic(m_topicType);
	m_viewPos += 10;
	m_viewPos = m_viewPos > (int)m_paper.m_vecTopic.size() - 1 ? m_paper.m_vecTopic.size() - 1 : m_viewPos;
	CleanTopicContent();
	ShowFigureTopic(m_paper.m_vecTopic[m_viewPos],m_viewPos);
}
//删除
void CPaperEditorDlg::OnBnClickedDelete()
{
	if (m_paper.m_vecTopic.size() < 1)
		return;
	m_paper.m_vecTopic.erase(m_paper.m_vecTopic.begin() + m_viewPos);		//删除
	if(m_paper.m_vecTopic.size() < 1)				//删完了，添加一个
		m_paper.m_vecTopic.push_back(stuTopic());
	m_viewPos = m_viewPos > (int)m_paper.m_vecTopic.size() - 1 ? m_paper.m_vecTopic.size() - 1 : m_viewPos;
	CleanTopicContent();
	ShowFigureTopic(m_paper.m_vecTopic[m_viewPos], m_viewPos);
	SetPaperScore();
}
//附加文件到题目
void CPaperEditorDlg::OnBnClickedAddfiletotopic()
{
}
//分隔符
void CPaperEditorDlg::OnBnClickedSeprator()
{
	m_editAnswer.SendMessage(WM_CHAR, '@', 0);	//@分割答案
}
//检查题目是不是合法
BOOL CPaperEditorDlg::CheckTopicValid()
{
	CString str;
	m_editPaperTitle.GetWindowText(m_paper.m_paperTitle);	//试卷名
	if (m_paper.m_paperTitle.GetLength() < 1)
	{
		AfxMessageBox("请输入试卷名!");
		m_editPaperTitle.SetFocus();
		return FALSE;
	}
	for(size_t i = 0;i < m_paper.m_vecTopic.size();++i)		//遍历检查
	{
		str.Format("问题%d:",i + 1);
		if(m_paper.m_vecTopic[i].m_title.GetLength() < 1)		//题目
		{
			AfxMessageBox(str + "请输入题目内容!");
			ShowFigureTopic(m_paper.m_vecTopic[i],i);
			m_editTopicTitle.SetFocus();
			return FALSE;
		}
		if(m_paper.m_vecTopic[i].m_type == eTopicTypeSelect)
		{
			int cul = m_paper.m_vecTopic[i].m_selectNum;
			if(m_paper.m_vecTopic[i].m_ansA.GetLength() < 1)		//选项内容不能为空
			{
				AfxMessageBox(str + "请输入A选项内容!");
				ShowFigureTopic(m_paper.m_vecTopic[i],i);
				m_editA.SetFocus();
				return FALSE;
			}
			if(m_paper.m_vecTopic[i].m_ansB.GetLength() < 1)
			{
				AfxMessageBox(str + "请输入B选项内容!");
				ShowFigureTopic(m_paper.m_vecTopic[i],i);
				m_editB.SetFocus();
				return FALSE;
			}
			if(cul > 2 && m_paper.m_vecTopic[i].m_ansC.GetLength() < 1)
			{
				AfxMessageBox(str + "请输入C选项内容!");
				ShowFigureTopic(m_paper.m_vecTopic[i],i);
				m_editC.SetFocus();
				return FALSE;
			}
			if(cul > 3 && m_paper.m_vecTopic[i].m_ansD.GetLength() < 1)
			{
				AfxMessageBox(str + "请输入D选项内容!");
				ShowFigureTopic(m_paper.m_vecTopic[i],i);
				m_editD.SetFocus();
				return FALSE;
			}
			if(cul > 4 && m_paper.m_vecTopic[i].m_ansE.GetLength() < 1)
			{
				AfxMessageBox(str + "请输入E选项内容!");
				ShowFigureTopic(m_paper.m_vecTopic[i],i);
				m_editE.SetFocus();
				return FALSE;
			}
			std::vector<CString>vec;					//判断选择题选项相同
			vec.push_back(m_paper.m_vecTopic[i].m_ansA);
			vec.push_back(m_paper.m_vecTopic[i].m_ansB);
			if (cul > 2)
				vec.push_back(m_paper.m_vecTopic[i].m_ansC);
			if (cul > 3)
				vec.push_back(m_paper.m_vecTopic[i].m_ansD);
			if (cul > 4)
				vec.push_back(m_paper.m_vecTopic[i].m_ansE);
			for (size_t j = 0;j < vec.size();++j)
			{
				for (size_t k = j + 1; k < vec.size();++k)
				{
					if (vec[j] == vec[k])
					{
						CString temps;
						temps.Format("选项%c与选项%c相同，请修改!", 'A' + j, 'A' + k);
						AfxMessageBox(str + temps);
						ShowFigureTopic(m_paper.m_vecTopic[i], i);
						return FALSE;
					}
				}
			}
			std::vector<int> vec1;
			vec1.push_back(m_paper.m_vecTopic[i].m_checkA);		//选项判断
			vec1.push_back(m_paper.m_vecTopic[i].m_checkB);
			if (cul > 2)
				vec1.push_back(m_paper.m_vecTopic[i].m_checkC);
			if (cul > 3)
				vec1.push_back(m_paper.m_vecTopic[i].m_checkD);
			if (cul > 4)
				vec1.push_back(m_paper.m_vecTopic[i].m_checkE);
			int count = 0;
			for (size_t j = 0;j < vec1.size();++j)
				if (vec1[j] == BST_CHECKED)
					++count;
			if (count < 1)							//至少有一个选中的
			{
				AfxMessageBox(str + "请选择正确的答案!");
				ShowFigureTopic(m_paper.m_vecTopic[i], i);
				return FALSE;
			}
		}
		else
		{
			if(m_paper.m_vecTopic[i].m_ans.GetLength() < 1)		//答案不能为空
			{
				AfxMessageBox(str + "请输入正确答案!");
				ShowFigureTopic(m_paper.m_vecTopic[i],i);
				m_editAnswer.SetFocus();
				return FALSE;
			}
		}
	}
	SetPaperScore();										//分配分数
	return TRUE;
}
//保存当前题目
void CPaperEditorDlg::SaveCurTopic(const eTopicType & type)
{
	m_editPaperTitle.GetWindowText(m_paper.m_paperTitle);	//保存试卷名
	CString s;
	m_editTopicTitle.GetWindowText(s);	
	m_paper.m_vecTopic[m_viewPos].m_title = s;		//标题、类型
	m_paper.m_vecTopic[m_viewPos].m_type = type;
	switch(type)
	{
	case eTopicTypeSelect:
	{
		m_paper.m_vecTopic[m_viewPos].m_selectNum = m_comboSelect.GetCurSel() + 2;	//选项、答案
		m_paper.m_vecTopic[m_viewPos].m_checkA = m_checkA.GetCheck();
		m_paper.m_vecTopic[m_viewPos].m_checkB = m_checkB.GetCheck();
		m_editA.GetWindowText(s);
		m_paper.m_vecTopic[m_viewPos].m_ansA = s;
		m_editB.GetWindowText(s);
		m_paper.m_vecTopic[m_viewPos].m_ansB = s;
		if(m_paper.m_vecTopic[m_viewPos].m_selectNum > 2)
		{
			m_paper.m_vecTopic[m_viewPos].m_checkC = m_checkC.GetCheck();
			m_editC.GetWindowText(s);
			m_paper.m_vecTopic[m_viewPos].m_ansC = s;
		}
		if(m_paper.m_vecTopic[m_viewPos].m_selectNum > 3)
		{
			m_paper.m_vecTopic[m_viewPos].m_checkD = m_checkD.GetCheck();
			m_editD.GetWindowText(s);
			m_paper.m_vecTopic[m_viewPos].m_ansD = s;
		}
		if(m_paper.m_vecTopic[m_viewPos].m_selectNum > 4)
		{
			m_paper.m_vecTopic[m_viewPos].m_checkE = m_checkE.GetCheck();
			m_editE.GetWindowText(s);
			m_paper.m_vecTopic[m_viewPos].m_ansE = s;
		}
		break;
	}
	case eTopicTypeBlank:
	case eTopicTypeQA:
	{
		m_editAnswer.GetWindowText(s);			//答案
		m_paper.m_vecTopic[m_viewPos].m_ans = s;
		break;
	}
	default:
		break;
	}
}
//清空当前题目界面内容
void CPaperEditorDlg::CleanTopicContent()
{
	m_editTopicTitle.SetWindowText("");
	m_checkA.SetCheck(BST_UNCHECKED);
	m_checkB.SetCheck(BST_UNCHECKED);
	m_checkC.SetCheck(BST_UNCHECKED);
	m_checkD.SetCheck(BST_UNCHECKED);
	m_checkE.SetCheck(BST_UNCHECKED);
	m_editA.SetWindowText("");
	m_editB.SetWindowText("");
	m_editC.SetWindowText("");
	m_editD.SetWindowText("");
	m_editE.SetWindowText("");
	m_editAnswer.SetWindowText("");
}
//检查当前试卷是否被修改
BOOL CPaperEditorDlg::IsPaperModify()
{
	SaveCurTopic(m_topicType);			//保存当前正在编辑的题目
	return !(m_tempPaper == m_paper);
}
//提示用户是否保存当前正在编辑的试卷
void CPaperEditorDlg::PromptSave()
{
	if (IDYES == MessageBox(_T("是否保存当前正在编辑的试卷？"), _T("提示"), MB_YESNO))  //选择保存
		OnBnClickedSave();
}
//关闭试卷编辑器
void CPaperEditorDlg::OnCancel()
{
	//AfxMessageBox(_T("关闭试卷编辑器"));
	////若当前存在未完成编辑的试卷，提示用户保存
	if (IsPaperModify())
	{
		PromptSave();
	}
	CDialogEx::OnCancel();
}
// 设置试卷分数
void CPaperEditorDlg::SetPaperScore()
{
	if (m_paper.m_scoreSet.m_type == eScoreTypeAverage)			//平均分配
	{
		double score = m_paper.m_scoreSet.m_total / m_paper.m_vecTopic.size();
		for (size_t i = 0;i < m_paper.m_vecTopic.size();++i)
			m_paper.m_vecTopic[i].m_score = score;
	}
	else if (m_paper.m_scoreSet.m_type == eScoreTypeSingle)		//单个分配
	{
		size_t len = min(m_paper.m_vecTopic.size(), m_paper.m_scoreSet.m_vecSigle.size());
		for (size_t i = 0;i < len;++i)
			m_paper.m_vecTopic[i].m_score = m_paper.m_scoreSet.m_vecSigle[i];
	}
	else if (m_paper.m_scoreSet.m_type == eScoreTypeBatch)		//批量分配
	{
		double choice = 0, multiChoice = 0, blank = 0, qa = 0;
		for (size_t i = 0;i < m_paper.m_vecTopic.size();++i)	//计算各种题型数量
		{
			if (m_paper.m_vecTopic[i].m_type == eTopicTypeBlank)		//填空
				++blank;
			else if (m_paper.m_vecTopic[i].m_type == eTopicTypeQA)		//问答
				++qa;
			else if (m_paper.m_vecTopic[i].m_type == eTopicTypeSelect && m_paper.m_vecTopic[i].IsSingleChoice())//单选
				++choice;
			else                                  //多选
				++multiChoice;
		}
		choice = choice == 0 ? 0 : m_paper.m_scoreSet.m_batch[0] / choice;				//每题的分数
		multiChoice = multiChoice == 0 ? 0 : m_paper.m_scoreSet.m_batch[1] / multiChoice;
		blank = blank == 0 ? 0 : m_paper.m_scoreSet.m_batch[2] / blank;
		qa = qa == 0 ? 0 : m_paper.m_scoreSet.m_batch[3] / qa;
		for (size_t i = 0;i < m_paper.m_vecTopic.size();++i)			//分数分配
		{
			if (m_paper.m_vecTopic[i].m_type == eTopicTypeBlank)		//填空
				m_paper.m_vecTopic[i].m_score = blank;
			else if (m_paper.m_vecTopic[i].m_type == eTopicTypeQA)		//问答
				m_paper.m_vecTopic[i].m_score = qa;
			else if (m_paper.m_vecTopic[i].m_type == eTopicTypeSelect && m_paper.m_vecTopic[i].IsSingleChoice())//单选
				m_paper.m_vecTopic[i].m_score = choice;
			else                                  //多选
				m_paper.m_vecTopic[i].m_score = multiChoice;
		}
	}
}
