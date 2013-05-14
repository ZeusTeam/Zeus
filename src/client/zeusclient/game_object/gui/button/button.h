#ifndef BUTTON_
#define BUTTON_

#include "game_object\gui\gui_item.h"
#include "engine\graphics_engine.h"
#include "control\control_object\font_object.h"
#include <string>

class Button
    : public GUIItem
{
public:
    Button(int _Id, float w, float h,const std::string& strFont);
    virtual ~Button();

public:

    void SetPos(float x, float y);
    void SetText(const std::string& strText);
    void SetBgLButton(const std::string& strId);
    void SetBgMove(const std::string& strId);
    void SetBg(const std::string& strId);

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
    TextureObject* m_bgButtonLB;
    TextureObject* m_bgButtonMove;
    TextureObject* m_bgButton;
    TextureObject* m_bgDarwButton;
    GraphicsEngine* m_Graphics;
    FontObject* m_Font;
};

#endif