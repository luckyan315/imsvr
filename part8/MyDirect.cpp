#include "StdAfx.h"
#include "MyDirect.h"
#include <mmsystem.h>

#include <stdio.h>
#include <cassert>

#include "AcquireExecutionTime.h"


CMyDirect::CMyDirect(HWND hWnd, UINT adapterID)
:m_adapterID(adapterID)
,m_hWnd(hWnd)
,m_pD3D(NULL)
,m_pd3dDevice(NULL)
{
    ZeroMemory( &m_d3dpp, sizeof( m_d3dpp ) );  
}

CMyDirect::~CMyDirect(void)
{
    
    this->CleanupMe();

    this->Cleanup();
}


HRESULT CMyDirect::InitD3D(BOOL defaultWindowed)
{
    if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )  
    {
        //LOG_ERROR("Direct Create Error!");
        return E_FAIL;  
    }

    //Presentation Setting == render method
    m_d3dpp.Windowed         = defaultWindowed;  
    m_d3dpp.SwapEffect       = D3DSWAPEFFECT_DISCARD;  
    m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;  
    //m_d3dpp.BackBufferFormat = D3DFMT_R5G6B5;  
    m_d3dpp.BackBufferCount  = 1;
    m_d3dpp.BackBufferHeight = SCREEN_HEIGHT;
    m_d3dpp.BackBufferWidth = SCREEN_WIDTH;
    m_d3dpp.hDeviceWindow = m_hWnd;
    m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //这个可以提高速度

    // 创建D3D设备  
    if( FAILED( m_pD3D->CreateDevice( m_adapterID, D3DDEVTYPE_HAL, m_hWnd,  
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,  &m_d3dpp, &m_pd3dDevice ) ) )  
    {  
        //LOG_ERROR("Create Device Error!");
        return E_FAIL;  
    }  

    this->SetState();

    OnDeviceInited();

    return S_OK;
}

void CMyDirect::SetState()
{
     // 设置设备状态  

     // 设置渲染格式  
     m_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );  

     // 关闭光照  
     m_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );  


     m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,  TRUE);
     m_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
     m_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
     m_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
}

void CMyDirect::Cleanup()  
{  

    if( m_pd3dDevice != NULL )   
    {
        m_pd3dDevice->Release();  
        m_pd3dDevice = NULL;
    }

    if( m_pD3D != NULL )    
    {
        m_pD3D->Release();  
        m_pD3D = NULL;
    }

}  

void CMyDirect::ToggleFullScreen()
{
    m_d3dpp.Windowed = !m_d3dpp.Windowed;

    // Notify objects if needed
    OnDeviceLost();

    // Reset device
    HRESULT hResult = m_pd3dDevice->Reset(&m_d3dpp);
    if(FAILED(hResult))
    {
        //LOG_ERROR("Reset Device Error!");
       return ;
    }
    // Update window style
    if(m_d3dpp.Windowed)
    {
        SetWindowLong(m_d3dpp.hDeviceWindow, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        SetWindowPos(m_d3dpp.hDeviceWindow, HWND_TOP, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
            SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    }
    else
    {
        SetWindowLong(m_d3dpp.hDeviceWindow, GWL_STYLE, WS_POPUPWINDOW);
        SetWindowPos(m_d3dpp.hDeviceWindow, HWND_TOP, 0, 0, 0, 0,
            SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    }

    // Reset render states, etc
    SetState();
}

void CMyDirect::Render()
{
    assert(m_pd3dDevice);

    // 清除场景背景  
    m_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );  

    // 场景开始渲染  
    if( SUCCEEDED( m_pd3dDevice->BeginScene() ) )  
    {  

        OnRender2D();

        // 场景结束渲染  
        m_pd3dDevice->EndScene();  
    }  

    // 提交缓冲  
    m_pd3dDevice->Present( NULL, NULL, NULL, NULL );  

}

double CMyDirect::FPS(double elapseMS)
{
    static double fps = 0.0f;

    static int num = 0;
    ++num;

    static AcquireExecutionTime t;
    double ts = t.GetTimeSpanMS(false);
    if( ts  > elapseMS)
    {
        fps = (double)(num) * 1000 /  ts;
        num = 0;
        t.Reset();
    }
    return fps;
}


//Body -- Only For Test
void CMyDirect::OnDeviceInited()
{
    /*
    ::CreateTexture9(m_pd3dDevice);

    D3DXCreateSprite(m_pd3dDevice, &g_Sprite);
    */
}
//Body -- Only For Test
void CMyDirect::OnDeviceLost()
{
    /*
    g_Sprite->OnLostDevice();
    */
}

//Body -- Only For Test
void CMyDirect::OnRender2D()
{
    /*
        D3DXVECTOR2 Translation;
        Translation.x = 0;
        Translation.y = 0;

        D3DXVECTOR2 Scaling;
        Scaling.x = 1.0f;
        Scaling.y = 1.0f;

        D3DXMATRIX Mat;
        D3DXMatrixTransformation2D(&Mat, NULL, 0, &Scaling, NULL, 0, &Translation);


        g_Sprite->Begin(0);
        g_Sprite->SetTransform(&Mat);

   
        static int i = 0;
        static AcquireExecutionTime t;
        double ts = t.GetTimeSpanMS();
        if( ts >= 50)
        {
            ++i;
            i %= MAX_BMP_LEN;
            t.Reset();
        }

        m_pd3dDevice->SetTexture(0, g_pTextures[i]);
        g_Sprite->Draw(g_pTextures[i], NULL, NULL, NULL, 0xFFFFFFFF );

        g_Sprite->End();

        char str[128];
        sprintf(str, "%.3f", CMyDirect::FPS()); 
        SetWindowText(m_hWnd, str);
        */
}


//Body -- Only For Test
void CMyDirect::CleanupMe()
{
    /*
    for(int i = 0 ; i < MAX_BMP_LEN; ++i)
    {
        if(g_pTextures[i] != NULL)
        {
            g_pTextures[i]->Release(); 
            g_pTextures[i] = NULL;
        }
    }
    if(g_Sprite != NULL)
    {
        g_Sprite->Release();
        g_Sprite = NULL;
    }*/
}

