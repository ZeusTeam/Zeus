#include "globaldef.h"
#include "playscene.h"
#include "control\controlobject\out_text.h"

PlayScene::PlayScene()
{
    m_MapX = 0.0f;
    m_MapY = 0.0f;
    m_Map = new GameMap;
    m_Map->Load("res\\img\\map1.png",
        "res\\img\\mapcollision1.png");
    m_ViewPosX = (int)m_Map->GetWidth() - 1;
    m_ViewPosX = ~m_ViewPosX;
    m_ViewPosY = (int)m_Map->GetHeight() - 1;
    m_ViewPosY = ~m_ViewPosY;
    m_PlayerRole = new PlayerRole(400, 300);
    m_Map->SetViewport(0, 0, 800, 600, m_PlayerRole->GetPos());
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
    m_Map->Render(m_PlayerRole->GetPos());
    float a = m_PlayerRole->GetPos().x + 1;
    PrintText::Print(0, 60, Text_Left, "people x: %f", a);
    PrintText::Print(0, 90, Text_Left, "people y: %f", 10.0f);
    m_PlayerRole->SetViewport(m_Map->GetViewportPos());
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

void PlayScene::_RollMap(roleVector& nextPos)
{
    if (m_PlayerRole->IsRollBorder() == Border_Bottom)
    {
        if ((m_MapY > 0) || (m_MapY > m_ViewPosY + WINDOW_HEIGHT))
        {
            m_MapY--;
            nextPos.y--;
            m_PlayerRole->MoveTo(nextPos);
        }
    }
    if (m_PlayerRole->IsRollBorder() == Border_Top)
    {
        if (m_MapY < 0)
        {
            m_MapY++;
            nextPos.y++;
            m_PlayerRole->MoveTo(nextPos);
        }
    }
    if (m_PlayerRole->IsRollBorder() == Border_Left)
    {
        if (m_MapY < 0 && m_MapX < 0)
        {
            m_MapX++;
            nextPos.x++;
            m_PlayerRole->MoveTo(nextPos);
        }
    }
    if (m_PlayerRole->IsRollBorder() == Border_Right)
    {
        if ((m_MapX > 0) || (m_MapX > m_ViewPosX + WINDOW_WIDTH))
        {
            m_MapX--;
            nextPos.x--;
            m_PlayerRole->MoveTo(nextPos);
        }
    }
}