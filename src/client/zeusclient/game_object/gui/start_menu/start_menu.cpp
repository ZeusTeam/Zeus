#include "globaldef.h"
#include "start_menu.h"

StartMenu::StartMenu()
{
    ///没有资源Pool 暂时这样写
    m_gui.AddCtrl(new StartMenuItem(1, 75, 375, 
        new TextureObject("Res\\img\\menu_item\\menu_texture.png", 0, 0, 210, 58), 
        new TextureObject("Res\\img\\menu_item\\menu_texture.png", 210, 0, 215, 58)));

    m_gui.AddCtrl(new StartMenuItem(2, 75, 450, 
    new TextureObject("Res\\img\\menu_item\\menu_texture.png", 0, 115, 220, 55), 
    new TextureObject("Res\\img\\menu_item\\menu_texture.png", 225, 115, 225, 55)));

    m_gui.AddCtrl(new StartMenuItem(3, 80, 525, 
        new TextureObject("Res\\img\\menu_item\\menu_texture.png", 0, 55, 155, 55), 
        new TextureObject("Res\\img\\menu_item\\menu_texture.png", 155, 60, 160, 55)));


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