#include "globaldef.h"
#include "create_player_scene.h"
#include "control\pool\picture_pool.h"
#include <atlbase.h>

#define EditCtrl_EditPlayerName 1
#define LISTCtrl_PROFESSIONLIST 2
#define Btn_Create 3
#define Btn_Return 4

void CreatePlayerScene::ButtonCreate()
{
    ::MessageBox(0, CW2A(m_EditPlayerName->GetText().c_str()), 0, MB_OK);
}

CreatePlayerScene::CreatePlayerScene()
{
    m_InputEngine = InputEngine::Instance();
    m_PlayerImage = PicturePool::Instance()->Get("Play1");
    m_PlayerImage->SetRenderRect(0, 0, 300, 350);
    m_StaticName = new FontObject("宋体", 22);

    m_EditPlayerName = new EditBox(1, 200, 22, ARGB(255,255,0, 0),"宋体", 22);
    m_ButtonCreate = new Button(Btn_Create, 110, 37, "宋体");
    m_ButtonReturn = new Button(Btn_Return, 110, 37, "宋体");

    m_EditPlayerName->SetPos(WINDOW_WIDTH - 140 - 220,
        WINDOW_HEIGHT - 115);
    m_ButtonCreate->SetPos(WINDOW_WIDTH - 140, WINDOW_HEIGHT - 120);
    m_ButtonReturn->SetPos(WINDOW_WIDTH - 140 - 220 - 220, WINDOW_HEIGHT - 120);

    m_ButtonReturn->SetBg("Btn_blue-Bg");
    m_ButtonReturn->SetBgMove("Btn_blue-Move");
    m_ButtonReturn->SetBgLButton("Btn_blue-LB");

    m_ButtonCreate->SetBg("Btn_blue-Bg");
    m_ButtonCreate->SetBgMove("Btn_blue-Move");
    m_ButtonCreate->SetBgLButton("Btn_blue-LB");
    //m_ButtonCreate->SetText("创建人物");

    m_Gui.AddCtrl(m_EditPlayerName);
    m_Gui.AddCtrl(m_ButtonCreate);
    m_Gui.AddCtrl(m_ButtonReturn);
    m_Gui.SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
    m_Gui.Enter();
}

CreatePlayerScene::~CreatePlayerScene()
{

}

void CreatePlayerScene::DisposeCtrl(int _Id)
{
    switch (_Id)
    {
    case Btn_Create:
        ButtonCreate();
    default:
        break;
    }
}

void CreatePlayerScene::Update()
{
    DisposeCtrl(m_Gui.Update(hgeCreate(HGE_VERSION)->Timer_GetDelta()));
}

void CreatePlayerScene::Output()
{
    GraphicsEngine::Instance()->Clear(ARGB(1,0,0,0));
    m_PlayerImage->Render(WINDOW_WIDTH / 2 - 100, 20);
    m_StaticName->Print(WINDOW_WIDTH - 140 - 220 - 100, WINDOW_HEIGHT - 115,
        "角色名：");
    m_Gui.Render();
}

void CreatePlayerScene::Reset()
{
    GraphicsEngine::Instance()->Clear(ARGB(1,0,0,0));
}