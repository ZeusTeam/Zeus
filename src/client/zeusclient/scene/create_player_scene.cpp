#include "globaldef.h"
#include "create_player_scene.h"
#include "control\pool\picture_pool.h"
#include "scene\role_select_scene.h"
#include <atlbase.h>

#define EditCtrl_EditPlayerName 1
#define LISTCtrl_PROFESSIONLIST 2
#define Btn_Create 3
#define Btn_Return 4
#define Static_Play_Message 5
#define Static_Play_Name 6

void CreatePlayerScene::ButtonCreate()
{
    m_PlayMessage->SetText((LPCTSTR)CW2A(m_EditPlayerName->GetText().c_str()));
}

void CreatePlayerScene::ButtonReturn()
{
    SceneEngine_->Pop();
    SceneEngine_->Push(new RoleSelectScene);
}

CreatePlayerScene::CreatePlayerScene()
{
    m_InputEngine = InputEngine::Instance();
    m_PlayerImage = PicturePool::Instance()->Get("Play1");
    m_PlayerImage->SetRenderRect(0, 0, 300, 350);
    m_PlayMessage = new StaticBox(Static_Play_Message, ARGB(255, 255, 0, 0),"宋体", 38);
    m_PlayName = new StaticBox(Static_Play_Name, ARGB(255, 255, 255, 255),"宋体", 22);

    m_EditPlayerName = new EditBox(EditCtrl_EditPlayerName,
        200, 38, ARGB(255, 255, 0, 0),"宋体", 38);
    m_ButtonCreate = new Button(Btn_Create, 114, 38, "宋体");
    m_ButtonReturn = new Button(Btn_Return, 114, 38, "宋体");

    m_PlayMessage->SetPos(WINDOW_WIDTH / 2,
        WINDOW_HEIGHT - 200);
    m_PlayMessage->SetText("~啦啦啦");
    m_PlayMessage->SetBackground(ARGB(255, 255, 255, 255));

    m_PlayName->SetPos(WINDOW_WIDTH - 140 - 220 - 100, WINDOW_HEIGHT - 115);
    m_PlayName->SetText("角色名：");

    m_EditPlayerName->SetPos(WINDOW_WIDTH - 140 - 220,
        WINDOW_HEIGHT - 120);
    m_ButtonCreate->SetPos(WINDOW_WIDTH - 140, WINDOW_HEIGHT - 120);
    m_ButtonReturn->SetPos(WINDOW_WIDTH - 140 - 220 - 220, WINDOW_HEIGHT - 120);

    m_ButtonReturn->SetBg("Btn_blue-Bg");
    m_ButtonReturn->SetBgMove("Btn_blue-Move");
    m_ButtonReturn->SetBgLButton("Btn_blue-LB");
    m_ButtonReturn->SetText("返回菜单");

    m_ButtonCreate->SetBg("Btn_blue-Bg");
    m_ButtonCreate->SetBgMove("Btn_blue-Move");
    m_ButtonCreate->SetBgLButton("Btn_blue-LB");
    m_ButtonCreate->SetText("创建人物");

    m_Gui.AddCtrl(m_EditPlayerName);
    m_Gui.AddCtrl(m_ButtonCreate);
    m_Gui.AddCtrl(m_ButtonReturn);
    m_Gui.AddCtrl(m_PlayMessage);
    m_Gui.AddCtrl(m_PlayName);
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
        break;
    case Btn_Return:
        ButtonReturn();
        break;
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
    GraphicsEngine::Instance()->Clear(ARGB(255,46,24,32));
    m_PlayerImage->Render(WINDOW_WIDTH / 2 - 100, 20);
    m_Gui.Render();
}

void CreatePlayerScene::Reset()
{
    GraphicsEngine::Instance()->Clear(ARGB(255,46,24,32));
}