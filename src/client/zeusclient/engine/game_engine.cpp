#include "game_engine.h"

GameEngine::GameEngine()
{
    m_hge = hgeCreate(HGE_VERSION);
    if (m_hge)
    {
        m_hge->System_SetState(HGE_SHOWSPLASH, false);
        m_hge->System_SetState(HGE_WINDOWED, true); 
    }
}


GameEngine::~GameEngine()
{
    Shutdown();
}

bool GameEngine::Initialize()
{
    if (!m_hge)
    {
        return false;
    }
    return m_hge->System_Initiate();
}

bool GameEngine::State(EngineFunc funtype, EngineCallbackFun fun)
{
    if (!m_hge)
    {
        return false;
    }
    switch (funtype)
    {
    case Func_Frame:
        m_hge->System_SetState(HGE_FRAMEFUNC, fun);
        break;
    case Func_Render:
        m_hge->System_SetState(HGE_RENDERFUNC, fun);
        break;
    default:
        break;
    }
    return true;
}

bool GameEngine::State(EngineAttributeInt attrtype, int value)
{
    if (!m_hge)
    {
        return false;
    }
    switch (attrtype)
    {
    case Attribute_Width:
        m_hge->System_SetState(HGE_SCREENWIDTH, value);
        break;
    case Attribute_Height:
        m_hge->System_SetState(HGE_SCREENHEIGHT, value);
        break;
    case Attribute_Fps:
        m_hge->System_SetState(HGE_FPS, value);
        break;
    default:
        break;
    }
    return true;
}

bool GameEngine::State(EngineAttributeString attrtype, tstring value)
{
    if (!m_hge)
    {
        return false;
    }
    switch (attrtype)
    {
    case Attribute_Title:
        m_hge->System_SetState(HGE_TITLE, value.c_str());
        break;
    case Attribute_LogPath:
        m_hge->System_SetState(HGE_LOGFILE, value.c_str());
        break;
    default:
        break;
    }
    return true;
}

void GameEngine::Start()
{
    if (m_hge)
    {
        m_hge->System_Start();
    }
}

void GameEngine::Shutdown()
{
    if (m_hge)
    {
        m_hge->System_Shutdown();
    }
}

HGE* GameEngine::PresentEngine()
{
    return m_hge;
}