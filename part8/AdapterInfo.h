/*
 * File     :   AdapterInfo.h
 * Descript :   获取所有adaptor(显卡与显示器对)的详细信息
 */
#ifndef ADAPTER_INFO_H
#define ADAPTER_INFO_H

#include <d3d9.h>

#include <vector>
/*
 *  Class       : AdapterInfo
 *  Function    : 获取计算机所有adaptor(显卡端口与显示设备对）的详细信息
 */
class AdapterInfo
{
public:
    typedef  std::vector<D3DADAPTER_IDENTIFIER9> ADAPTER_INFO;


    /*
     *  Param[in] pD3D D3D对象
     *  Function  构造AdapterInfo对象
     */
    AdapterInfo(LPDIRECT3D9 pD3D);
    ~AdapterInfo();

    /*
     *  Param[in]  void
     *  Return      返回计算机的adaptor的个数
     *  Descript    获取计算机的adaptor的个数
     */
    size_t GetAdapterCount()
    {
        return m_infos.size();
    }
    /*
     *  Param[in]   void
     *  Return      const AdapterInfo::ADAPTER_INFO 获取D3D对象详细信息的容器
     *  Descript    获取D3D对象详细信息容器，每个元素的具体格式参考 D3DADAPTER_IDENTIFIER9 对象的文档
     */
    const AdapterInfo::ADAPTER_INFO & GetInfo()
    {
        return m_infos;
    }
private:
    /*
     * 初始化D3D对象，并获取信息存入对象的内部容器中
     */
    int Init();

private:
    LPDIRECT3D9 m_pD3D;

    ADAPTER_INFO m_infos;
};


#endif
