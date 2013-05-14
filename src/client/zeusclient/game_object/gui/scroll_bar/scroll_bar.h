#ifndef SCROLL_BAR_
#define SCROLL_BAR_
#include "game_object\gui\gui_item.h"
#include "game_object\gui\button\button.h"
#include "import\hge\include\hge.h"
#include "import\hge\include\hgecolor.h"
class ScrollBar
    : public GUIItem
{
public:
    ScrollBar(int _id, float _x, float _y, float width, float height, int length, bool horizontal = false, int minMove = 1, bool focusRemain = false);
    ~ScrollBar();

    virtual void Render();
    //virtual void Reset();
    virtual void Focus(bool bFocused);
    virtual void MouseOver(bool bOver);
    void SetSliderColor(DWORD color);

    float x;                  //计算up down按钮后的位置
    float y;
    float h;                  //计算up down按钮后的大小
    float w;

private:

    float m_pos;                //当前滑块位置 用百分比表示
    float m_sliderLen;          //滑块显示的长度
    int m_minMove;              //滑块条最小移动的逻辑距离
    int m_maxLen;               //滑块条表示的逻辑长度
    hgeRect* m_upBtnRect;       //往上的按钮
    hgeRect* m_downBtnRect;     //往下的按钮
    bool m_hor;                 //是否为水平滚动条
    bool m_focusRemain;         //是否允许停留焦点
    hgeColor m_upBtnColor;
    hgeColor m_downBtnColor;
};



#endif