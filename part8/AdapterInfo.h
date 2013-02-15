#ifndef ADAPTER_INFO_H
#define ADAPTER_INFO_H

#include <d3d9.h>

#include <vector>

class AdapterInfo
{
public:
    typedef  std::vector<D3DADAPTER_IDENTIFIER9> ADAPTER_INFO;




    AdapterInfo(LPDIRECT3D9 pD3D);
    ~AdapterInfo();


    int Init();


    size_t GetAdapterCount()
    {
        return m_infos.size();
    }

    const AdapterInfo::ADAPTER_INFO & GetInfo()
    {
        return m_infos;
    }


private:
    LPDIRECT3D9 m_pD3D;

    ADAPTER_INFO m_infos;
};


HRESULT TestGetInfo()  ;


#endif
