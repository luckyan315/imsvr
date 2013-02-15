/*
 * File     :  TextureContainer.cpp
 * Descript :  纹理容器类， 从多个图片路径中载入数据到D3D的纹理对象容器中。
 */
#include "StdAfx.h"
#include "TextureContainer.h"

#include <algorithm>
#include <d3dx9.h> 

TextureContainer::TextureContainer(LPDIRECT3DDEVICE9 pDevice)
:m_pDevice(pDevice)
{
}

TextureContainer::~TextureContainer(void)
{
    this->Clear();
}


/*
 *  判断给定路径的纹理是否存在与纹理容器中
 */
bool TextureContainer::IsExist(std::string & path)
{
    TextureCollection::iterator it = std::find(m_data.begin(), m_data.end(), path);
    if(it != m_data.end())
    {
        return true;
    }
    return false;
}
/*
 *  删除纹理容器内的所有纹理对象
 */
void TextureContainer::Clear()
{
    TexturePtrCollection::iterator it = m_textures.begin();
    for(; it != m_textures.end(); ++it)
    {
        (*it)->Release();
    }
    m_textures.clear();
    m_data.clear();
}
/*
 * Param[in] path  一些图片所在的路径（绝对路径或者相对路径）
 * Return    void
 * Descript        输入图片路径，载入所有图片数据到纹理容器中
 */
void TextureContainer::Set(std::vector<std::string> & path)
{
    if(m_data.size() > 0)
        this->Clear();

    std::vector<std::string>::iterator it = path.begin();
    for(; it != path.end(); ++it)
    {
        this->Append(*it);
    }
}

/*
 *  Param[in]   图片路径
 *  Return  void
 *  Descript    添加一个指定路径的图片到纹理容器中
 */
void TextureContainer::Append(std::string &path)
{
    if(IsExist(path) == false) 
    {
        //Load Texture into device
        LPDIRECT3DTEXTURE9 pTexture;
        D3DXCreateTextureFromFileEx(m_pDevice, path.c_str(), 0, 0, 0, 0,
            D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT,
            D3DX_DEFAULT , 0, NULL, NULL, &pTexture);

        m_textures.push_back(pTexture);
        m_data.push_back(path);
    }
}
/*
 *  Param[in] 图片路径
 *  Return  void
 *  Descript   从纹理容器中删除指定路径的纹理信息
 */
void TextureContainer::Remove(std::string & path)
{
    size_t sz = m_data.size();
    for(size_t i = 0; i < sz; i++)
    {
        if(m_data[i] == path)
        {
            m_textures[i]->Release();
            TexturePtrCollection::iterator tit = m_textures.begin();
            std::advance(tit, i);
            m_textures.erase(tit);

            TextureCollection::iterator it = m_data.begin();
            std::advance(it, i);
            m_data.erase(it);
        }
    }
}
