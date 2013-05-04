#include "globaldef.h"
#include "start_menu_item.h"

StartMenuItem::StartMenuItem(int _id, float x, float y, TextureObject* texUsual, TextureObject* texFocused)
    : m_x(x)
    , m_y(y)
    , m_texFocused(texFocused)
    , m_texUsual(texUsual)
    , m_isFocused(false)
{
    this->id = _id;
    this->bStatic = false;
    this->bVisible = true;
    this->bEnabled = true;
}

StartMenuItem::~StartMenuItem()
{
    if (m_texFocused)
    {
        delete m_texFocused;
    }
    if (m_texUsual)
    {
        delete m_texUsual;
    }
}


void StartMenuItem::Render()
{
    if (m_isFocused)
    {
        m_texFocused->Render(m_x, m_y);
    }
    else
    {
        m_texUsual->Render(m_x, m_y);
    }
}


void StartMenuItem::Focus(bool bFocused)
{
    m_isFocused = bFocused;
}

bool StartMenuItem::KeyClick(int key, int chr)
{
    if (key == KEY_ENTER)
        return true;
    return false;
}