// PinTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "gjtag.h"
#include "PinTest.h"


// CPinTest

IMPLEMENT_DYNAMIC(CPinTest, CWnd)

CPinTest::CPinTest()
{

}

CPinTest::~CPinTest()
{
}


BEGIN_MESSAGE_MAP(CPinTest, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CPinTest ��Ϣ�������



void CPinTest::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.SetTextColor(RGB(0,255,255));
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(10,10,"PinTest JTAG");
}

