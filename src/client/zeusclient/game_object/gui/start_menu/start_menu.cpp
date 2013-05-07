#include "globaldef.h"
#include "start_menu.h"

StartMenu::StartMenu()
{
    m_gui.AddCtrl(new StartMenuItem(1, 60, 350, "开始游戏", NULL));

    m_gui.AddCtrl(new StartMenuItem(2, 60, 425, "神秘房间", NULL));

    m_gui.AddCtrl(new StartMenuItem(3, 60, 500, "退出", NULL));


    m_gui.SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
    m_gui.SetFocus(1);
    m_gui.Enter();
}

StartMenu::~StartMenu()
{
}

bool StartMenu::Render()
{
   m_gui.Render();
   return false;
}

StartMenuState StartMenu::Update()
{
    int id = m_gui.Update(hgeCreate(HGE_VERSION)->Timer_GetDelta());
    switch (id)
    {
    case 1:
        return StartMenu_Start;
    case 2:
        return StartMenu_About;
    case 3:
        return StartMenu_Exit;
    default:
        break;
    }
    return StartMenu_None;
}