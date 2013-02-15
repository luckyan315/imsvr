#pragma once


// CScreenWnd

class CScreenWnd : public CWnd
{
	DECLARE_DYNAMIC(CScreenWnd)

public:
    static const int WIDTH = 520;
    static const int HEIGHT = 520;

	CScreenWnd();
	virtual ~CScreenWnd();

// ÖØÐ´
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	DECLARE_MESSAGE_MAP()
};


