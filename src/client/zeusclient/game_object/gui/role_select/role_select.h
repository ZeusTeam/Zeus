#ifndef ROLE_SELECT_
#define ROLE_SELECT_
#include "role_select_item.h"
#include "control\pool\picture_pool.h"
#include "import\hge\include\hgegui.h"
enum RoleSelectState
{
    RoleSelect_EnterGame,
    RoleSelect_CreateRole,
    RoleSelect_Return,
    RoleSelect_None
};
class RoleSelect
{
public:
    RoleSelect();
    ~RoleSelect();

    int GetSelectedRoleID();
    RoleSelectState Update();
    bool Render();

private:
    hgeGUI m_gui;
    TextureObject* m_bgTex;
    hgeSprite* m_cursorMouse;
};

#endif