#include "globaldef.h"
#include "role_select_scene.h"
#include "control\control_object\out_text.h"
#include "engine\graphics_engine.h"
#include "control\pool\picture_pool.h"

PlayScene::PlayScene()
{
    m_MapX = 0.0f;
    m_MapY = 0.0f;
    m_Map = new GameMap;
    m_Map->Load("map1", "mapcollision1");
    m_Map->PushCovering("res\\img\\covering1.png", 238.0f, 0.0f);
    m_Font = new FontObject("Î¢ÈíÑÅºÚ", 22);
    m_Font->SetColor(ARGB(255,255,0,0));
    m_ViewPosX = (int)m_Map->GetWidth() - 1;
    m_ViewPosX = ~m_ViewPosX;
    m_ViewPosY = (int)m_Map->GetHeight() - 1;
    m_ViewPosY = ~m_ViewPosY;
    m_PlayerRole = new PlayerRole(400, 300);
    m_Map->SetViewport(0, 0, 800, 600, m_PlayerRole->GetPos());

    m_Edit = new EditBox(1, WINDOW_WIDTH, 22, ARGB(255,255,0, 0),"Î¢ÈíÑÅºÚ", 22);
    m_Edit->SetPos(0, WINDOW_HEIGHT - 24);

    m_Gui.AddCtrl(m_Edit);
    m_Gui.SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
    m_Gui.SetFocus(1);
    m_Gui.Enter();
}


PlayScene::~PlayScene()
{
    delete m_Map;
    delete m_PlayerRole;
    delete m_Font;
}

void PlayScene::Reset()
{
    GraphicsEngine::Instance()->Clear(ARGB(1,0,0,0));
}

void PlayScene::Output()
{
    m_Map->Render(m_PlayerRole->GetPos());
    m_PlayerRole->SetViewport(m_Map->GetViewportPos());
    m_PlayerRole->Render();
    m_Map->RenderCovering();

    m_Font->Print(0, 0, "ÊÓÍ¼ x : %f", m_Map->GetViewportPos().x);
    m_Font->Print(0, 30, "ÊÓÍ¼ y : %f", m_Map->GetViewportPos().y);
    m_Font->Print(0, 60, "ÈËÎï x: %f", m_PlayerRole->GetPos().x);
    m_Font->Print(0, 90, "ÈËÎï y: %f", m_PlayerRole->GetPos().y);

    m_Gui.Render();
    //PrintText::Print(0, 0, Text_Left, "viewportPos.x : %f", m_Map->GetViewportPos().x);
    //PrintText::Print(0, 30, Text_Left, "viewportPos.y : %f", m_Map->GetViewportPos().y);
    //PrintText::Print(0, 60, Text_Left, "people x: %f", m_PlayerRole->GetPos().x);
    //PrintText::Print(0, 90, Text_Left, "people y: %f", m_PlayerRole->GetPos().y);
}

void PlayScene::Update()
{
    m_Gui.Update(hgeCreate(HGE_VERSION)->Timer_GetDelta());
    roleVector nextPos = m_PlayerRole->GetNextPos();
    if (!m_Map->isCollision(nextPos, m_PlayerRole->GetAreaRadins(), ARGB(255,255,255,255)))
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