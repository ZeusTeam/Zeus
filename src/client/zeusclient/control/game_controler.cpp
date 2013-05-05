#include "globaldef.h"
#include "game_controler.h"
#include "scene/menu_scene.h"
#include "engine\graphics_engine.h"

GameControler* Singleton<GameControler>::m_pInst = 0;

GameControler::GameControler()
{
}

GameControler::~GameControler()
{
}

void GameControler::Start()
{
   SceneEngine_->Push(new MenuScene);
}

bool GameControler::Update()
{
    return SceneEngine_->Update();
}

bool GameControler::Render()
{
    GraphicsEngine::Instance()->BeginScene();
    SceneEngine_->Output();
    GraphicsEngine::Instance()->EndScene();
    return true;
}

bool GameControler::Initialize()
{
    return true;
}