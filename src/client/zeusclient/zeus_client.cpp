#include "globaldef.h"
#include "import\hge\include\hge.h"
#include "engine\game_engine.h"
#include "engine\texture_engine.h"
#include "engine\graphics_engine.h"
#include "control\game_controler.h"
#include "resource\xml_list.h"
#include "resource\cpicturexml_parse.h"
#include "resource\xml_list.h"
#include "control\control_object\font_object.h"

#include <tchar.h>
#include <Shlwapi.h>

#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib, "../../../import/hge/lib/hge.lib")
#pragma comment(lib, "../../../import/hge/lib/hgehelp.lib")

GameControler* game;

SceneEngine* SceneEngine_ = NULL;
InputEngine* InputEngine_ = NULL;
TextureEngine* TextureEngine_ = NULL;
GraphicsEngine* GraphicsEngine_ = NULL;

HWND g_hWnd = NULL;

bool Update()
{
    return game->Update();
}

bool Render()
{
    return game->Render();
}


void InitializeWindow(GameEngine* engine)
{
    engine->State(Func_Frame, Update);
    engine->State(Func_Render, Render);
    engine->State(Attribute_Width, WINDOW_WIDTH);
    engine->State(Attribute_Height, WINDOW_HEIGHT);
    engine->State(Attribute_Fps, 60);
    engine->State(Attribute_Title, _T("ZEUS"));
    engine->State(Attribute_LogPath, _T("RPGDemo.log"));
    engine->State(Attribute_HideCursor, false);
}

void InitializeEngine(GameEngine* engine)
{
    SceneEngine_ = SceneEngine::Instance();
    InputEngine_ = InputEngine::Instance();
    TextureEngine_ = TextureEngine::Instance();
    GraphicsEngine_ = GraphicsEngine::Instance();
    game = GameControler::Instance();
    InputEngine_->Initialize(engine);
    TextureEngine_->Initialize(engine);
    GraphicsEngine_->Initialize(engine);
    SceneEngine_->Initialize();
}

void InitializeResource()
{
    char filePath[MAX_PATH] = {0};
    ::GetModuleFileNameA(0, filePath, MAX_PATH);
    ::PathRemoveFileSpecA(filePath);
    ::PathAppendA(filePath, "res\\xml\\xmllist.xml");
    CXMLResource::Instance()->LoadXML(filePath);
    memset(filePath, 0, MAX_PATH);

    for (auto it = CXMLResource::Instance()->Begin();
        it != CXMLResource::Instance()->End(); it++)
    {
        ::GetModuleFileNameA(0, filePath, MAX_PATH);
        ::PathRemoveFileSpecA(filePath);
        ::PathAppendA(filePath, it->second->Path.c_str());
        if (it->first == "picture_stage1")
        {
            CPictureXMLParse::Instance()->LoadXML(filePath);
        }
    }
}

int WINAPI WinMain(          HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{
    GameEngine engine;
    InitializeWindow(&engine);
    InitializeEngine(&engine);
    InitializeResource();

    if (engine.Initialize())
    {
        g_hWnd = engine.GethWnd();
        game->Start();
        engine.Start();
    }
    else
    {
        MessageBox(NULL, "´´½¨´°¿ÚÊ§°Ü", NULL, MB_OK);
    }

    return 0;
}