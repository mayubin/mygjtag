// gjtag.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "gjtag.h"
#include "MainFrm.h"
#include "ppt.h"

// 使用 GPIPLUS 命名空间
#include "gdiplus.h"
using namespace Gdiplus;
ULONG_PTR  gdiplusToken;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CGjtagApp

BEGIN_MESSAGE_MAP(CGjtagApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CGjtagApp::OnAppAbout)
	ON_COMMAND(ID_LOADBSD, &CGjtagApp::OnLoadbsd)
END_MESSAGE_MAP()


// CGjtagApp 构造

CGjtagApp::CGjtagApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CGjtagApp 对象

CGjtagApp theApp;


// CGjtagApp 初始化

BOOL CGjtagApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	// 使用gdiplus要添加的初始化
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken,&gdiplusStartupInput,NULL);

	CWinApp::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	// 若要创建主窗口，此代码将创建新的框架窗口
	// 对象，然后将其设置为应用程序的主窗口对象
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// 创建并加载框架及其资源
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	
	pFrame->SetWindowText(_T("GRAPH Text"));

	// 打开并口设备,若打开失败则退出
/*	int n=OpenPpt();
	if(!n)
	{
		TRACE("OpenPpt=%d",n);
		AfxMessageBox("Can open the PPT port.\n",MB_OK|MB_ICONERROR);
		return FALSE;
	}
*/

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
	return TRUE;
}


// CGjtagApp 消息处理程序




// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CGjtagApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CGjtagApp 消息处理程序

/******************************************************************************
* GJTAG 程序后添加的函数
*******************************************************************************/
void CGjtagApp::OnLoadbsd()
{
	// AfxMessageBox("BSD");
	m_cpudata.LoadBSDFile(_T("at91sam9260_pqfp.bsd"));
	AfxMessageBox("AT91SAM9260.BSD File loaded!");
}
