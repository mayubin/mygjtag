#pragma once

#include "MemDCEx.h"

// CPinTest

class CPinTest : public CWnd
{
	DECLARE_DYNAMIC(CPinTest)

public:
	CPinTest();
	virtual ~CPinTest();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


