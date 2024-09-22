
// ScreenShotDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ScreenShot.h"
#include "ScreenShotDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScreenShotDlg 对话框



CScreenShotDlg::CScreenShotDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCREENSHOT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenShotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_WClASS, SSWIN_CLASS);
	DDX_Control(pDX, IDC_EDIT_WNAME, SSWIN_NAME);
	DDX_Control(pDX, IDC_CHECK_IFSELF, IF_SELF);
	DDX_Control(pDX, IDC_Edit_ScrFre, Scfre);
	DDX_Control(pDX, IDC_Edit_W_out, OUTIMG_W);
	DDX_Control(pDX, IDC_Edit_H_out, OUTIMG_H);
	DDX_Control(pDX, IDC_COMBO1, ComBox_SELF);
	DDX_Control(pDX, IDC_Edit_SCOPEW, ASSIGN_W);
	DDX_Control(pDX, IDC_Edit_SCOPEH, ASSIGN_H);
	DDX_Control(pDX, IDC_STATIC_TIPS, TEXT_TARGETWR);
	DDX_Control(pDX, IDC_STATIC_TEXTASSIGN, TEXT_ASSIGN_SC);
	DDX_Control(pDX, IDC_BUTTON_STOP, CSB_stop);
	DDX_Control(pDX, IDC_STATIC_OUTSIZE, TEXT_OUTSIZE);
	DDX_Control(pDX, IDC_EDIT_OUTDIR, SCEDITOUTDIR);
	DDX_Control(pDX, IDC_EDIT1, TEXT_SCCOUNT);
	DDX_Control(pDX, IDC_Edit_X, EditAssignLeft);
	DDX_Control(pDX, IDC_Edit_Y, EditAssignTop);
	DDX_Control(pDX, IDC_Edit_W, EditAssignRight);
	DDX_Control(pDX, IDC_Edit_H, EditAssignBottom);
	DDX_Control(pDX, IDC_CHECK_outsize, CHECK_OUTSIZE);
	DDX_Control(pDX, IDC_BUTTON_Start, ButtonStartSC);
}

BEGIN_MESSAGE_MAP(CScreenShotDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Start, &CScreenShotDlg::OnBnClickedButtonStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_IFSELF, &CScreenShotDlg::OnBnClickedCheckIfself)
ON_BN_CLICKED(IDC_BUTTON_Start2, &CScreenShotDlg::OnBnClickedButtonStart2)
ON_BN_CLICKED(IDC_BUTTON_STOP, &CScreenShotDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CScreenShotDlg 消息处理程序

BOOL CScreenShotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetTimer(TIMER2, 1, 0); //定时器
	Scfre.SetWindowTextW(L"3000");
	SSWIN_CLASS.SetWindowTextW(L"");
	SSWIN_NAME.SetWindowTextW(L"");
	OUTIMG_W.SetWindowTextW(L"352");
	OUTIMG_H.SetWindowTextW(L"352");
	ASSIGN_W.SetWindowTextW(L"352");
	ASSIGN_H.SetWindowTextW(L"352");
	SCEDITOUTDIR.SetWindowTextW(L"Train");
	TEXT_SCCOUNT.SetWindowTextW(L"1");
	CHECK_OUTSIZE.SetCheck(BST_CHECKED);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CScreenShotDlg::OnPaint()
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
HCURSOR CScreenShotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CScreenShotDlg::OnBnClickedButtonStart()
{
	ButtonStartSC.SetWindowTextW(L"已开始！");
	CSB_stop.SetWindowTextW(L"停止");
	SetTimer(TIMER1, timefreq, 0); //定时器
	// TODO: 在此添加控件通知处理程序代码
}

extern void process_screen();
void CScreenShotDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case TIMER1:
	{	
		process_screen();
		CString num;
		num.Format(L"%d", cutsc_count);
		TEXT_SCCOUNT.SetWindowTextW(num);
		break;
	}
	case TIMER2:
	{
		getmousepos();
		break;
	}
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CScreenShotDlg::getmousepos() {	
	if (::GetKeyState(VK_LCONTROL) < 0 && ::GetKeyState(VK_LBUTTON) < 0)
	{
		POINT cursorPos;
		::GetCursorPos(&cursorPos);
		CString num;
		num.Format(L"%d", cursorPos.x);
		EditAssignLeft.SetWindowTextW(num);
		num.Format(L"%d", cursorPos.y);
		EditAssignTop.SetWindowTextW(num);
		
	}
	if (::GetKeyState(VK_LSHIFT) < 0 && ::GetKeyState(VK_LBUTTON) < 0)
	{
		POINT cursorPos;
		::GetCursorPos(&cursorPos);
		CString num;
		num.Format(L"%d", cursorPos.x);
		EditAssignRight.SetWindowTextW(num);
		num.Format(L"%d", cursorPos.y);
		EditAssignBottom.SetWindowTextW(num);
	}
}

void CScreenShotDlg::OnBnClickedCheckIfself()
{
	if (IF_SELF.GetCheck() == BST_CHECKED)
		ComBox_SELF.ShowWindow(SW_SHOW);
	else
		ComBox_SELF.ShowWindow(SW_HIDE);
	// TODO: 在此添加控件通知处理程序代码
}


extern void autowokedir();

void CScreenShotDlg::OnBnClickedButtonStart2()
{
	static bool once = false;
	// TODO: 在此添加控件通知处理程序代码
	if (once)
		::CloseHandle(TargetWin);
	if (!once)
		once = !once;

	SSWIN_CLASS.GetWindowTextW(winclass);
	SSWIN_NAME.GetWindowTextW(winname);
	TargetWin = ::FindWindow(winclass.GetString(), winname.GetString());
	if (!TargetWin) {
		TEXT_TARGETWR.SetWindowTextW(L"指定窗口Rect:");
		TEXT_ASSIGN_SC.SetWindowTextW(L"当前截屏Rect:");
		AfxMessageBox(L"获取窗口句柄失败！");
		return;
	}

	CString tips = L"配置内容为：\n";
	tips += (L"窗口类名：" + winclass + L"\n");
	tips += (L"窗口标题：" + winname + L"\n");
	RECT rect;
	::GetWindowRect(TargetWin, &rect);

	CString num;
	num.Format(L"%d", rect.left);
	tips += L"窗口区域为 x:" + num; 
	num.Format(L"%d", rect.top);
	tips += L" y:" + num;
	num.Format(L"%d", rect.right);
	tips += L" width:" + num;
	num.Format(L"%d", rect.bottom);
	tips += L" hight:" + num + L"\n";

	CString stttsx = L"指定窗口Rect:";
	num.Format(L"%d", rect.left);
	stttsx += L" left:" + num;
	num.Format(L"%d", rect.top);
	stttsx += L" top:" + num;
	num.Format(L"%d", rect.right);
	stttsx += L" right:" + num;
	num.Format(L"%d", rect.bottom);
	stttsx += L" bottom:" + num + L"\n";
	TEXT_TARGETWR.SetWindowTextW(stttsx);
	
	isselfdo = (IF_SELF.GetCheck() == BST_CHECKED);
	tips += (isselfdo ? L"自定义截图：真\n" : L"自定义截图：假\n");

	memcpy(&TarWinRect, &rect, sizeof(RECT));
	if (isselfdo)
	{
		CString t;
		ComBox_SELF.GetWindowTextW(t);
		if (t == L"左上区域") {
			scselftype = REGION_UL;
		}
		else if (t == L"左下区域") {
			scselftype = REGION_DL;
		}
		else if (t == L"右上区域") {
			scselftype = REGION_UR;
		}
		else if (t == L"右下区域") {
			scselftype = REGION_DR;
		}
		else {
			scselftype = REGION_DEF;
		}
		switch (scselftype)
		{
		case REGION_UL:
		{
			CString ASW;
			ASSIGN_W.GetWindowTextW(ASW);
			CString ASH;
			ASSIGN_H.GetWindowTextW(ASH);
			int w= _ttoi(ASW);
			int h = _ttoi(ASH);
			TarWinRect.right = TarWinRect.left + w;
			TarWinRect.bottom = TarWinRect.top + h;
			TEXT_ASSIGN_SC.SetWindowTextW((L"当前截屏rect: left:" + std::to_wstring(TarWinRect.left) + L" top:" + std::to_wstring(TarWinRect.top) + L" right:" + std::to_wstring(TarWinRect.right) + L" buttom:" + std::to_wstring(TarWinRect.bottom) + L"\n").c_str());
			TEXT_OUTSIZE.SetWindowTextW(L"截图尺寸：" + ASW + L"x" + ASH +L"\n");
			tips += L"左上区域-->指定范围:\n截图尺寸：" + ASW + L"x" + ASH + L"\n";
			tips += (L"截屏rect: left:" +std::to_wstring(TarWinRect.left) + L" top:" + std::to_wstring(TarWinRect.top) + L" right:" + std::to_wstring(TarWinRect.right) + L" buttom:" + std::to_wstring(TarWinRect.bottom) + L"\n").c_str();
			break;
		}	
		case REGION_DL:
		{
			CString ASW;
			ASSIGN_W.GetWindowTextW(ASW);
			CString ASH;
			ASSIGN_H.GetWindowTextW(ASH);
			int w = _ttoi(ASW);
			int h = _ttoi(ASH);
			TarWinRect.right = TarWinRect.left + w;
			TarWinRect.top = TarWinRect.bottom - h;
			TEXT_ASSIGN_SC.SetWindowTextW((L"当前截屏rect: left:" + std::to_wstring(TarWinRect.left) + L" top:" + std::to_wstring(TarWinRect.top) + L" right:" + std::to_wstring(TarWinRect.right) + L" buttom:" + std::to_wstring(TarWinRect.bottom) + L"\n").c_str());
			TEXT_OUTSIZE.SetWindowTextW(L"截图尺寸：" + ASW + L"x" + ASH + L"\n");
			tips += L"左下区域-->指定范围:\n截图尺寸：" + ASW + L"x" + ASH + L"\n";
			tips += (L"截屏rect: left:" + std::to_wstring(TarWinRect.left) + L" top:" + std::to_wstring(TarWinRect.top) + L" right:" + std::to_wstring(TarWinRect.right) + L" buttom:" + std::to_wstring(TarWinRect.bottom) + L"\n").c_str();
			break;			
		}
	
		case REGION_UR:
		{
			CString ASW;
			ASSIGN_W.GetWindowTextW(ASW);
			CString ASH;
			ASSIGN_H.GetWindowTextW(ASH);
			int w = _ttoi(ASW);
			int h = _ttoi(ASH);
			TarWinRect.left = TarWinRect.right - w;
			TarWinRect.bottom = TarWinRect.top + h;
			TEXT_ASSIGN_SC.SetWindowTextW((L"当前截屏rect: left:" + std::to_wstring(TarWinRect.left) + L" top:" + std::to_wstring(TarWinRect.top) + L" right:" + std::to_wstring(TarWinRect.right) + L" buttom:" + std::to_wstring(TarWinRect.bottom) + L"\n").c_str());
			TEXT_OUTSIZE.SetWindowTextW(L"截图尺寸：" + ASW + L"x" + ASH + L"\n");
			tips += L"右上区域-->指定范围:\n截图尺寸：" + ASW + L"x" + ASH + L"\n";
			tips += (L"截屏rect: left:" + std::to_wstring(TarWinRect.left) + L" top:" + std::to_wstring(TarWinRect.top) + L" right:" + std::to_wstring(TarWinRect.right) + L" buttom:" + std::to_wstring(TarWinRect.bottom) + L"\n").c_str();
			break;
		}
			
		case REGION_DR:
		{
			CString ASW;
			ASSIGN_W.GetWindowTextW(ASW);
			CString ASH;
			ASSIGN_H.GetWindowTextW(ASH);
			int w = _ttoi(ASW);
			int h = _ttoi(ASH);
			TarWinRect.left = TarWinRect.right - w;
			TarWinRect.top = TarWinRect.bottom - h;
			TEXT_ASSIGN_SC.SetWindowTextW((L"当前截屏rect: left:" + std::to_wstring(TarWinRect.left) + L" top:" + std::to_wstring(TarWinRect.top) + L" right:" + std::to_wstring(TarWinRect.right) + L" buttom:" + std::to_wstring(TarWinRect.bottom) + L"\n").c_str());
			TEXT_OUTSIZE.SetWindowTextW(L"截图尺寸：" + ASW + L"x" + ASH + L"\n");
			tips += L"右下区域-->指定范围:\n截图尺寸：" + ASW + L"x" + ASH + L"\n";
			tips += (L"截屏rect: left:" + std::to_wstring(TarWinRect.left) + L" top:" + std::to_wstring(TarWinRect.top) + L" right:" + std::to_wstring(TarWinRect.right) + L" buttom:" + std::to_wstring(TarWinRect.bottom) + L"\n").c_str();
			break;
		}	
		default: {
			tips += L"自定义区域-->指定RECT: left:";
			CString t_rect;
			EditAssignLeft.GetWindowTextW(t_rect);
			int l = _ttoi(t_rect);
			tips += t_rect;

			EditAssignTop.GetWindowTextW(t_rect);
			int t = _ttoi(t_rect);
			tips +=L" top:" + t_rect;

			EditAssignRight.GetWindowTextW(t_rect);
			int r = _ttoi(t_rect);
			if (r <= l)
			{
				r = l + 1;
				tips += L"\nERROS right:erro value.value of right must bigger than value of left.\n";
			}
			else
			{
				tips += L" right:" + t_rect;
			}		

			EditAssignBottom.GetWindowTextW(t_rect);
			int b = _ttoi(t_rect);
			if (b <= t)
			{
				b = t + 1;
				tips += L"\nERROS bottom:erro value.value of bottom must bigger than value of up.\n";
			}
			else
			{
				tips += L" bottom:" + t_rect + L"\n";
			}	
			TarWinRect = { l,t,r,b };
			break;
			}
		}	
		if (CHECK_OUTSIZE.GetCheck() == BST_CHECKED) {
			num.Format(L"%d", TarWinRect.right - TarWinRect.left);
			OUTIMG_W.SetWindowTextW(num);
			num.Format(L"%d", TarWinRect.bottom - TarWinRect.top);
			OUTIMG_H.SetWindowTextW(num);
		}
	}
	else
	{	
		stttsx = L"当前截屏Rect:";
		num.Format(L"%d", rect.left);
		stttsx += L" left:" + num;
		num.Format(L"%d", rect.top);
		stttsx += L" top:" + num;
		num.Format(L"%d", rect.right);
		stttsx += L" right:" + num;
		num.Format(L"%d", rect.bottom);
		stttsx += L" bottom:" + num + L"\n";
		TEXT_ASSIGN_SC.SetWindowTextW(stttsx);

		int cut_width = rect.right - rect.left;
		int cut_hight = rect.bottom - rect.top;
		CString cuttips = L"截图尺寸：";
		num.Format(L"%d", cut_width);
		cuttips += num + L" x ";
		num.Format(L"%d", cut_hight);
		cuttips += num + L"\n";
		TEXT_OUTSIZE.SetWindowTextW(cuttips);
		tips += cuttips;

		if (CHECK_OUTSIZE.GetCheck() == BST_CHECKED)
		{
			num.Format(L"%d", rect.right - rect.left);
			OUTIMG_W.SetWindowTextW(num);
			num.Format(L"%d", rect.bottom - rect.top);
			OUTIMG_H.SetWindowTextW(num);
		}
	}

	CString toutsizew;
	OUTIMG_W.GetWindowTextW(toutsizew);
	outimg_width = _ttoi(toutsizew);
	CString toutsizeh;
	OUTIMG_H.GetWindowTextW(toutsizeh);
	outimg_hight = _ttoi(toutsizeh);
	tips += L"输出尺寸：" + toutsizew + L" x " + toutsizeh + L"\n";

	CString  OutImgDIR;
	SCEDITOUTDIR.GetWindowTextW(OutImgDIR);
	tips += L"输出目录：" + OutImgDIR + L"\n";

	extern char myoutdir[];
	CStringA OutImgDIRA(OutImgDIR.GetString());
	strcpy_s(myoutdir,MAX_PATH, OutImgDIRA.GetString());
	autowokedir();


	CString T_TimeFreq;
	Scfre.GetWindowTextW(T_TimeFreq);
	timefreq = _ttoi(T_TimeFreq);
	tips += L"截图频率："+ T_TimeFreq + L"ms\n";

	CString T_SCCOUT;
	TEXT_SCCOUNT.GetWindowTextW(T_SCCOUT);
	cutsc_count = _ttoi(T_SCCOUT);
	tips += L"截图计数：" + T_SCCOUT + L"次\n";
	AfxMessageBox(tips);
}


void CScreenShotDlg::OnBnClickedButtonStop()
{
	ButtonStartSC.SetWindowTextW(L"开始");
	CSB_stop.SetWindowTextW(L"已停止");
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(TIMER1);
}

CScreenShotDlg::~CScreenShotDlg() {
	::CloseHandle(TargetWin);
}