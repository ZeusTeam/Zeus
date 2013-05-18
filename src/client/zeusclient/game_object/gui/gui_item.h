#ifndef GUI_ITEM_
#define GUI_ITEM_
#include "import\hge\include\hgegui.h"
#include "control\control_object\animation_object.h"
#include "control\control_object\texture_object.h"
#include "control\control_object\font_object.h"

class GUIItem
    : public hgeGUIObject
{
public:
    GUIItem()   {}
    virtual         ~GUIItem() {}

    virtual void    Render() = 0;
    virtual void    Update(float dt) {}

    virtual void    Enter() {}                                          //元素进入的绘制
    virtual void    Leave() {}                                          //元素离开的绘制
    virtual void    Reset() {}                                          //元素返回的默认状态并绘制
    virtual bool    IsDone() { return true; }                           //是否绘制完毕
    virtual void    Focus(bool bFocused) {}                             //焦点设置
    virtual void    MouseOver(bool bOver) {}                            //鼠标是否离开元素区域

    virtual bool    MouseMove(float x, float y) { return false; }
    virtual bool    MouseLButton(bool bDown) { return false; }
    virtual bool    MouseRButton(bool bDown) { return false; }
    virtual bool    MouseWheel(int nNotches) { return false; }
    virtual bool    KeyClick(int key, int chr) { return false; }

};

#endif