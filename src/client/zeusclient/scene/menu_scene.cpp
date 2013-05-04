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
    m_startMenu.Render();
}

void MenuScene::Update()
{
    StartMenuState state = m_startMenu.Update();
    if (state == StartMenu_Exit)
    {
        SceneEngine_->Pop();
    }
    else if (state == StartMenu_Start)
    {
        SceneEngine_->Pop();
        SceneEngine_->Push(new PlayScene);
    }
    esle if (state == StartMenu_About)
    {

    }
}