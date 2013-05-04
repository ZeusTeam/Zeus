#ifndef TEXTURE_
#define TEXTURE_

#include "import\hge\include\hge.h"
#include "engine\texture_engine.h"
#include "engine\graphics_engine.h"

#include <string>

class TextureObject
{
public:
    TextureObject();
    TextureObject(const std::string& strPath, float tx = 0.0f, float ty = 0.0f, float width = 0.0f, float height = 0.0f);

    virtual ~TextureObject();

    bool Load(const std::string& strPath, float tx = 0.0f, float ty = 0.0f, float width = 0.0f, float height = 0.0f);

    float GetWidth() const { return m_texWidth; }

    float GetHeight() const { return m_texHeight; }

    DWORD* CheckColor(float x, float y, int cx, int cy);

    void SetRenderRect(float tx, float ty, float width, float height);

    virtual void Render(float x, float y);

    virtual void Release();

    GameTexture& GetObject() { return m_hTex; }

private:
    float m_texHeight;      //����ĸ߶�
    float m_texWidth;       //����Ŀ��
    float m_renderWidth;    //����ʱ����������
    float m_renderHeight;   //����ʱ����������
    float m_tx;             //����ʱ��������������
    float m_ty;
    GameTexture m_hTex;
    TextureEngine* m_TexEngine;
    GraphicsEngine* m_GraphicsEngine;
};

#endif