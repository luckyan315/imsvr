/*
 * File     :   AdapterInfo.cpp
 * Descript :   获取所有adaptor(显卡与显示器对)的详细信息
 */
#include "stdafx.h"
#include "AdapterInfo.h"

AdapterInfo::AdapterInfo(LPDIRECT3D9 pD3D)
:m_pD3D(pD3D)
{
    this->Init();
}
AdapterInfo::~AdapterInfo()
{

}

/*
 * 初始化D3D对象，并获取信息存入对象的内部容器中
 */
int AdapterInfo::Init()
{
    UINT cnt = m_pD3D->GetAdapterCount();


    for(UINT i = 0; i < cnt; ++i)
    {
        D3DADAPTER_IDENTIFIER9 adpInfo;
        if(D3D_OK == m_pD3D->GetAdapterIdentifier(i, 0, &adpInfo))
        {
            m_infos.push_back(adpInfo);
        }
        else
        {
            return -1;
        }
    }
    return 0;
}
