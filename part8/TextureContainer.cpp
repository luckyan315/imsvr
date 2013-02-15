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


bool TextureContainer::IsExist(std::string & path)
{
    TextureCollection::iterator it = std::find(m_data.begin(), m_data.end(), path);
    if(it != m_data.end())
    {
        return true;
    }
    return false;
}
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