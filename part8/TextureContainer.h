/*
 * File     :  TextureContainer.h
 * Descript :  纹理容器类， 从多个图片路径中载入数据到D3D的纹理对象容器中。
 */
#ifndef TEXTURE_CONTAINER_H
#define TEXTURE_CONTAINER_H

#include <vector>
#include <string>
#include <d3dx9.h> 

/*
 *  Class    : TextureContainer
 *  Function : 纹理容器类，包含一些基本操作，添加，删除，查询是否存在，清除等操作
 */
class TextureContainer
{

public:
    typedef std::string TextureNode;
    typedef std::vector<TextureNode> TextureCollection;

    typedef std::vector<LPDIRECT3DTEXTURE9> TexturePtrCollection;


public:
    
    TextureContainer(LPDIRECT3DDEVICE9 pDevice);
    ~TextureContainer(void);

    /*
     *  Param[in] idx   纹理对象再容器中的索引
     *  return          返回纹理对象结构
     *  Descritp        基于index获取对应的纹理对象
     */
    LPDIRECT3DTEXTURE9 Get(size_t idx){return m_textures[idx];}

    /*
     *  删除纹理容器内的所有纹理对象
     */
    void Clear();
    /*
     * Param[in] path  一些图片所在的路径（绝对路径或者相对路径）
     * Return    void
     * Descript        输入图片路径，载入所有图片数据到纹理容器中
     */
    void Set(std::vector<std::string> & path);

    /*
     *  判断给定路径的纹理是否存在与纹理容器中
     */
    bool IsExist(std::string & path);

    /*
     *  Param[in]   图片路径
     *  Return  void
     *  Descript    添加一个指定路径的图片到纹理容器中
     */
    void Append(std::string &path);
    /*
     *  Param[in] 图片路径
     *  Return  void
     *  Descript   从纹理容器中删除指定路径的纹理信息
     */
    void Remove(std::string & path);

    /*
     * 获取纹理对象中纹理的数目
     */
    size_t GetSize() const {return m_data.size();}
    /*
     * 获取纹理容器的实际容器对象
     */
    const std::vector<TextureNode> & GetData() const {return m_data;}

private:
    
    TextureCollection m_data;
    TexturePtrCollection m_textures;
    LPDIRECT3DDEVICE9 m_pDevice;
};

#endif
