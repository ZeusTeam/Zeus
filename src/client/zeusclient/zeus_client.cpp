#include "globaldef.h"
#include "import\hge\include\hge.h"
#include "engine\game_engine.h"
#include "control\game_controler.h"

#include <tchar.h>

#pragma comment(lib, "../../../import/hge/lib/hge.lib")
#pragma comment(lib, "../../../import/hge/lib/hgehelp.lib")

HGE* hge = NULL;
GameControler* game;

SceneEngine* SceneEngine_ = NULL;
InputEngine* InputEngine_ = NULL;

bool Update()
{
    return game->Update();
}

bool Render()
{
    return game->Render();
}


int WINAPI WinMain(          HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{
    GameEngine engine;
    engine.State(Func_Frame, Update);
    engine.State(Func_Render, Render);
    engine.State(Attribute_Width, WINDOW_WIDTH);
    engine.State(Attribute_Height, WINDOW_HEIGHT);
    engine.State(Attribute_Fps, 60);
    engine.State(Attribute_Title, _T("RPG Demo"));
    engine.State(Attribute_LogPath, _T("RPGDemo.log"));

    SceneEngine_ = SceneEngine::Instance();
    InputEngine_ = InputEngine::Instance();
    InputEngine_->Initialize(&engine);
    SceneEngine_->Initialize();
    hge = engine.PresentEngine();

    if (engine.Initialize())
    {
        game = GameControler::Instance();
        game->Start();
        engine.Start();
    }
    else
    {
        MessageBox(NULL, "´´½¨´°¿ÚÊ§°Ü", NULL, MB_OK);
    }

    return 0;
}