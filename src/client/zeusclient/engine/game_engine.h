#ifndef GAMEENGINE_
#define GAMEENGINE_

#include "import\hge\include\hge.h"
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

typedef enum _EngineAttributeString
{
    Attribute_Title,
    Attribute_LogPath,
}EngineAttributeString;

typedef HGE* GameEnginePtr;

typedef bool (*EngineCallbackFun) ();

class GameEngine
{
public:
    GameEngine();
    virtual ~GameEngine();

public:
    bool Initialize();

    bool State(EngineFunc funtype, EngineCallbackFun fun);

    bool State(EngineAttributeInt attrtype, int value);

    bool State(EngineAttributeString attrtype,const std::string& value);

    void Start();

    void Shutdown();

    GameEnginePtr PresentEngine();

public:
    bool Input_GetKeyState(int nKey);

private:
    GameEnginePtr m_hge;
};

#endif