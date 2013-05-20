#ifndef STATIC_BOX_
#define STATIC_BOX_

#include "game_object\gui\gui_item.h"
#include "control\control_object\font_object.h"
#include <string>

class StaticBox
    : public GUIItem
{
public:
    StaticBox(int _Id, DWORD nFontColor,
        char* lpFontName, UINT nFontSize, bool bBold = false,
        bool bItalic = false, bool bAntialias = true    );
    virtual ~StaticBox();

    virtual void SetText(const std::string& strText);

    virtual const std::string& GetText() const;

    void SetPos(float x, float y);

    void Update(float dt);

    virtual void Render();

    void SetBackground(DWORD color);

private:
    std::string m_Text;
    FontObject* m_Font;
    int m_Static_w;
    int m_Static_h;
    float m_Static_x;
    float m_Static_y;
    DWORD m_BgColor;
    hgeSprite* m_bgSprite; ///> ±³¾°É«¿é
};

#endif