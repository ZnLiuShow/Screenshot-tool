
// ScreenShotDlg.h: 头文件
//

#pragma once

#define REGION_DEF 0
#define REGION_UL 1
#define REGION_DL 2
#define REGION_UR 3
#define REGION_DR 4
// CScreenShotDlg 对话框
class CScreenShotDlg : public CDialogEx
{
// 构造
public:
	CScreenShotDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CScreenShotDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREENSHOT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	void getmousepos();
public:
	CString winclass;
	CString winname;
	bool isselfdo;
	HWND TargetWin;
	int scselftype;
	int timefreq;
	int outimg_width;
	int outimg_hight;

	RECT TarWinRect;
	CString OutImgDIR;
	unsigned int cutsc_count;
public:
	// 窗口类名
	CEdit SSWIN_CLASS;
	// 窗口标题名
	CEdit SSWIN_NAME;
	afx_msg void OnBnClickedButtonStart();
	CButton IF_SELF;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 截图的频率
	CEdit Scfre;
	// 输出图片宽度
	CEdit OUTIMG_W;
	// 输出图片高度
	CEdit OUTIMG_H;
	// 自定义区域截图
	CComboBox ComBox_SELF;
	afx_msg void OnBnClickedCheckIfself();
    // 指定宽
	CEdit ASSIGN_W;
	// 指定高
	CEdit ASSIGN_H;
	afx_msg void OnBnClickedButtonStart2();
	CStatic TEXT_TARGETWR;
	CStatic TEXT_ASSIGN_SC;
	CButton CSB_stop;
	afx_msg void OnBnClickedButtonStop();
	// 输出的尺寸
	CStatic TEXT_OUTSIZE;
	CEdit SCEDITOUTDIR;
	// 截屏计数
	CEdit TEXT_SCCOUNT;
	CEdit EditAssignLeft;
	CEdit EditAssignTop;
	CEdit EditAssignRight;
	CEdit EditAssignBottom;
	CButton CHECK_OUTSIZE;
	CButton ButtonStartSC;
};
