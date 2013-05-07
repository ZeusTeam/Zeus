#ifndef EDIT_BOX_
#define EDIT_BOX_

#include "game_object\gui\gui_item.h"
#include "control\control_object\font_object.h"
#include "engine\graphics_engine.h"
#include "engine\input_engine.h"
#include <string>

class EditBox
    : public GUIItem
{
public:
    EditBox(int _Id, UINT nEditWidth, UINT nEditHeight, DWORD nFontColor,
        char* lpFontName, UINT nFontSize, bool bBold = false,
        bool bItalic = false, bool bAntialias = true);

    virtual ~EditBox();

    virtual void Render();

    virtual void SetPos(float x, float y);

    virtual void Render(float x, float y);

    virtual void Focus(bool bFocused);//焦点设置

    virtual void Update(float dt);

    virtual bool MouseLButton(bool bDown);

    virtual bool KeyClick(int key, int chr);

    virtual void SetText(const std::string& strText);

    virtual const std::string& GetText() const;

    virtual void OnChar( UINT nChar, UINT nRepCnt, UINT nFlags );

    virtual void OnCharHZ( UINT nChar, UINT nRepCnt, UINT nFlags );

    virtual void CatStr(const std::string& strText);

private:
    static LRESULT CALLBACK EditWndProc(HWND hWnd,
        UINT nMsg, WPARAM wParam, LPARAM lParam);

    bool DiposeKey();

private:
    std::wstring m_Text;
    std::wstring m_ClipboardText;
    FontObject* m_Font;
    int m_Edit_w;
    int m_Edit_h;
    float m_Edit_Pos_x;
    float m_Edit_Pos_y;
    int m_FontSize;
    int m_PresentFontWidth;
    bool m_IsFocus; ///>是否是焦点
    bool m_IsOnlyNumber; ///>是否只允许数字输入
    float m_Border_x;
    float m_Border_y;
    float m_Border_w;
    float m_Border_h;
    float m_CharPos;
    hgeSprite* m_pSprite; ///> 光标精灵
    hgeSprite* m_bgSprite; ///> 光标选字精灵
    GraphicsEngine* m_Graphics;
    InputEngine* m_Input;
};

#endif