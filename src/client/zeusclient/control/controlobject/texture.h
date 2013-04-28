#ifndef TEXTURE_
#define TEXTURE_

#include "import\hge\include\hge.h"
#include "import\hge\include\hgesprite.h"
#include <string>
#include <vector>

class Texture
{
public:
    Texture();
    virtual ~Texture();

    virtual bool Load(const std::string& strPath,
        float x, float y);

    virtual bool LoadFrame(const std::string& strPath,
        float y, float width, float height);

    virtual void Render(float x, float y, float tx, float ty , float width = 0, float height = 0);

    virtual void RenderFrame(int nFramePos, float x, float y);

    float GetX() const { return m_TextureX; }

    float GetY() const { return m_TextureY; }

    float GetWidth() const { return m_TextureWidth; }

    float GetHeight() const { return m_TextureHeight; }

    void Render(float x, float y);

    DWORD* CheckColor(float x, float y, int cx, int cy);


    virtual void Release();

private:
    float m_TextureX;
    float m_TextureY;
    float m_TextureWidth;
    float m_TextureHeight;
    int m_nFrame;
    HTEXTURE m_Texture;
    hgeSprite* m_Sprite_ptr;
    std::vector<hgeSprite*> m_vecFrameSprite;
};

#endif