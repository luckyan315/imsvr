// ScreenWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScreenWnd.h"


// CScreenWnd

IMPLEMENT_DYNAMIC(CScreenWnd, CWnd)

CScreenWnd::CScreenWnd()
{

}

CScreenWnd::~CScreenWnd()
{
}



BOOL CScreenWnd::PreCreateWindow(CREATESTRUCT& cs)
{
    if( !CWnd::PreCreateWindow(cs) )
        return FALSE;

    return TRUE;
}

BEGIN_MESSAGE_MAP(CScreenWnd, CWnd)
END_MESSAGE_MAP()



// CScreenWnd ��Ϣ�������


