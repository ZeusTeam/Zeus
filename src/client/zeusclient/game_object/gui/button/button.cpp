#include "button.h"

Button::Button(int _Id, float w, float h,
               const std::string& strFont, ButtonFun dis)
{
    this->id = _Id;
    this->bStatic = false;
    this->bVisible = true;
    this->bEnabled = true;

    m_Button_x = 0.0f;
    m_Button_y = 0.0f;
    m_Button_w = w;
    m_Button_h = h;
    m_Border_w = w + 1;
    m_Border_h = h + 1;
    m_Border_x = 0.0f;
    m_Border_y = 0.0f;
    m_DisButton = dis;
    m_Graphics = GraphicsEngine::Instance();
    m_Font = new FontObject(strFont, 22);
}

Button::~Button()
{

}

void Button::SetPos(float x, float y)
{
    m_Border_x = x - 1;
    m_Border_y = y - 1;
    m_Button_x = x;
    m_Button_y = y;
}

void Button::SetText(const std::string& strText)
{
    m_Text = strText;
}

const std::string& Button::GetText()
{
    return m_Text;
}

void Button::Render()
{
    //»æÖÆ±ß¿ò
    if (m_Graphics)
    {
        m_Graphics->RenderLine(m_Border_x, m_Border_y,
            m_Border_x + m_Border_w, m_Border_y);
        m_Graphics->RenderLine(m_Border_x, m_Border_y,
            m_Border_x, m_Border_y + m_Border_h);
        m_Graphics->RenderLine(m_Border_x + m_Border_w, m_Border_y + m_Border_h,
            m_Border_x + m_Border_w, m_Border_y);
        m_Graphics->RenderLine(m_Border_x + m_Border_w, m_Border_y + m_Border_h,
            m_Border_x, m_Border_y + m_Border_h);
    }
    if (m_Font)
    {
        m_Font->Print(
            m_Button_x + (m_Button_w / 2) - (int)((float)m_Font->TextKerningWidth(m_Text.c_str()) / 1.5),
            m_Button_y + (m_Button_h / 2) - (m_Font->GetFontSize() / 2), m_Text.c_str());
    }
}

void Button::Update(float dt)
{
    this->rect.x1 = m_Button_x;
    this->rect.y1 = m_Button_y;
    this->rect.x2 = m_Button_x + m_Button_w;
    this->rect.y2 = m_Button_y + m_Button_h;
}

void Button::Enter()
{
}

void Button::Leave()
{
}

void Button::Reset()
{
}

void Button::Focus(bool bFocused)
{
}

void Button::MouseOver(bool bOver)
{
}

bool Button::MouseMove(float x, float y)
{
    return false;
}

bool Button::MouseLButton(bool bDown)
{
    if (bDown)
    {
        m_DisButton();
        return true;
    }
    return false;
}

bool Button::MouseRButton(bool bDown)
{
    return false;
}

bool Button::KeyClick(int key, int chr)
{
    return false;
}