#include "role_select_scene.h"
#include "play_scene.h"
#include "menu_scene.h"
#include "create_player_scene.h"
#include "control\pool\picture_pool.h"

#define SelectView_Role 1
#define ImageBox_Role1 2
#define ImageBox_Role2 3
#define ImageBox_Role3 4
#define Button_Return 5
#define Button_CreateRole 6
#define Button_DeleteRole 7
#define Button_StartGame 8

RoleSelectScene::RoleSelectScene()
{
    m_roleBox1 = new ImageBox(ImageBox_Role1, 35, 60, "RoleSelect-Role");
    m_roleBox2 = new ImageBox(ImageBox_Role2, 290, 60, "RoleSelect-Role");
    m_roleBox3 = new ImageBox(ImageBox_Role3, 544, 60, "RoleSelect-Role");

    m_selectView = new SelectView(SelectView_Role, 10, 60, 780, 410);
    m_selectView->SetHorInterval(30);
    m_selectView->SetItemWidth(224);
    m_selectView->SetItemHeight(297);
    m_selectView->AddItem("RoleSelect-RoleBox", "RoleSelect-RoleBoxFocus");
    m_selectView->AddItem("RoleSelect-RoleBox", "RoleSelect-RoleBoxFocus");
    m_selectView->AddItem("RoleSelect-RoleBox", "RoleSelect-RoleBoxFocus");
    m_selectView->SetCurrentItem(0);

    m_returnBtn = new Button(Button_Return, 114, 38, "微软雅黑");
    m_returnBtn->SetBg("Btn_blue-Bg");
    m_returnBtn->SetBgMove("Btn_blue-Move");
    m_returnBtn->SetBgLButton("Btn_blue-LB");
    m_returnBtn->SetText("返回");
    m_returnBtn->SetPos(36, 468);


    m_createRoleBtn = new Button(Button_CreateRole, 114, 38, "微软雅黑");
    m_createRoleBtn->SetBg("Btn_blue-Bg");
    m_createRoleBtn->SetBgMove("Btn_blue-Move");
    m_createRoleBtn->SetBgLButton("Btn_blue-LB");
    m_createRoleBtn->SetText("创建角色");
    m_createRoleBtn->SetPos(159, 468);

    m_deleteRoleBtn = new Button(Button_DeleteRole, 114, 38, "微软雅黑");
    m_deleteRoleBtn->SetBg("Btn_blue-Bg");
    m_deleteRoleBtn->SetBgMove("Btn_blue-Move");
    m_deleteRoleBtn->SetBgLButton("Btn_blue-LB");
    m_deleteRoleBtn->SetText("删除角色");
    m_deleteRoleBtn->SetPos(283, 468);
    
    m_startGameBtn = new Button(Button_StartGame, 114, 38, "微软雅黑");
    m_startGameBtn->SetBg("Btn_blue-Bg");
    m_startGameBtn->SetBgMove("Btn_blue-Move");
    m_startGameBtn->SetBgLButton("Btn_blue-LB");
    m_startGameBtn->SetText("开始游戏");
    m_startGameBtn->SetPos(606, 468);

    m_gui.AddCtrl(m_roleBox1);
    m_gui.AddCtrl(m_roleBox2);
    m_gui.AddCtrl(m_roleBox3);
    m_gui.AddCtrl(m_selectView);
    m_gui.AddCtrl(m_returnBtn);
    m_gui.AddCtrl(m_createRoleBtn);
    m_gui.AddCtrl(m_deleteRoleBtn);
    m_gui.AddCtrl(m_startGameBtn);
    m_gui.SetFocus(SelectView_Role);
    m_gui.Enter();
}

RoleSelectScene::~RoleSelectScene()
{

}

void RoleSelectScene::OnReturnBtnClick()
{
}
void RoleSelectScene::OnCreateRoleBtnClick()
{
    
}
void RoleSelectScene::OnDeleteRoleBtnClick()
{
    //这个暂时没有实现 先不写
}
void RoleSelectScene::OnStartGameBtnClick()
{

}

void RoleSelectScene::Update()
{
    //按钮被单击了会返回他的id
    switch (m_gui.Update(hgeCreate(HGE_VERSION)->Timer_GetDelta()))
    {

    }
}
void RoleSelectScene::Output()
{
    //白色底图
    GraphicsEngine::Instance()->Clear(ARGB(255,255,255,255));
    m_gui.Render();
}
void RoleSelectScene::Reset()
{
    GraphicsEngine::Instance()->Clear(ARGB(1,0,0,0));
}