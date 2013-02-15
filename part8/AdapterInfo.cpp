
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




HRESULT TestGetInfo()  
{  
    LPDIRECT3D9             g_pD3D       = NULL; //Direct3D对象  
    //创建Direct3D对象, 该对象用来创建Direct3D设备对象  
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )  
        return E_FAIL;  

    AdapterInfo info(g_pD3D);


    unsigned int cnt = ( unsigned int)info.GetAdapterCount();
    printf("Adapter Count %d\n", cnt);


    for(unsigned int i = 0; i < cnt; ++i)
    {
        const D3DADAPTER_IDENTIFIER9 & adpInfo = info.GetInfo()[i];


        printf("info of adapter(%d):\n", i+1);
        printf("\tDriver[%s]\n", adpInfo.Driver);
        printf("\tDescription[%s]\n", adpInfo.Description);
        printf("\tDevName[%s]\n", adpInfo.DeviceName);
        printf("\tVendorId[%d]\n", adpInfo.VendorId);
        printf("\tDriverVersion[%d]\n", adpInfo.DriverVersion);
    }
    return S_OK;  
}  