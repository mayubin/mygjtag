// wndtest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "gjtag.h"
#include "wndtest.h"


// wndtest

IMPLEMENT_DYNAMIC(wndtest, CWnd)

wndtest::wndtest()
{

}

wndtest::~wndtest()
{
}


BEGIN_MESSAGE_MAP(wndtest, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// wndtest ��Ϣ�������



void wndtest::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	dc.SetTextColor(RGB(255,0,0));
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(10,10,"JTAG Scanning...");
}
