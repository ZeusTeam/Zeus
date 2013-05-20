#include "globaldef.h"
#include "start_menu_item.h"

StartMenuItem::StartMenuItem(int _id, float x, float y, std::string title, TextureObject* texBg)
    : m_x(x)
    , m_y(y)
    , m_texBg(texBg)
    , m_title(title)
    , m_isFocused(false)
{
    this->id = _id;
    this->bStatic = false;
    this->bVisible = true;
    this->bEnabled = true;

    if (!utils::InstallFont("res\\fzfys.ttf"))
    {
        utils::ErrorMessage("StartMenuItem初始化:安装字体'fzwys.ttf'失败");
    }
    m_font = new FontObject("方正风雅宋简体", 46);
    if (!m_font)
    {
        utils::ErrorMessage("StartMenuItem初始化:读字体'方正风雅宋简体'失败");
    }
}

StartMenuItem::~StartMenuItem()
{
    if (m_font)
    {
        delete m_font;
    }
    utils::UninstallFont("res\\fzfys.ttf");
}


void StartMenuItem::Render()
{
    if (m_texBg)
    {
        m_texBg->Render(m_x, m_y);
    }
    if (m_font)
    {
        if (m_isFocused) ///选中的item文字为蓝色
        {
            m_font->SetColor(0xFF1b7fcc);
        }
        else
        {
            m_font->SetColor(0xFF2E2D2D);
        }

        m_font->Print(m_x, m_y, m_title.c_str());
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