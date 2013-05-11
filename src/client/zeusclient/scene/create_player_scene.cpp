#include "create_player_scene.h"

#define EditCtrl_EditPlayerName 100001
#define LISTCtrl_PROFESSIONLIST 200001

CreatePlayerScene::CreatePlayerScene()
{
    m_EditPlayerName = new EditBox(EditCtrl_EditPlayerName,
        100, 100, ARGB(255, 255, 0, 0), "ËÎÌו", 22);
    //m_ProfessionList = new hgeGUIListbox(LISTCtrl_PROFESSIONLIST,
    //    200.0f, 200.0f, 500.0f, 500.0f, );
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
    m_Gui.Update(hgeCreate(HGE_VERSION)->Timer_GetDelta());
}

void CreatePlayerScene::Output()
{
    m_Gui.Render();
}

void CreatePlayerScene::Reset()
{

}