#pragma once

#include "MemDCEx.h"

// CWaveScope
#define MAX_PEN 5

class CWaveScope : public CWnd
{
	DECLARE_DYNAMIC(CWaveScope)

public:
	CWaveScope();
	virtual ~CWaveScope();

protected:
	DECLARE_MESSAGE_MAP()

protected:

	// 线程相关的变量
	BOOL m_bRunThread;
	CMemDCEx * m_pGridDC;			// 绘制网格线的DC
	CMemDCEx * m_pScopeDC;			// 绘制波形的DC
	CMemDCEx * m_pCompDC;			// 合成的DC

	HANDLE m_thread;				// 线程句柄
	ULONG mt_ID_DrawThread;			// 线程ID

	int m_nWidth;					// 窗口宽
	int m_nHeight;					// 窗口高

	int grid_width;
	int grid_height;

	COLORREF wave_color;
	COLORREF grid_color;
	COLORREF bg_color;				// 背景颜色
	int data_len;					// 数据长度
	double scale;					// 比例

	double * data;					// 数据
	double hi_value;				// 最高值
	double lo_value;				// 最低值
public:
	afx_msg void OnPaint();

	// 设置数据来源
	// void SetData( CWaveData * data );
	afx_msg void OnSize(UINT nType, int cx, int cy);

	// 波形绘制线程
	static DWORD WINAPI DrawScopeThread(void * param);
	void DrawScope();
	void Disable();
	void Active();
	afx_msg void OnDestroy();
	void DeleteAll(void);

	// 设置显示值的数值范围(最大值，最小值)
	void SetValueScope( double min_vale,double max_value);
	
	// 绘制背景及网格
	void DrawGrid();

	// 求给定数值对应的显示Y位置
	int GetY(double v);

	// 绘制波型
	void DrawData();

	// 设置显示数据指针
	void SetData(double * data_buf,int len);
};


