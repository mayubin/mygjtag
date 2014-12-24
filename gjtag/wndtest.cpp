// wndtest.cpp : 实现文件
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



// wndtest 消息处理程序



void wndtest::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	dc.SetTextColor(RGB(255,0,0));
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(10,10,"JTAG Scanning...");
}
