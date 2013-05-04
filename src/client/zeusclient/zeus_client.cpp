#include "globaldef.h"
#include "import\hge\include\hge.h"
#include "engine\game_engine.h"
#include "engine\texture_engine.h"
#include "engine\graphics_engine.h"
#include "control\game_controler.h"

#include <tchar.h>

#pragma comment(lib, "../../../import/hge/lib/hge.lib")
#pragma comment(lib, "../../../import/hge/lib/hgehelp.lib")

GameControler* game;

SceneEngine* SceneEngine_ = NULL;
InputEngine* InputEngine_ = NULL;
TextureEngine* TextureEngine_ = NULL;
GraphicsEngine* GraphicsEngine_ = NULL;

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
    TextureEngine_ = TextureEngine::Instance();
    GraphicsEngine_ = GraphicsEngine::Instance();
    InputEngine_->Initialize(&engine);
    TextureEngine_->Initialize(&engine);
    GraphicsEngine_->Initialize(&engine);

    SceneEngine_->Initialize();

    if (engine.Initialize())
    {
        game = GameControler::Instance();
        game->Start();
        engine.Start();
    }
    else
    {
        MessageBox(NULL, "��������ʧ��", NULL, MB_OK);
    }

    return 0;
}