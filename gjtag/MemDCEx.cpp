#include "StdAfx.h"
#include "MemDCEx.h"

CMemDCEx::CMemDCEx(CDC* pDC, CRect rect):CMemDC(pDC,rect)
{
}

CMemDCEx::~CMemDCEx(void)
{
}


void CMemDCEx::Show()
{
	// Copy the offscreen bitmap onto the screen.
	if(m_bMemDC)
	{
		// TRACE("fff w=%d h=%d",m_rect.Width(),m_rect.Height());
		m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
			this, m_rect.left, m_rect.top, SRCCOPY);
	}
};

void CMemDCEx::BitBlt(CDC * pDC)
{
	CMemDC::BitBlt(m_rect.left,m_rect.top,m_rect.Width(),m_rect.Height(),
		pDC,m_rect.left,m_rect.top,SRCPAINT);
}