#include "stdafx.h"
#include "MyDirect2D.h"


#include <stdio.h>
#include <d3dx9.h>  
#include <cassert>

#include "AcquireExecutionTime.h"
#include "TextureContainer.h"
#include "GUI_ScanTestDlg.h"

CMyDirect2D::CMyDirect2D(HWND hWnd, UINT adapterID)
:CMyDirect(hWnd, adapterID)
, m_Sprite(NULL)
, m_Textures(NULL)
, m_fps(200.0)
, m_lpSyncWnd(NULL)
{

}
CMyDirect2D::~CMyDirect2D()
{
    this->CleanupMe();
}

void CMyDirect2D::OnDeviceInited()
{
    assert(m_pd3dDevice != NULL);
    D3DXCreateSprite(m_pd3dDevice, &m_Sprite);
    m_Textures = new TextureContainer(m_pd3dDevice);
}

void CMyDirect2D::OnDeviceLost()
{
    m_Sprite->OnLostDevice();
}


void CMyDirect2D::OnRender2D()
{
    if(m_Textures->GetSize() == 0)
    {
        return ;
    }

    D3DXVECTOR2 Translation;
    Translation.x = 0;
    Translation.y = 0;

    D3DXVECTOR2 Scaling;
    Scaling.x = 1.0f;
    Scaling.y = 1.0f;

    D3DXMATRIX Mat;
    D3DXMatrixTransformation2D(&Mat, NULL, 0, &Scaling, NULL, 0, &Translation);

    m_Sprite->Begin(0);
    m_Sprite->SetTransform(&Mat);



    static int i = 0;
    static AcquireExecutionTime t;
    double ts = t.GetTimeSpanMS();
    if( ts >= 1000/m_fps)
    {
        ++i;
        i %= m_Textures->GetSize();
        t.Reset();
		//同步输出
		if(m_lpSyncWnd!=NULL)
		{
			CGUI_ScanTestDlg *pDlg=(CGUI_ScanTestDlg*)m_lpSyncWnd;
			pDlg->SyncOutput();	//同步输出
		}
    }

    LPDIRECT3DTEXTURE9 pTexture = m_Textures->Get(i);
    if(pTexture != NULL)
    {
        m_pd3dDevice->SetTexture(0,pTexture );
        m_Sprite->Draw(pTexture, NULL, NULL, NULL, 0xFFFFFFFF );
    }
    else
    {
        assert(0);
    }

    m_Sprite->End();

    // Show the FPS on windows Title
    char str[128];
    sprintf(str, "%.3f", CMyDirect::FPS()); 
    SetWindowText(m_hWnd, str);
}

void CMyDirect2D::CleanupMe()
{
    delete m_Textures;
    m_Textures = NULL;

    if(m_Sprite != NULL)
    {
        m_Sprite->Release();
        m_Sprite = NULL;
    }
}

// after OnInited this function will be called
void CMyDirect2D::FillTextures(std::vector<std::string> & pathes)
{
    m_Textures->Set(pathes);
}