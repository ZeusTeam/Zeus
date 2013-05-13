#include "create_player_scene.h"
#include "control\pool\picture_pool.h"

#define EditCtrl_EditPlayerName 1
#define LISTCtrl_PROFESSIONLIST 2

void ButtonCreate()
{
    //::MessageBox(NULL, "其实我没有创建", 0, MB_OK);
}

CreatePlayerScene::CreatePlayerScene()
{
    m_InputEngine = InputEngine::Instance();
    m_PlayerImage = PicturePool::Instance()->Get("Play1");
    m_EditPlayerName = new EditBox(1, 200, 22, ARGB(255,255,0, 0),"宋体", 22);
    m_EditPlayerName->SetPos(0, 200 - 24);
    m_ButtonCreate = new Button(2, 110, 37, "宋体", ButtonCreate);
    m_ButtonCreate->SetPos(30, 200);
    m_ButtonCreate->SetBg("RoleSelect-CreateRole");
    m_ButtonCreate->SetBgMove("RoleSelect-CreateRole_Move");
    m_ButtonCreate->SetBgLButton("RoleSelect-CreateRole_LB");
    //m_ButtonCreate->SetText("创建人物");

    m_Gui.AddCtrl(m_EditPlayerName);
    m_Gui.AddCtrl(m_ButtonCreate);
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
    GraphicsEngine::Instance()->Clear(ARGB(1,0,0,0));
    m_Gui.Render();
}

void CreatePlayerScene::Reset()
{
    GraphicsEngine::Instance()->Clear(ARGB(1,0,0,0));
}