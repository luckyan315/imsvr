#ifndef TEXTURE_CONTAINER_H

#define TEXTURE_CONTAINER_H

#include <vector>
#include <string>

#include <d3dx9.h> 

class TextureContainer
{

public:
    typedef char ImageType;
    typedef std::string TextureNode;
    typedef std::vector<TextureNode> TextureCollection;

    typedef std::vector<LPDIRECT3DTEXTURE9> TexturePtrCollection;


public:
    TextureContainer(LPDIRECT3DDEVICE9 pDevice);
    ~TextureContainer(void);

    LPDIRECT3DTEXTURE9 Get(size_t idx){return m_textures[idx];}


    void Clear();
    void Set(std::vector<std::string> & path);

    bool IsExist(std::string & path);

    void Append(std::string &path);
    void Remove(std::string & path);

    size_t GetSize() const {return m_data.size();}
    const std::vector<TextureNode> & GetData() const {return m_data;}

private:
    
    TextureCollection m_data;
    TexturePtrCollection m_textures;
    LPDIRECT3DDEVICE9 m_pDevice;
};

#endif
