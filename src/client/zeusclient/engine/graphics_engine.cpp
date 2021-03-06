#include "graphics_engine.h"

template<> GraphicsEngine* Singleton<GraphicsEngine>::m_pInst = NULL;

GraphicsEngine::GraphicsEngine()
{
    m_GameEngine_Ptr = GameEngine::Instance();
    m_HDC = ::GetDC(m_GameEngine_Ptr->GethWnd());
}

GraphicsEngine::~GraphicsEngine()
{
    if (m_HDC)
    {
        ::ReleaseDC(
            m_GameEngine_Ptr->GethWnd(), m_HDC);
    }
}

void GraphicsEngine::SetClipping(int x, int y, int w, int h)
{
    if (!m_GameEngine_Ptr)
    {
        return;
    }
    m_GameEngine_Ptr->PresentEngine()->Gfx_SetClipping(x, y, w, h);
}

void GraphicsEngine::SetClipping()
{
    if (!m_GameEngine_Ptr)
    {
        return;
    }
    m_GameEngine_Ptr->PresentEngine()->Gfx_SetClipping();
}

HDC GraphicsEngine::WindowDC()
{
    return m_HDC;
}

void GraphicsEngine::BeginScene()
{
    if (!m_GameEngine_Ptr)
    {
        return;
    }
    m_GameEngine_Ptr->PresentEngine()->Gfx_BeginScene();
}

void GraphicsEngine::EndScene()
{
    if (!m_GameEngine_Ptr)
    {
        return;
    }
    m_GameEngine_Ptr->PresentEngine()->Gfx_EndScene();
}

void GraphicsEngine::Clear(DWORD color)
{
    if (!m_GameEngine_Ptr)
    {
        return;
    }
    m_GameEngine_Ptr->PresentEngine()->Gfx_Clear(color);
}

void GraphicsEngine::RenderLine(float x1, float y1,
        float x2, float y2,
        DWORD color,
        float z)
{
    if (!m_GameEngine_Ptr)
    {
        return;
    }
    m_GameEngine_Ptr->PresentEngine()->Gfx_RenderLine(
        x1, y1, x2, y2, color, z);
}

void GraphicsEngine::RenderQuad(const hgeQuad *quad)
{
    if (!m_GameEngine_Ptr)
    {
        return;
    }
    m_GameEngine_Ptr->PresentEngine()->Gfx_RenderQuad(quad);
}