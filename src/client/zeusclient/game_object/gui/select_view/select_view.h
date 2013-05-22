#ifndef SELECT_VIEW_
#define SELECT_VIEW
//////////////////////////////////////////////////////////
//          SelectView GUI组件
//
//  作用: 提供几个Item 用户可以通过单击或者键盘输入 选择需要的Item
//
//  Item的属性:  SelectView管理的索引index、
//               纹理tex、是否为焦点focus、在客户区对应的矩形rect
//  注意事项: 如果没有设置 width和height将为第一个item的Tex的width和height
//////////////////////////////////////////////////////////
#include <list>
#include <string>
#include "game_object\gui\gui_item.h"
#include "control\control_object\texture_object.h"

struct SelectItem
{
    TextureObject* normalTex;       //平常纹理
    TextureObject* focusTex;        //为焦点时的纹理
    hgeRect rect;                  //在客户区的矩形
};
typedef std::list<SelectItem> SelectItemList;

class SelectView
    : public GUIItem
{
public:

    SelectView(int _id, float x, float y, float width, float height);
    ~SelectView();
    virtual void Render();
    virtual bool MouseLButton(bool bDown);
    virtual bool KeyClick(int key, int chr);

    void AddItem(const std::string normalTexID, const std::string focusTexID);
    void InserItem(int index, const std::string normalTexID, const std::string focusTexID);
    void DeleteItem(int index);
    void Clear();

    void SetItemTex(int index, const std::string normalTexID, const std::string focusTexID);
    //如果没有设置 width和height将为第一个item的Tex的width和height
    inline  void SetItemWidth(float w) { m_itemWidth = w; }
    inline  void SetItemHeight(float h) { m_itemHeight = h; }
    inline  void SetCurrentItem(int index);
    inline  void SetHorInterval(float interval) { m_intervalHor = interval; }
    inline  void SetVerInterval(float interval) { m_intervalVer = interval; }

    inline  int GetSelect() const { return m_currentIndex; }
    inline  int GetCount() const { return m_itemCount; }

    SelectItem GetItem(int index) const;

private:
    void Refresh();                         //产生变动后 重新计算Item的信息

    SelectItemList m_items;               //保存所有item信息的容器
    float m_itemWidth;                      //每个item的大小由第一个元素决定 也可以设定
    float m_itemHeight;
    float m_intervalHor;                      //horizontal Item之间水平间隔
    float m_intervalVer;                      //vertical Item之间垂直间隔
    int m_currentIndex;                     //当前item的索引
    int m_itemCount;                        //item的总数
    float m_x;
    float m_y;
    float m_height;
    float m_width;
};


#endif