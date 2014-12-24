// gjtag.h : gjtag 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "ChipData.h"

// CGjtagApp:
// 有关此类的实现，请参阅 gjtag.cpp
//

class CGjtagApp : public CWinApp
{
public:
	CGjtagApp();

	CCPUData m_cpudata;

// 重写
public:
	virtual BOOL InitInstance();

// 实现

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLoadbsd();
};

extern CGjtagApp theApp;