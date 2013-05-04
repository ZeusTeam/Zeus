#include "globaldef.h"
#include "menu_scene.h"
#include "play_scene.h"
#include "engine\input_engine.h"
#include "control\pool\picture_pool.h"

MenuScene::MenuScene()
{
    m_bgRenderer = PicturePool::Instance()->Get("menubg");
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
    if (!m_bgRenderer)
    {
        return;
    }
    m_bgRenderer->Render(0,0);
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