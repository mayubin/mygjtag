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

	// �߳���صı���
	BOOL m_bRunThread;
	CMemDCEx * m_pGridDC;			// ���������ߵ�DC
	CMemDCEx * m_pScopeDC;			// ���Ʋ��ε�DC
	CMemDCEx * m_pCompDC;			// �ϳɵ�DC

	HANDLE m_thread;				// �߳̾��
	ULONG mt_ID_DrawThread;			// �߳�ID

	int m_nWidth;					// ���ڿ�
	int m_nHeight;					// ���ڸ�

	int grid_width;
	int grid_height;

	COLORREF wave_color;
	COLORREF grid_color;
	COLORREF bg_color;				// ������ɫ
	int data_len;					// ���ݳ���
	double scale;					// ����

	double * data;					// ����
	double hi_value;				// ���ֵ
	double lo_value;				// ���ֵ
public:
	afx_msg void OnPaint();

	// ����������Դ
	// void SetData( CWaveData * data );
	afx_msg void OnSize(UINT nType, int cx, int cy);

	// ���λ����߳�
	static DWORD WINAPI DrawScopeThread(void * param);
	void DrawScope();
	void Disable();
	void Active();
	afx_msg void OnDestroy();
	void DeleteAll(void);

	// ������ʾֵ����ֵ��Χ(���ֵ����Сֵ)
	void SetValueScope( double min_vale,double max_value);
	
	// ���Ʊ���������
	void DrawGrid();

	// �������ֵ��Ӧ����ʾYλ��
	int GetY(double v);

	// ���Ʋ���
	void DrawData();

	// ������ʾ����ָ��
	void SetData(double * data_buf,int len);
};


