#include "globaldef.h"
#include "start_menu.h"

StartMenu::StartMenu()
{
    ///没有资源Pool 暂时这样写
    m_gui.AddCtrl(new StartMenuItem(1, 75, 400, 
        new TextureObject("Res\\img\\menu_item\\menu_texture.png", 0, 0, 210, 55), 
        new TextureObject("Res\\img\\menu_item\\menu_texture.png", 210, 0, 210, 55)));

    m_gui.AddCtrl(new StartMenuItem(2, 110, 475, 
        new TextureObject("Res\\img\\menu_item\\menu_texture.png", 0, 55, 155, 55), 
        new TextureObject("Res\\img\\menu_item\\menu_texture.png", 155, 55, 155, 55)));

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
    int id = m_gui.Update(hge->Timer_GetDelta());
    switch (id)
    {
    case 1:
        return StartMenu_Start;
    case 2:
        return StartMenu_Exit;
    default:
        break;
    }
    return StartMenu_None;
}