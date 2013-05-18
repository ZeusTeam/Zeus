#include "role_select_scene.h"
#include "play_scene.h"
#include "menu_scene.h"
#include "create_player_scene.h"

RoleSelectScene::RoleSelectScene()
{

}

RoleSelectScene::~RoleSelectScene()
{

}

void RoleSelectScene::Update()
{
    switch (m_roleSelectGUI.Update())
    {
    case RoleSelect_EnterGame:
        SceneEngine_->Pop();
        SceneEngine_->Push(new PlayScene);
        break;
    case RoleSelect_Return:
        SceneEngine_->Pop();
        SceneEngine_->Push(new MenuScene);
        break;
    case RoleSelect_CreateRole:
        SceneEngine_->Pop();
        SceneEngine_->Push(new CreatePlayerScene);
        break;
    case RoleSelect_None:
        break;
    }
}
void RoleSelectScene::Output()
{
    m_roleSelectGUI.Render();
}
void RoleSelectScene::Reset()
{
    GraphicsEngine::Instance()->Clear(ARGB(1,0,0,0));
}