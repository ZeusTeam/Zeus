#include "globaldef.h"
#include "role_select_item.h"

RoleSelectItem::RoleSelectItem(int _id, bool _bStatic, float x, float y, const std::string roleName, 
                       TextureObject* normalTex, TextureObject* focusTex, AnimationObject* enterAnimation, 
                       AnimationObject* leaveAnimation)
                       : m_x(x)
                       , m_y(y)
                       , m_roleName(roleName)
                       , m_normalTex(normalTex)
                       , m_focusTex(focusTex)
                       , m_enterAnimation(enterAnimation)
                       , m_leaveAnimation(leaveAnimation)
                       , m_isDoneEnter(true)
                       , m_isDoneLeave(true)
                       , m_focused(false)
{
    this->id = _id;
    this->bStatic = _bStatic;
    this->bVisible = true;
    this->bEnabled = true;
    this->rect.Set(x, y, x + normalTex->GetWidth(), y + normalTex->GetHeight());
}

RoleSelectItem::~RoleSelectItem()
{
}
void RoleSelectItem::Focus(bool bFocused)
{
    m_focused = bFocused;
}

void RoleSelectItem::Render()
{
    if (m_focused)
    {
        if (m_focusTex)
        {
            m_focusTex->Render(m_x, m_y);
        }
        else if (m_normalTex)
        {
            m_normalTex->Render(m_x, m_y);
        }
    }
    else
    {
        if (m_normalTex)
        {
            m_normalTex->Render(m_x, m_y);
        }
    }
}

void RoleSelectItem::Enter()
{
    if (m_enterAnimation)
    {
        m_enterAnimation->Play(0, m_enterAnimation->GetFrames(), false);
        m_isDoneEnter = false;
    }
}

void RoleSelectItem::Leave()
{
    if (m_leaveAnimation)
    {
        m_leaveAnimation->Play(0, m_leaveAnimation->GetFrames(), false);
        m_isDoneLeave = false;
    }
}

bool RoleSelectItem::IsDone()
{
    return m_isDoneEnter && m_isDoneLeave;
}

void RoleSelectItem::Update(float dt)
{
    if (m_enterAnimation && !m_isDoneEnter)
    {
        if (m_enterAnimation->GetFrames() == m_enterAnimation->CurrentFrame()) //进入动画播放完毕
        {
                m_isDoneEnter = true;
        }
        else
        {
            m_enterAnimation->Update();
        }
    }
    if (m_leaveAnimation && !m_isDoneLeave)
    {
        if (m_leaveAnimation->GetFrames() == m_leaveAnimation->CurrentFrame()) //离开动画播放完毕
        {
            m_isDoneLeave = true;
        }
        else
        {
            m_leaveAnimation->Update();
        }
    }
}

bool RoleSelectItem::KeyClick(int key, int chr)
{
    if (key == KEY_ENTER) //按下回车 选择角色 返回ID
    {
        return true;
    }

    return false;
}

bool RoleSelectItem::MouseLButton(bool bDown)
{
    if (bDown) //鼠标左键按下
    {
        
    }
    else //鼠标左键释放
    {
        return true;
    }
    return false;
}