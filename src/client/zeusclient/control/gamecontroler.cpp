#include "globaldef.h"
#include "gamecontroler.h"
#include "scene/menuscene.h"

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
    hge->Gfx_BeginScene();
    SceneEngine_->Output();
    hge->Gfx_EndScene();
    return true;
}

bool GameControler::Initialize()
{
    return true;
}