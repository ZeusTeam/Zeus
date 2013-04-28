#include "globaldef.h"
#include "playscene.h"

PlayScene::PlayScene()
{
    m_Map = new GameMap;
    m_Map->Load("res\\img\\map.png",
        "res\\img\\mapcollision.png");

    m_PlayerRole = new PlayerRole(400, 300);
}

PlayScene::~PlayScene()
{
    delete m_Map;
    delete m_PlayerRole;
}

void PlayScene::Reset()
{
    hge->Gfx_Clear(ARGB(1,0,0,0));
}

void PlayScene::Output()
{
    m_Map->Render();
    m_PlayerRole->Render();
}

void PlayScene::Update()
{
    roleVector nextPos = m_PlayerRole->GetNextPos();
    if (!m_Map->isCollision(nextPos, m_PlayerRole->GetAreaRadins(), ARGB(255,255,255,255))) ///不碰撞白色 可移动
    {
        m_PlayerRole->MoveTo(nextPos);
    }
    else
    {
        m_PlayerRole->Stop();
    }
    m_PlayerRole->Update();
}