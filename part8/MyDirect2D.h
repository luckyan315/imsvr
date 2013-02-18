#ifndef MY_DIRECT_2D_H
#define MY_DIRECT_2D_H

#include <vector>
#include "MyDirect.h"


class TextureContainer;
class CMyDirect2D : public CMyDirect
{
public:
    CMyDirect2D(HWND hWnd, UINT adapterID = D3DADAPTER_DEFAULT);
    ~CMyDirect2D(void);

//Override
    void OnDeviceInited();
    void OnDeviceLost();
    void OnRender2D();

    void SetObjectFPS(double fps){ m_fps = fps;}
    const double GetObjectFPS() const {return m_fps;}


    void FillTextures(std::vector<std::string> & pathes);

	void SetSyncOutputWnd(LPVOID lpWnd){m_lpSyncWnd=lpWnd;};

protected:
    void CleanupMe();

private:
    LPD3DXSPRITE m_Sprite;
    TextureContainer * m_Textures;
    double m_fps;
	LPVOID m_lpSyncWnd;
};

#endif
