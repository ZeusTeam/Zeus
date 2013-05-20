#include "globaldef.h"
#include "select_view.h"
#include "control\pool\picture_pool.h"
SelectView::SelectView(int _id, float x, float y, float width, float height)
    : m_x(x)
    , m_y(y)
    , m_width(width)
    , m_height(height)
    , m_currentIndex(-1)
    , m_intervalHor(10)
    , m_intervalVer(10)
    , m_itemCount(0)
    , m_itemHeight(0)
    , m_itemWidth(0)
{
    this->id = _id;
    this->bStatic = false;
    this->bVisible = true;
    this->bEnabled = true;
    this->rect.Set(x, y, x + width, y + height);
}

SelectView::~SelectView()
{
}

void SelectView::Clear()
{
    m_items.clear();
}

bool SelectView::MouseLButton(bool bDown)
{
    int j = 0;
    float x = 0, y = 0;
    for (auto i = m_items.begin(); i != m_items.end(); ++i)
    {
        hge->Input_GetMousePos(&x, &y);
        if (i->rect.TestPoint(x, y) && bDown) //单击item
        {
            m_currentIndex = j;
            break;
        }
        ++j;
    }
    return false;
}

bool SelectView::KeyClick(int key, int chr)
{
    if (key == KEY_LEFT && m_currentIndex > 0 )
    {
        --m_currentIndex;
    }
    else if(key == KEY_RIGHT && m_currentIndex < m_itemCount - 1)
    {
        ++m_currentIndex;
    }
    return false;
}

void SelectView::Render()
{
    int j = 0;
    for (auto i = m_items.begin(); i != m_items.end(); ++i)
    {
        if (i->rect.x1 != -1) // -1 表示不显示
        {
            if (j == m_currentIndex && i->focusTex) //绘制选中item
            {
                i->focusTex->SetRenderRect(0, 0, i->rect.x2 - i->rect.x1, i->rect.y2 - i->rect.y1);
                i->focusTex->Render(i->rect.x1, i->rect.y1);
            }
            else if(i->normalTex)
            {
                i->normalTex->SetRenderRect(0, 0, i->rect.x2 - i->rect.x1, i->rect.y2 - i->rect.y1);
                i->normalTex->Render(i->rect.x1, i->rect.y1);
            }
        }
        ++j;
    }
}

void SelectView::Refresh()
{
    float x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    for (auto i = m_items.begin(); i != m_items.end(); ++i)
    {
        if (i == m_items.begin()) //第一个
        {
            x1 = m_x + m_intervalHor;
            y1 = m_y + m_intervalVer;
            //没有设置item大小 默认为第一个tex的大小
            if (!m_itemHeight && !m_itemWidth && i->normalTex)
            {
                m_itemWidth = i->normalTex->GetWidth();
                m_itemHeight = i->normalTex->GetHeight();
            }
        }
        else if (x1 + m_intervalHor + m_itemWidth > m_width) //需要换行
        {
            x1 = m_x + m_intervalHor;
            y1 = y2 + m_intervalVer;
        }
        else //无需换行
        {
            x1 = x2 + m_intervalHor;
        }
        // 得到rect右下角坐标
        x2 = x1 + m_itemWidth;
        y2 = y1 + m_itemHeight;
        if (x2 > m_x + m_width || y2 > m_y + m_height) //超出边界
        {
            i->rect.Set(-1, -1, -1, -1); //不显示
        }
        else
        {
            i->rect.Set(x1, y1, x2, y2);
        }
    }
}

void SelectView::DeleteItem(int index)
{
    if (index < 0 || index > m_items.size())
    {
        return;
    }
    auto i = m_items.begin();
    for (int j = 0; j <= index; ++j)
    {
        ++i; //遍历链表
    }
    m_items.erase(i);
    //更新一下item的rect
    Refresh();
    --m_itemCount;
}

void SelectView::AddItem(const std::string normalTexID, const std::string focusTexID)
{
    SelectItem si = {0};
    si.normalTex = PicturePool::Instance()->Get(normalTexID);
    si.focusTex = PicturePool::Instance()->Get(focusTexID);
    m_items.push_back(si);
    Refresh();
    ++m_itemCount;
}

void SelectView::InserItem(int index, const std::string normalTexID, const std::string focusTexID)
{
    if (index < 0 || index > m_items.size())
    {
        return;
    }
    SelectItem si = {0};
    si.normalTex = PicturePool::Instance()->Get(normalTexID);
    si.focusTex = PicturePool::Instance()->Get(focusTexID);
    auto i = m_items.begin();
    for (int j = 0; j <= index; j++)
    {
        ++i; //遍历链表
    }
    m_items.insert(i, si);
    //更新一下item的rect
    Refresh();
    ++m_itemCount;
    if (index <= m_currentIndex)
    {
        ++m_currentIndex;
    }
}

void SelectView::SetItemTex(int index, const std::string normalTexID, const std::string focusTexID)
{
    if (index < 0 || index > m_items.size())
    {
        return;
    }
    auto i = m_items.begin();
    for (int j = 0; j <= index; j++)
    {
        ++i; //遍历链表
    }
    i->normalTex = PicturePool::Instance()->Get(normalTexID);
    i->focusTex = PicturePool::Instance()->Get(focusTexID);    
    //更新一下item的rect
    Refresh();
}

SelectItem SelectView::GetItem(int index) const
{
    SelectItem si = {0};
    if (index < 0 || index > m_items.size())
    {
        return si; // 返回个空的
    }
    auto i = m_items.begin();
    for (int j = 0; j <= index; j++)
    {
        ++i; //遍历链表
    }
    return *i;
}

void SelectView::SetCurrentItem(int index)
{
    if (index < 0 || index > m_items.size())
    {
        return ;
    }
    m_currentIndex = index;
}