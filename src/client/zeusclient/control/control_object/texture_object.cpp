#include "globaldef.h"
#include "texture_object.h"

TextureObject::TextureObject()
    : m_hTex(NULL)
    , m_texHeight(0)
    , m_texWidth(0)
    , m_tx(0)
    , m_ty(0)
    , m_renderWidth(0)
    , m_renderHeight(0)
    , m_TexEngine(NULL)
{
    m_TexEngine = TextureEngine::Instance();
    m_GraphicsEngine = GraphicsEngine::Instance();
}

TextureObject::~TextureObject()
{
    if (m_hTex)
    {
        if (m_TexEngine)
        {
            m_TexEngine->Release(m_hTex);
            m_hTex = NULL;
        }
    }

}

bool TextureObject::Load(const std::string& strPath)
{
    //��ʱ���������POOL֮���ٽ����滻
    if (!m_TexEngine)
    {
        return false;
    }
    m_hTex = m_TexEngine->Load(strPath);
    if (!m_hTex)
    {
        return false;
    }
    m_texWidth = (float)m_TexEngine->GetWidth(m_hTex);
    m_texHeight = (float)m_TexEngine->GetHeight(m_hTex);
    m_tx = 0;
    m_ty = 0;
    m_renderWidth = m_texWidth;
    m_renderHeight = m_texHeight;
    return true;
}


void TextureObject::Render(float x, float y)
{
    hgeQuad quad = { 0 };

    quad.blend = BLEND_DEFAULT;
    quad.tex = m_hTex;
    for (int i = 0; i < 4; i++)
    {
        quad.v[i].col = 0xFFFFFFFF;
    }

    if (m_renderWidth == 0)
    {
        m_renderWidth = m_texWidth;
    }
    if (m_renderHeight == 0)
    {
        m_renderHeight = m_texHeight;
    }
    quad.v[0].tx = m_tx / m_texWidth;
    quad.v[0].ty = m_ty / m_texHeight;

    quad.v[1].tx = quad.v[0].tx + m_renderWidth / m_texWidth;
    quad.v[1].ty = quad.v[0].ty;

    quad.v[2].tx = quad.v[0].tx + m_renderWidth / m_texWidth;
    quad.v[2].ty = quad.v[0].ty + m_renderHeight / m_texHeight;

    quad.v[3].tx = quad.v[0].tx;
    quad.v[3].ty = quad.v[0].ty + m_renderHeight / m_texHeight;

    quad.v[0].x = x;
    quad.v[0].y = y;

    quad.v[1].x = x + m_renderWidth;
    quad.v[1].y = y;

    quad.v[2].x = x + m_renderWidth;
    quad.v[2].y = y + m_renderHeight;

    quad.v[3].x = x;
    quad.v[3].y = y + m_renderHeight;

    m_GraphicsEngine->RenderQuad(&quad);
}

void TextureObject::SetRenderRect(float tx, float ty, float width, float height)
{
    m_tx = tx;
    m_ty = ty;
    m_renderWidth = width;
    m_renderHeight = height;
}

void TextureObject::Release()
{
    if (m_hTex)
    {
        if (m_TexEngine)
        {
            m_TexEngine->Release(m_hTex);
            m_hTex = NULL;
        }
    }
}


DWORD* TextureObject::CheckColor(float x, float y, int cx, int cy)
{
    if (!m_TexEngine)
    {
        return false;
    }
    if (x < 0 || y < 0 || x + cx > m_texWidth || y + cy > m_texHeight)
    {
        return NULL;
    }
    DWORD* pClr;
    pClr = m_TexEngine->Lock(m_hTex, true, (int)x, (int)y, cx, cy);
    m_TexEngine->Unlock(m_hTex);
    return pClr;
}