// gjtag.h : gjtag Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "ChipData.h"

// CGjtagApp:
// �йش����ʵ�֣������ gjtag.cpp
//

class CGjtagApp : public CWinApp
{
public:
	CGjtagApp();

	CCPUData m_cpudata;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLoadbsd();
};

extern CGjtagApp theApp;