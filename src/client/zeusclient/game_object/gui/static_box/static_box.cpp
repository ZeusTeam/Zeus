#include "static_box.h"

StaticBox::StaticBox(int _Id, DWORD nFontColor,
        char* lpFontName, UINT nFontSize, bool bBold,
        bool bItalic, bool bAntialias)
{
    m_Font = new FontObject(lpFontName, nFontSize);
    m_Font->SetColor(nFontColor);
    m_BgColor = ARGB(1, 255, 255, 255);
    m_bgSprite = new hgeSprite(NULL, 0, 0,
    1.2f * float(nFontSize) / 12, m_Font->TextWidth(m_Text.c_str()));
}

StaticBox::~StaticBox()
{
    if (m_Font)
    {
        delete m_Font;
        m_Font = NULL;
    }
}

void StaticBox::SetText(const std::string& strText)
{
    m_Text = strText.c_str();
}

const std::string& StaticBox::GetText() const
{
    return m_Text;
}

void StaticBox::Update(float dt)
{
    m_bgSprite->SetColor(m_BgColor);
    if (m_Font)
    {
        m_Static_w = m_Font->TextWidth(m_Text.c_str());
        m_Static_h = m_Font->GetFontSize();
    }
}

void StaticBox::SetPos(float x, float y)
{
    m_Static_x = x;
    m_Static_y = y;
}

void StaticBox::Render()
{
    if (m_bgSprite)
    {
        m_bgSprite->RenderStretch(
                m_Static_x - 1,
                m_Static_y,
                m_Static_x + m_Static_w + 1,
                m_Static_y + m_Static_h);
    }
    if (m_Font)
    {
        m_Font->Print(m_Static_x, m_Static_y,
            m_Text.c_str());
    }
}

void StaticBox::SetBackground(DWORD color)
{
    m_BgColor = color;
}