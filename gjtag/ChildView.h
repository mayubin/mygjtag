// ChildView.h : CChildView ��Ľӿ�
//


#pragma once

#include "PinTest.h"

// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:
	CPinTest m_pingtest;

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

