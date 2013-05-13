#ifndef BUTTON_
#define BUTTON_

#include "game_object\gui\gui_item.h"
#include "engine\graphics_engine.h"
#include "control\control_object\font_object.h"
#include <string>

typedef void(*ButtonFun)();

class Button
    : public GUIItem
{
public:
    Button(int _Id, float w, float h,const std::string& strFont, ButtonFun dis);
    virtual ~Button();

public:

    void SetPos(float x, float y);
    void SetText(const std::string& strText);
    const std::string& GetText();

    virtual void    Render();
    virtual void    Update(float dt);

    virtual void    Enter();
    virtual void    Leave();
    virtual void    Reset();
    virtual void    Focus(bool bFocused);
    virtual void    MouseOver(bool bOver);

    virtual bool    MouseMove(float x, float y);
    virtual bool    MouseLButton(bool bDown);
    virtual bool    MouseRButton(bool bDown);
    virtual bool    KeyClick(int key, int chr);
private:
    float m_Border_x;
    float m_Border_y;
    float m_Border_w;
    float m_Border_h;
    float m_Button_w;
    float m_Button_h;
    float m_Button_x;
    float m_Button_y;
    std::string m_Text;
    GraphicsEngine* m_Graphics;
    ButtonFun m_DisButton;
    FontObject* m_Font;
};

#endif