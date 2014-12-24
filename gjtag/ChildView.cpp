// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "gjtag.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CChildView ��Ϣ�������

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);


	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	
	// TODO: �ڴ˴������Ϣ����������
	
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0,255,0));
	dc.TextOut(100,100,"Hello,world");
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	m_pingtest.MoveWindow(0,cy-32,cx,cy);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rect;
	GetClientRect(&rect);
	m_pingtest.Create(NULL,NULL,WS_CHILD,rect,this,0,NULL);
	m_pingtest.ShowWindow(SW_SHOW);
	return 0;
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	GetClientRect(&rect);
	//GetWindowRect(&rect);
	CBrush br(RGB(0,0,0));
	pDC->FillRect(&rect,&br);
	return FALSE;
	return CWnd::OnEraseBkgnd(pDC);
}
