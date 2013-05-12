#ifndef START_MENU_ITEM_
#define START_MENU_ITEM
#include "game_object\gui\gui_item.h"
#include "import\hge\include\hgefont.h"
#include "import\hge\include\hgesprite.h"
#include "import\hge\include\hgecolor.h"
#include "control\control_object\font_object.h"
#include "control\control_object\out_text.h"
#include "control\control_object\texture_object.h"
#include "include\utils\utils.h"
#include <string>


/*  以下是hgeGUIObject中的public成员
    int				id;
    bool			bStatic;
    bool			bVisible;
    bool			bEnabled;
    hgeRect			rect;
    DWORD			color;

    hgeGUI			*gui;
    hgeGUIObject	*next;
    hgeGUIObject	*prev;
*/

class StartMenuItem
    : public GUIItem
{
public:
    StartMenuItem(int _id, float x, float y
        , std::string title         ///显示在组件上的标题
        , TextureObject* texBg      ///组件的背景图
        );
    virtual         ~StartMenuItem();

    virtual void    Render();

    virtual void    Focus(bool bFocused);                             //焦点设置
    virtual bool    KeyClick(int key, int chr);

private:
    StartMenuItem() {}
    float m_x;
    float m_y;
    bool m_isFocused;
    std::string m_title;
    FontObject* m_font;
    TextureObject* m_texBg;
};


#endif