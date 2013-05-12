#ifndef ROLE_SELECT_ITEM_
#define ROLE_SELECT_ITEM_
#include "game_object\gui\gui_item.h"
#include "import\hge\include\hgesprite.h"
#include <string>

class RoleSelectItem
    : public GUIItem
{
public:
    RoleSelectItem(int _id, bool _bStatic, float x, float y, const std::string roleName, 
        TextureObject* normalTex, TextureObject* focusTex, 
        AnimationObject* enterAnimation, AnimationObject* leaveAnimation);
    virtual void    Render();
    virtual void    Update(float dt);
    virtual void    Enter();
    virtual void    Leave();
    virtual bool    IsDone();
    virtual void    Focus(bool bFocused);
    virtual bool    KeyClick(int key, int chr);
    virtual bool    MouseLButton(bool bDown);
    ~RoleSelectItem();

private:
    RoleSelectItem() {}
    bool m_focused;
    bool m_isDoneEnter;
    bool m_isDoneLeave;
    float m_x;
    float m_y;
    TextureObject* m_focusTex;
    TextureObject* m_normalTex;
    AnimationObject* m_enterAnimation;
    AnimationObject* m_leaveAnimation;
    std::string m_roleName;

};
#endif