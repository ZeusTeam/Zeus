#include "globaldef.h"
#include "texture.h"

Texture::Texture()
    : m_Sprite_ptr(NULL)
    , m_Texture(NULL)
    , m_TextureHeight(0)
    , m_TextureWidth(0)
    , m_TextureX(0)
    , m_TextureY(0)
    , m_nFrame(0)
{
}

Texture::~Texture()
{
    if (m_Texture)
    {
        hge->Texture_Free(m_Texture);
        m_Texture = NULL;
    }
    if (m_Sprite_ptr)
    {
        delete m_Sprite_ptr;
        m_Sprite_ptr = NULL;
    }

    if (!m_vecFrameSprite.empty())
    {
        for (auto it = m_vecFrameSprite.begin();
            it != m_vecFrameSprite.end(); it++)
        {
            delete (*it);
        }
    }
}

bool Texture::Load(const std::string& strPath,
        float x, float y)
{
    //暂时这样，完成POOL之后再进行替换
    m_Texture = hge->Texture_Load(strPath.c_str());
    if (!m_Texture)
    {
        return false;
    }
    m_TextureX = x;
    m_TextureY = y;
    m_TextureWidth = (float)hge->Texture_GetWidth(m_Texture);
    m_TextureHeight = (float)hge->Texture_GetHeight(m_Texture);

    m_Sprite_ptr = new hgeSprite(m_Texture, m_TextureX, m_TextureY, m_TextureWidth, m_TextureHeight);

    if (!m_Sprite_ptr)
    {
        return false;
    }

    return true;
}

bool Texture::LoadFrame(const std::string& strPath,
                        float y, float width, float height)
{
    //暂时这样，完成POOL之后再进行替换
    m_Texture = hge->Texture_Load(strPath.c_str());
    if (!m_Texture)
    {
        return false;
    }
    int nTexWidth = hge->Texture_GetWidth(m_Texture);
    for (int index = 0; index < nTexWidth; index++)
    {
        m_vecFrameSprite.push_back(
            new hgeSprite(m_Texture, index * width, y, width, height));
    }
    m_TextureWidth = width;
    m_TextureHeight = height;
    return true;
}

void Texture::Render(float x, float y)
{
    m_Sprite_ptr->Render(x, y);
}

void Texture::RenderFrame(int nFramePos, float x, float y)
{
    if (nFramePos > (int)m_vecFrameSprite.size() || m_vecFrameSprite.empty())
    {
        return;
    }
    m_vecFrameSprite[nFramePos]->Render(x, y);
}

void Texture::Release()
{
    if (m_Texture)
    {
        hge->Texture_Free(m_Texture);
        m_Texture = NULL;
    }
    if (m_Sprite_ptr)
    {
        delete m_Sprite_ptr;
        m_Sprite_ptr = NULL;
    }
    if (!m_vecFrameSprite.empty())
    {
        for (auto it = m_vecFrameSprite.begin();
            it != m_vecFrameSprite.end(); it++)
        {
            delete (*it);
        }
    }
}


DWORD* Texture::CheckColor(float x, float y, float cx, float cy)
{
    if (x < 0 || y < 0 || x + cx > m_TextureWidth || y + cy > m_TextureHeight)
    {
        return NULL;
    }
    DWORD* pClr;
    pClr = hge->Texture_Lock(m_Texture, true, x, y, cx, cy);
    hge->Texture_Unlock(m_Texture);
    return pClr;
}