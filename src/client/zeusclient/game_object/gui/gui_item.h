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

    virtual void    Enter() {}                                          //Ԫ�ؽ���Ļ���
    virtual void    Leave() {}                                          //Ԫ���뿪�Ļ���
    virtual void    Reset() {}                                          //Ԫ�ط��ص�Ĭ��״̬������
    virtual bool    IsDone() { return true; }                           //�Ƿ�������
    virtual void    Focus(bool bFocused) {}                             //��������
    virtual void    MouseOver(bool bOver) {}                            //����Ƿ��뿪Ԫ������

    virtual bool    MouseMove(float x, float y) { return false; }
    virtual bool    MouseLButton(bool bDown) { return false; }
    virtual bool    MouseRButton(bool bDown) { return false; }
    virtual bool    MouseWheel(int nNotches) { return false; }
    virtual bool    KeyClick(int key, int chr) { return false; }

};

#endif