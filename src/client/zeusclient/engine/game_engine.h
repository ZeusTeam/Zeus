#ifndef GAMEENGINE_
#define GAMEENGINE_

#include "import\hge\include\hge.h"
#include "include\utils\singleton.h"
#include <string>

#ifndef UNICODE
#define tstring std::string
#else
#define tstring std::wstring
#endif

typedef enum _EngineFunc
{
    Func_Frame,
    Func_Render,
}EngineFunc;

typedef enum _EngineAttributeInt
{
    Attribute_Width,
    Attribute_Height,
    Attribute_Fps,
}EngineAttributeInt;

typedef enum _EngineAttributeBool
{
    Attribute_HideCursor,
}EngineAttributeBool;

typedef enum _EngineAttributeString
{
    Attribute_Title,
    Attribute_LogPath,
}EngineAttributeString;

typedef HGE* GameEnginePtr;
typedef HEFFECT GameTexture;
typedef bool (*EngineCallbackFun) ();

class GameEngine
    : public Singleton<GameEngine>
{
    friend class Singleton<GameEngine>;
public:
    GameEngine();
    virtual ~GameEngine();

public:
    virtual bool Initialize();

    bool State(EngineFunc funtype, EngineCallbackFun fun);

    bool State(EngineAttributeInt attrtype, int value);

    bool State(EngineAttributeBool attrtype, bool value);

    bool State(EngineAttributeString attrtype,const std::string& value);

    void Start();

    void Shutdown();

    GameEnginePtr PresentEngine();

    HWND GethWnd();

public:
    bool Input_GetKeyState(int nKey);

public:
    GameTexture Texture_Load(const std::string& path);

    void Texture_Free(GameTexture tex);

    DWORD* Texture_Lock(GameTexture tex,
                      bool bReadOnly = true,
                      int left = 0,
                      int top = 0,
                      int width = 0,
                      int height = 0);

    void Texture_UnLock(GameTexture tex);

    int Texture_GetWidth(GameTexture tex);

    int Texture_GetHeight(GameTexture tex);

private:
    GameEnginePtr m_hge;
    HWND m_hWnd;
};

#endif