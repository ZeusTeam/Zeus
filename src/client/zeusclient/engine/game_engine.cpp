#include "game_engine.h"

template<> GameEngine* Singleton<GameEngine>::m_pInst = NULL;

GameEngine::GameEngine()
{
    m_hWnd = NULL;
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

HWND GameEngine::GethWnd()
{
    if (!m_hge)
    {
        return 0;
    }
    return m_hge->System_GetState(HGE_HWND);
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

bool GameEngine::State(EngineAttributeString attrtype, const std::string& value)
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

bool GameEngine::State(EngineAttributeBool attrtype, bool value)
{
    if (!m_hge)
    {
        return false;
    }
    switch (attrtype)
    {
    case Attribute_HideCursor:
        m_hge->System_SetState(HGE_HIDEMOUSE, value);
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

///> Input
bool GameEngine::Input_GetKeyState(int nKey)
{
    return m_hge->Input_GetKeyState(nKey);
}

///> Texture
GameTexture GameEngine::Texture_Load(const std::string& path)
{
    if (!m_hge)
    {
        return 0;
    }
    return (GameTexture)m_hge->Texture_Load(path.c_str());
}

void GameEngine::Texture_Free(GameTexture tex)
{
    if (!m_hge)
    {
        return;
    }
    m_hge->Texture_Free((HEFFECT)tex);
}

DWORD* GameEngine::Texture_Lock(GameTexture tex,
                      bool bReadOnly,
                      int left,
                      int top,
                      int width,
                      int height)
{
    if (!m_hge)
    {
        return 0;
    }
    return m_hge->Texture_Lock((HEFFECT)tex, bReadOnly,
        left, top, width, height);
}

void GameEngine::Texture_UnLock(GameTexture tex)
{
    if (!m_hge)
    {
        return;
    }
    return m_hge->Texture_Unlock((HEFFECT)tex);
}

int GameEngine::Texture_GetWidth(GameTexture tex)
{
    if (!m_hge)
    {
        return 0;
    }
    return m_hge->Texture_GetWidth((HEFFECT)tex);
}

int GameEngine::Texture_GetHeight(GameTexture tex)
{
    if (!m_hge)
    {
        return 0;
    }
    return m_hge->Texture_GetHeight((HEFFECT)tex);
}