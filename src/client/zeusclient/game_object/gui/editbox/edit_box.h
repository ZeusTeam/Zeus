#ifndef EDIT_BOX_
#define EDIT_BOX_

#include "game_object\gui\gui_item.h"
#include "control\control_object\font_object.h"
#include "engine\graphics_engine.h"
#include "engine\input_engine.h"
#include <string>
#include <vector>

class EditBox
    : public GUIItem
{
public:
    EditBox(int _Id, UINT nEditWidth, UINT nEditHeight, DWORD nFontColor,
        char* lpFontName, UINT nFontSize, bool bBold = false,
        bool bItalic = false, bool bAntialias = true);

    virtual ~EditBox();

    virtual void Render();

    virtual void Reset();

    virtual void SetPos(float x, float y);

    virtual void Render(float x, float y);

    virtual void Focus(bool bFocused);//��������

    virtual void Update(float dt);

    virtual bool MouseLButton(bool bDown);

    virtual bool KeyClick(int key, int chr);

    virtual void SetText(const std::string& strText);

    virtual const std::wstring& GetText() const;

    virtual void OnChar( UINT nChar, UINT nRepCnt, UINT nFlags );

    virtual void OnCharHZ( UINT nChar, UINT nRepCnt, UINT nFlags );

    virtual void CatStr(const std::string& strText);

private:
    static LRESULT CALLBACK EditWndProc(HWND hWnd,
        UINT nMsg, WPARAM wParam, LPARAM lParam);

    static WNDPROC m_LastHgeWndProc;
    static EditBox* m_FocusEditPtr;

    bool DiposeKey();

private:
    std::wstring m_Text;
    std::wstring m_ClipboardText;
    std::vector<float> vecFontWidth;
    FontObject* m_Font;
    int m_Edit_w;
    int m_Edit_h;
    float m_Edit_Pos_x;
    float m_Edit_Pos_y;
    int m_FontSize;
    float m_PresentFontWidth;
    float m_bgFontPos;
    float m_LastCurrPos;
    float m_CurrPos;
    float m_CurrTimer;
    bool m_IsShowCurr;
    bool m_IsSelect;
    bool m_IsFocus; ///>�Ƿ��ǽ���
    bool m_IsOnlyNumber; ///>�Ƿ�ֻ������������
    float m_Border_x;
    float m_Border_y;
    float m_Border_w;
    float m_Border_h;
    float m_CharPos;
    hgeSprite* m_pSprite; ///> ��꾫��
    hgeSprite* m_bgSprite; ///> ���ѡ�־���
    GraphicsEngine* m_Graphics;
    InputEngine* m_Input;
};

#endif