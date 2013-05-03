#include "graphics_engine.h"

template<> GraphicsEngine* Singleton<GraphicsEngine>::m_pInst = NULL;

GraphicsEngine::GraphicsEngine()
{
    m_GameEngine_Ptr = NULL;
}

GraphicsEngine::~GraphicsEngine()
{
}

bool GraphicsEngine::Initialize(GameEngine* pGameEngine)
{
    if (!pGameEngine)
    {
        return false;
    }
    m_GameEngine_Ptr = pGameEngine;
    return true;
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