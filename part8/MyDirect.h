#ifndef MY_DIRECT_H
#define MY_DIRECT_H

#include <d3dx9.h> 

class CMyDirect
{
public:
    
    static const int SCREEN_WIDTH  = 800;
    static const int SCREEN_HEIGHT = 600;

    static double FPS(double elapseMS = 500.0);


    CMyDirect(HWND hWnd, UINT adapterID = D3DADAPTER_DEFAULT);
    virtual ~CMyDirect(void);




    virtual HRESULT InitD3D(BOOL defaultWindowed = TRUE);
    

    virtual void OnDeviceInited();
    

    virtual void OnDeviceLost();
    virtual void OnRender2D();

    

    void Cleanup();
    void Render();

    void ToggleFullScreen();

    LPDIRECT3DDEVICE9 GetD3DDevice() {return m_pd3dDevice;}

    D3DPRESENT_PARAMETERS & GetD3DPresent() {return m_d3dpp;}

    virtual void SetState();

    void SetAdapterID(const UINT adapterID){m_adapterID = adapterID;}
    const UINT GetAdapterID() {return m_adapterID;}

protected:
       void CleanupMe();

protected:

    UINT m_adapterID;
    HWND            m_hWnd;     //ref
    D3DPRESENT_PARAMETERS   m_d3dpp; // local var

    LPDIRECT3D9     m_pD3D;     // pointer need to free
    LPDIRECT3DDEVICE9       m_pd3dDevice; //pointer need to free
};

void CreateTexture9(LPDIRECT3DDEVICE9 pd3dDevice);

#endif

