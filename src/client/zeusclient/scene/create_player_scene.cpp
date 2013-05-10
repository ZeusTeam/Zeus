#include "create_player_scene.h"

#define EditCtrl_EditPlayerName 100001

CreatePlayerScene::CreatePlayerScene()
{
    m_EditPlayerName = new EditBox(EditCtrl_EditPlayerName,
        100, 100, ARGB(255, 255, 0, 0), "ËÎÌו", 22);
    m_EditPlayerName->SetPos(200.0f,300.0f);
    m_Gui.AddCtrl(m_EditPlayerName);
    m_Gui.SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
    m_Gui.Enter();
}

CreatePlayerScene::~CreatePlayerScene()
{

}

void CreatePlayerScene::Update()
{
    m_Gui.Update(1.0f);
}

void CreatePlayerScene::Output()
{
    m_Gui.Render();
}

void CreatePlayerScene::Reset()
{

}