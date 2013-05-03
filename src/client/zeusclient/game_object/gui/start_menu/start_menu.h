#ifndef START_MENU_
#define START_MENU_
#include "start_menu_item.h"
#include "import\hge\include\hgegui.h"

enum StartMenuState
{
    StartMenu_Start,
    StartMenu_Exit,
    StartMenu_None
};
class StartMenu
{
public:
    StartMenu();
    ~StartMenu();

    StartMenuState Update();

    bool Render();

private:
    hgeGUI m_gui;
};

#endif