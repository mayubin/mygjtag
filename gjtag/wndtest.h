#pragma once


// wndtest

class wndtest : public CWnd
{
	DECLARE_DYNAMIC(wndtest)

public:
	wndtest();
	virtual ~wndtest();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


