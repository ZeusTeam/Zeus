#include "globaldef.h"
#include "menu_scene.h"
#include "play_scene.h"
#include "engine\input_engine.h"

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
    if (InputEngine::Instance()->IsKey(KEY_ESCAPE) == Key_Down)
    {
        SceneEngine_->Pop();
    }
    if (InputEngine::Instance()->IsKey(KEY_ENTER) == Key_Down)
    {
        SceneEngine_->Pop();
        SceneEngine_->Push(new PlayScene);
    }
}