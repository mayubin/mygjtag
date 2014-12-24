// gjtag.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "gjtag.h"
#include "MainFrm.h"
#include "ppt.h"

// ʹ�� GPIPLUS �����ռ�
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


// CGjtagApp ����

CGjtagApp::CGjtagApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CGjtagApp ����

CGjtagApp theApp;


// CGjtagApp ��ʼ��

BOOL CGjtagApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	// ʹ��gdiplusҪ��ӵĳ�ʼ��
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken,&gdiplusStartupInput,NULL);

	CWinApp::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	// ��Ҫ���������ڣ��˴��뽫�����µĿ�ܴ���
	// ����Ȼ��������ΪӦ�ó���������ڶ���
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// ���������ؿ�ܼ�����Դ
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	
	pFrame->SetWindowText(_T("GRAPH Text"));

	// �򿪲����豸,����ʧ�����˳�
/*	int n=OpenPpt();
	if(!n)
	{
		TRACE("OpenPpt=%d",n);
		AfxMessageBox("Can open the PPT port.\n",MB_OK|MB_ICONERROR);
		return FALSE;
	}
*/

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	return TRUE;
}


// CGjtagApp ��Ϣ�������




// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// �������жԻ����Ӧ�ó�������
void CGjtagApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CGjtagApp ��Ϣ�������

/******************************************************************************
* GJTAG �������ӵĺ���
*******************************************************************************/
void CGjtagApp::OnLoadbsd()
{
	// AfxMessageBox("BSD");
	m_cpudata.LoadBSDFile(_T("at91sam9260_pqfp.bsd"));
	AfxMessageBox("AT91SAM9260.BSD File loaded!");
}
