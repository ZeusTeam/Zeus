#ifndef START_MENU_ITEM_
#define START_MENU_ITEM
#include "game_object\gui\gui_item.h"
#include "import\hge\include\hgefont.h"
#include "import\hge\include\hgesprite.h"
#include "import\hge\include\hgecolor.h"
#include "control\control_object\out_text.h"
#include "control\control_object\texture_object.h"
#include <string>


/*  ������hgeGUIObject�е�public��Ա
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
    StartMenuItem(int _id, float x, float y, TextureObject* texUsual, TextureObject* texFocused);
    virtual         ~StartMenuItem();

    virtual void    Render();

    virtual void    Focus(bool bFocused);                             //��������
    virtual bool    KeyClick(int key, int chr);

private:
    StartMenuItem() {}
    float m_x;
    float m_y;
    bool m_isFocused;
    TextureObject* m_texUsual;
    TextureObject* m_texFocused;
};


#endif