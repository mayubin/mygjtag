#pragma once
#include "memdc.h"
#include "MemDC.h"

class CMemDCEx :
	public CMemDC
{
public:
	CMemDCEx(CDC* pDC, CRect rect = CRect(0,0,0,0));
	~CMemDCEx(void);

	// 贴到给定的CDC上(显示出来)
	void Show();

	// 将pDC的内容贴到当前MemDC中
	void BitBlt(CDC * pDC);
};
