#include "scroll_bar.h"

#define BTN_PROPORTION 0.037f    //按钮与滑块条长度比例

ScrollBar::ScrollBar(int _id, float x, float y, float width, float height, int length, bool horizontal, int minMove, bool focusRemain)
    : m_x(x)
    , m_y(y)
    , m_w(width)
    , m_h(height)
    , m_maxLen(length)
    , m_hor(horizontal)
    , m_minMove(minMove)
    , m_focusRemain(focusRemain)
    , m_pos(0)
{
    ///根据比例计算出滑块的长度
    m_sliderLen = minMove / length * height;

    //根据不同滚动条类别计算按钮的矩形
    if (horizontal)//横向滚动条
    {
        m_upBtnRect = new hgeRect(x - BTN_PROPORTION * width, y, x, y + height);
        m_downBtnRect = new hgeRect(x + width, y, x + width + BTN_PROPORTION * width, y + height);
    }
    else  //纵向滚动条
    {
        m_upBtnRect = new hgeRect(x, y - BTN_PROPORTION * height, x + width, y);
        m_downBtnRect = new hgeRect(x , y + height, x + width, y + height + BTN_PROPORTION * height);
    }

    rect.Set(m_upBtnRect->x1, m_upBtnRect->y1, m_downBtnRect->x2, m_downBtnRect->y2);
    
    m_sliderColor.SetHWColor(ARGB(155, 0, 0, 0));
    m_upBtnColor.SetHWColor(ARGB(155, 0, 0, 0));
    m_downBtnColor.SetHWColor(ARGB(155, 0, 0, 0));
    m_prevAlpha = m_sliderColor.a;
}

ScrollBar::~ScrollBar()
{
    delete m_upBtnRect;
    delete m_downBtnRect;
}

void ScrollBar::Render()
{
    if (m_hor) //横向滚动条
    {

    }
    else // 纵向滚动条
    {

}



void ScrollBar::Focus(bool bFocused)
{
    if (bFocused && !m_focusRemain) //不停留焦点 传递给下一个obj
    {
        gui->SetFocus(next->id);
    }
}

void ScrollBar::MouseOver(bool bOver)
{
    float x = 0;
    float y = 0;
    hge->Input_GetMousePos(&x, &y);
    if (bOver) // 鼠标进入 碰撞到的部分颜色加深
    {
        if (m_upBtnRect->TestPoint(x, y)) //碰撞到up按钮
        {
            if (m_upBtnColor.a + 50 <= 255)
            {
                m_upBtnColor.a += 50;
            }
            else
            {
                m_upBtnColor.a = 255;
            }

        }
        else if (m_downBtnRect->TestPoint(x, y)) //碰撞到down按钮
        {
            if (m_downBtnColor.a + 50 <= 255)
            {
                m_downBtnColor.a += 50;
            }
            else
            {
                m_downBtnColor.a = 255;
            }
        }
        else // 碰撞到滑块条部分
        {
            if (m_sliderColor.a + 50 <= 255)
            {
                m_sliderColor.a += 50;
            }
            else
            {
                m_sliderColor.a = 255;
            }
        }

    }
    else // 鼠标离开
    {
        m_upBtnColor.a = m_prevAlpha;
        m_downBtnColor.a = m_prevAlpha;
        m_sliderColor.a = m_prevAlpha;
    }
}