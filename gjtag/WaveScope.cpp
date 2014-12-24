// WaveScope.cpp : 实现文件
//

#include "stdafx.h"
#include "WaveScope.h"
#include "MemDC.h"
#include "gdiplus.h"
#pragma comment(lib,"C:\\Program Files\\Microsoft SDKs\\Windows\\v6.0A\\Lib\\GdiPlus.lib")

// CWaveScope
using namespace Gdiplus;



IMPLEMENT_DYNAMIC(CWaveScope, CWnd)

CWaveScope::CWaveScope()
{
	m_pGridDC = NULL;
	m_pScopeDC = NULL;
	m_pCompDC = NULL;

	wave_color = RGB(0,255,0);
	grid_color = RGB(127,127,127);
	bg_color = RGB(0,0,0);
	// grid_width = PI*GRID_PI;
	grid_width = 44;
	grid_height = 44;
	data_len = 0;
	data = NULL;
	scale = -1;

}

CWaveScope::~CWaveScope()
{

}


BEGIN_MESSAGE_MAP(CWaveScope, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CWaveScope 消息处理程序


void CWaveScope::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.SetTextColor(RGB(255,255,255));
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(10,10,"WaveScope");
}

void CWaveScope::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
/*	CRect rect(0,0,cx,cy);
	m_nWidth = cx;
	m_nHeight = cy;


	CDC * dc = GetDC();
	if(m_pGridDC)
	{
		delete m_pGridDC;
		m_pGridDC = NULL;
	}
	
	m_pGridDC = new CMemDCEx(dc,rect);

	if(m_pScopeDC)
	{
		delete m_pScopeDC;
		m_pScopeDC = NULL;
	}

	m_pScopeDC = new CMemDCEx(dc,rect);

	if(m_pCompDC)
	{
		delete m_pCompDC;
		m_pCompDC = NULL;
	}

	m_pCompDC = new CMemDCEx(dc,rect);

	// 启动绘图线程
	Active();*/
}

// 显示线程静态函数
DWORD WINAPI CWaveScope::DrawScopeThread(void * param)
{
	CWaveScope * scope = (CWaveScope*)param;
	
	// 调用成员函数的绘制函数
	if(scope) 
		scope->DrawScope();
	return 0;
}

// 显示线程类成员函数
void CWaveScope::DrawScope()
{
	while(m_bRunThread)
	{
		Sleep(15);
		if(m_pGridDC)
		{
			TRACE("DrawScope");
			// 绘制跑动的小方块
			static int x =10;
			static int d =10;
			static int a =0;
			a+=d;
			if(a>=250) d = -10;
			if(a<=50) d = +10;
			x+=4;
			if(x>1280) x =-100;
			m_pGridDC->FillSolidRect(0,0,m_nWidth,m_nHeight,RGB(0,0,0));
			m_pGridDC->FillSolidRect(x,10,10,10,RGB(0,a,0));

			m_pCompDC->FillSolidRect(0,0,m_nWidth,m_nHeight,RGB(0,0,0));
			m_pCompDC->BitBlt(m_pGridDC);	
			m_pCompDC->BitBlt(m_pScopeDC);
		}
		m_pCompDC->Show();
	}
}

void CWaveScope::Disable()
{
	m_bRunThread = 0;
	DWORD ec;
	// 是否更新在线标志的线程正在运行?
	BOOL b;
	do{
		Sleep(50);
		b = GetExitCodeThread(m_thread,&ec);
	}
	while(b && ec == STILL_ACTIVE);
}

void CWaveScope::Active()
{
	m_bRunThread = 1;
	DWORD ec;
	// 是否更新在线标志的线程正在运行?
	BOOL b=GetExitCodeThread(m_thread,&ec);
	if(!b || ec!=STILL_ACTIVE)
	{
		// 如果其尚未运行或已结束,则建立新的线程
		m_thread=CreateThread(NULL,65536,DrawScopeThread,this,0,&mt_ID_DrawThread);
		// 设置一个最高的优先级
		SetThreadPriority(m_thread,THREAD_PRIORITY_HIGHEST);
	}
}

void CWaveScope::OnDestroy()
{
	CWnd::OnDestroy();
	DeleteAll();
}

void CWaveScope::DeleteAll(void)
{
	TRACE ("Delete All DC");
	if(m_pGridDC)
	{
		delete m_pGridDC;
		m_pGridDC = NULL;
	}
	if(m_pScopeDC)
	{
		delete m_pScopeDC;
		m_pScopeDC = NULL;
	}
	if(m_pCompDC)
	{
		delete m_pCompDC;
		m_pCompDC = NULL;
	}

}

void CWaveScope::SetValueScope( double min_vale,double max_value)
{
	hi_value = max_value;
	lo_value = min_vale;
	scale = -m_nHeight/(max_value-min_vale);
}

void CWaveScope::DrawGrid()
{
	CRect rt(0,0,m_nWidth,m_nHeight);
	CBrush br(bg_color);
	m_pGridDC->FillRect(&rt,&br);

	CPen pen(PS_SOLID,1,grid_color);
	CPen *oldpen = m_pGridDC->SelectObject(&pen);
	for(int i = 0; i < m_nWidth; i+=grid_width)
	{
		m_pGridDC->MoveTo(i,0);
		m_pGridDC->LineTo(i,m_nHeight);
	}
	for(int i = 0; i < m_nHeight; i+=grid_height)
	{
		m_pGridDC->MoveTo(0,i);
		m_pGridDC->LineTo(0,m_nWidth);
	}
	m_pScopeDC->SelectObject(oldpen);
}

// 得到给定数据的图形坐标y值
int CWaveScope::GetY(double v)
{
	int y = m_nHeight + (v - lo_value) * scale;
	if (y>m_nHeight) 
		return m_nHeight;
	if (y<0) 
		return 0;
	return y;
}

void CWaveScope::DrawData()
{
	if(data!=NULL)
	{
		m_pScopeDC->FillSolidRect(0,0,m_nWidth,m_nHeight,RGB(0,0,0));
		CPen pen(PS_SOLID,1,wave_color);
		CPen *oldpen = m_pScopeDC->SelectObject(&pen);
		m_pScopeDC->MoveTo(0,GetY(data[0]));
		for(int i=0;i<data_len;i++)
		{
			m_pScopeDC->LineTo(i,GetY(data[i]));
			if(i>=m_nWidth)
				break;
		}
		m_pScopeDC->SelectObject(oldpen);
	}
}

void CWaveScope::SetData(double * data_buf,int len)
{
	data = data_buf;
	data_len = len;
}
