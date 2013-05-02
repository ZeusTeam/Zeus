#include "globaldef.h"
#include "menu_scene.h"
#include "play_scene.h"

MenuScene::MenuScene()
{
    m_bgRenderer.Load("res\\img\\menubg.png");
}

MenuScene::~MenuScene()
{
}

void MenuScene::Reset()
{
}

void MenuScene::Output()
{
    m_bgRenderer.Render(0,0);
}

void MenuScene::Update()
{
    if (hge->Input_GetKeyState(KEY_ESCAPE))
    {
        SceneEngine_->Pop();
    }
    if (hge->Input_GetKeyState(KEY_ENTER))
    {
        SceneEngine_->Pop();
        SceneEngine_->Push(new PlayScene);
    }
}