#pragma once
#include "memdc.h"
#include "MemDC.h"

class CMemDCEx :
	public CMemDC
{
public:
	CMemDCEx(CDC* pDC, CRect rect = CRect(0,0,0,0));
	~CMemDCEx(void);

	// ����������CDC��(��ʾ����)
	void Show();

	// ��pDC������������ǰMemDC��
	void BitBlt(CDC * pDC);
};
