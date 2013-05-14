#include "edit_box.h"
#include "engine\game_engine.h"
#include "globaldef.h"
#include <atlbase.h>

WNDPROC EditBox::m_LastHgeWndProc = NULL; ///> 原有程序回调
EditBox* EditBox::m_FocusEditPtr = NULL; ///> 当前获得焦点的Edit

LRESULT CALLBACK EditBox::EditWndProc(HWND hWnd, UINT nMsg,
                                      WPARAM wParam, LPARAM lParam)
{
    if (WM_KEYDOWN == nMsg || WM_KEYUP == nMsg)
    {
        MSG aMsg;
        memset(&aMsg,0,sizeof(MSG));

        aMsg.hwnd = hWnd;
        aMsg.message = nMsg;
        aMsg.wParam = wParam;
        aMsg.lParam = lParam;
        aMsg.time = GetTickCount();

        TranslateMessage(&aMsg);

        if (m_FocusEditPtr && WM_KEYDOWN == nMsg)
        {
            switch(wParam)
            {
            case VK_DELETE: //key delete
            case VK_LEFT: //key left
            case VK_RIGHT: //key right
            case VK_UP:
            case VK_DOWN:
            case VK_HOME: //key home
            case VK_END: //key end
                m_FocusEditPtr->OnChar(static_cast<UINT>(wParam),
                    LOWORD(lParam), HIWORD(lParam));
                break;
            }
        }
    }
    else if (WM_CHAR == nMsg )
    {
        if (m_FocusEditPtr)
        {
            m_FocusEditPtr->OnChar(static_cast<UINT>(wParam),
                LOWORD(lParam), HIWORD(lParam));
            return TRUE;
        }
    }
    else if (WM_IME_CHAR == nMsg)
    {
        if (m_FocusEditPtr)
        {
            m_FocusEditPtr->OnCharHZ(static_cast<UINT>(wParam),
                LOWORD(lParam), HIWORD(lParam));
            return TRUE;
        }
    }

    return m_LastHgeWndProc
        ? m_LastHgeWndProc(hWnd,nMsg,wParam,lParam)
        : TRUE;
}

bool EditBox::DiposeKey()
{
    if (!m_Input)
    {
        return false;
    }
    if (m_Input->IsKey(KEY_TAB) == Key_Down)
    {
        this->CatStr("    ");
    }
    else if (m_Input->IsKey(KEY_BACKSPACE) == Key_Down)
    {
        if (!m_Text.empty())
        {
            m_Text.pop_back();
            m_CharPos--;
        }
    }
    else if ((m_Input->IsKey(KEY_SHIFT) == Key_Down)
        && (m_Input->IsKey(KEY_LEFT) == Key_Down))
    {
        if (m_CharPos <= vecFontWidth.size() && m_CharPos != 0)
        {
            if ((int)m_bgFontPos != (int)m_PresentFontWidth)
            {
                if (!m_IsSelect)
                {
                    m_LastCurrPos = m_bgFontPos;
                }
                m_bgFontPos += vecFontWidth[(int)m_CharPos - 1];
                m_CurrPos = m_bgFontPos;
                m_IsSelect = true;
            }
        }
    }
    else if ((m_Input->IsKey(KEY_SHIFT) == Key_Down)
        && (m_Input->IsKey(KEY_RIGHT) == Key_Down))
    {
        if ((int)m_CharPos <= (int)vecFontWidth.size() && m_CharPos != 0)
        {
            if (m_bgFontPos != 0)
            {
                if (!m_IsSelect)
                {
                    m_LastCurrPos = m_bgFontPos;
                }
                m_bgFontPos -= vecFontWidth[(int)m_CharPos - 1];
                m_CurrPos = m_bgFontPos;
                m_IsSelect = true;
            }
        }
    }
    else if (m_Input->IsKey(KEY_LEFT) == Key_Down)
    {
        if (m_CharPos <= vecFontWidth.size() && m_CharPos != 0)
        {
            if ((int)m_bgFontPos != (int)m_PresentFontWidth)
            {
                m_bgFontPos += vecFontWidth[(int)m_CharPos - 1];
            }
        }
        m_IsSelect = false;
    }
    else if (m_Input->IsKey(KEY_RIGHT) == Key_Down)
    {
        if ((int)m_CharPos <= (int)vecFontWidth.size() && m_CharPos != 0)
        {
            if (m_bgFontPos != 0)
            {
                m_bgFontPos -= (float)vecFontWidth[(int)m_CharPos - 1];
            }
        }
        m_IsSelect = false;
    }
    else if (m_Input->IsKey(KEY_UP) == Key_Down)
    {
    }
    else if (m_Input->IsKey(KEY_DOWN) == Key_Down)
    {
    }
    else
    {
        return false;
    }
    return true;
}

void EditBox::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    if (m_FocusEditPtr != this)
    {
        return;
    }
    if(DiposeKey())
    {
        return;
    }
    if (m_FontSize <= m_Edit_w)
    {
        static   int   i = 0;
        static char szImeChar[3];
        szImeChar[2]='\0';

        if(nChar & 0x80)
        {
            if(i!=2)
            {
                szImeChar[i]=(char)nChar;
                i++;
            }
                
            if(i==2)
            {
                i=0;
                CatStr(szImeChar);
                m_CharPos++;
            }
         }
         else
         {
                i = 0;
                szImeChar[0]=(char)nChar;
                szImeChar[1]='\0';
                CatStr(szImeChar);
                m_CharPos++;
          }
    }
}

void EditBox::CatStr(const std::string& strText)
{
    m_Text += CA2W(strText.c_str());
}

void EditBox::OnCharHZ( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    if (m_FocusEditPtr != this)
    {
        return;
    }
    if(DiposeKey())
    {
        return;
    }
    if (m_FontSize < m_Edit_w)
    {
        char szImeChar[3];

        if (nChar < 128)
        {
            szImeChar[0]=(char)nChar;
            szImeChar[1]='\0';
        }
        else
        {
            szImeChar[0]=(char)(nChar >> 8);
            szImeChar[1]=(char)nChar;
            szImeChar[2]='\0';
        }
        CatStr(szImeChar);
        m_CharPos++;
    }
}

EditBox::EditBox(int _Id, UINT nEditWidth, UINT nEditHeight, DWORD nFontColor,
        char* lpFontName, UINT nFontSize, bool bBold,
        bool bItalic, bool bAntialias)
{
    this->id = _Id;
    this->bStatic = false;
    this->bVisible = true;
    this->bEnabled = true;

    m_PresentFontWidth = 0;
    m_IsSelect = false;
    m_Graphics = GraphicsEngine::Instance();
    m_Input = InputEngine::Instance();
    m_Edit_w = nEditWidth;
    m_Edit_h = nEditHeight;
    m_CharPos = 0;
    m_bgFontPos = 0;
    m_Edit_Pos_x = 0;
    m_Edit_Pos_y = 0;
    m_Border_x = 0;
    m_Border_y = 0;
    m_LastCurrPos = 0;
    m_CurrPos = 0;
    m_CurrTimer = 0.0f;
    m_IsShowCurr = false;
    m_IsOnlyNumber = false;
    m_Border_w = (float)nEditWidth;
    m_Border_h = (float)nEditHeight;
    m_Edit_w = (nEditWidth == 0 ? 1 : nEditWidth);
    m_Edit_h = (nFontSize == 0 ? 12 : nFontSize);

    m_Font = new FontObject(lpFontName, nFontSize, bBold, bItalic, bAntialias);

    m_pSprite = new hgeSprite(NULL, 0, 0,
        1.2f * float(nFontSize) / 12, (float)m_Edit_h);

    m_bgSprite = new hgeSprite(NULL, 0, 0,
        1.2f * float(nFontSize) / 12, (float)m_Edit_h);

    if (m_Font && m_pSprite && m_bgSprite)
    {
        m_FontSize = (int)m_Font->GetFontSize();
        m_bgSprite->SetColor(0x99BCCEF7);
        m_pSprite->SetColor(nFontColor);
        m_Font->SetColor(nFontColor);
    }
    else
    {
        return;
    }

    if (!m_LastHgeWndProc)
    {
        m_LastHgeWndProc = (WNDPROC)::GetWindowLong(
            GameEngine::Instance()->GethWnd(), GWL_WNDPROC);
        ::SetWindowLong(GameEngine::Instance()->GethWnd(),
            GWL_WNDPROC, (LONG)EditWndProc);
    }
}

EditBox::~EditBox()
{
}

void EditBox::Render(float x, float y)
{
    m_Border_x = x - 1;
    m_Border_y = y - 1;
    m_Border_w = (float)m_Edit_w + 2;
    m_Border_h = (float)m_Edit_h + 2;

    //绘制边框
    if (m_Graphics)
    {
        m_Graphics->RenderLine(m_Border_x, m_Border_y,
            m_Border_x + m_Border_w, m_Border_y);
        m_Graphics->RenderLine(m_Border_x, m_Border_y,
            m_Border_x, m_Border_y + m_Border_h);
        m_Graphics->RenderLine(m_Border_x + m_Border_w, m_Border_y + m_Border_h,
            m_Border_x + m_Border_w, m_Border_y);
        m_Graphics->RenderLine(m_Border_x + m_Border_w, m_Border_y + m_Border_h,
            m_Border_x, m_Border_y + m_Border_h);
    }
    m_Graphics->SetClipping((int)x, (int)y, (int)m_Border_w, (int)m_Border_h);
    if (m_FocusEditPtr == this && m_IsShowCurr)
    {
        m_pSprite->Render(m_PresentFontWidth - m_bgFontPos, y);
    }
    m_Font->Render(x, y, (LPCSTR)CW2A(m_Text.c_str()));
    if (m_FocusEditPtr == this && m_IsSelect)
    {
        m_bgSprite->RenderStretch(
                m_Edit_Pos_x + (m_PresentFontWidth - m_LastCurrPos),
                m_Edit_Pos_y,
                m_Edit_Pos_x + (m_PresentFontWidth - m_CurrPos),
                m_Edit_Pos_y + (m_FontSize));
    }
    m_Graphics->SetClipping();
}

void EditBox::Render()
{
    hgeSprite* ClearSprite = new hgeSprite(NULL, 0, 0,
        (float)m_Edit_w, (float)m_Edit_h);
    ClearSprite->SetColor(ARGB(1,0,0,0));
    if (ClearSprite)
    {
        ClearSprite->RenderStretch(
                m_Edit_Pos_x,
                m_Edit_Pos_y,
                m_Edit_Pos_x + m_Edit_w,
                m_Edit_Pos_y + m_Edit_h);
    }
    this->Render(m_Edit_Pos_x, m_Edit_Pos_y);
    if (ClearSprite)
    {
        delete ClearSprite;
    }
}

void EditBox::SetPos(float x, float y)
{
    m_Edit_Pos_x = x;
    m_Edit_Pos_y = y;
}

bool EditBox::MouseLButton(bool bDown)
{
    if (bDown)
    {
        m_FocusEditPtr = this;
        m_IsShowCurr = true;
    }
    return false;
}

void EditBox::Focus(bool bFocused)
{
    if (bFocused)
    {
        m_FocusEditPtr = this;
        m_IsShowCurr = true;
    }
    else
    {
        m_FocusEditPtr = NULL;
        m_IsShowCurr = false;
    }
}

void EditBox::Update(float dt)
{
    this->rect.x1 = m_Edit_Pos_x;
    this->rect.y1 = m_Edit_Pos_y;
    this->rect.x2 = m_Edit_Pos_x + m_Edit_w;
    this->rect.y2 = m_Edit_Pos_y + m_Edit_h;
    m_CurrTimer += dt;
    if (m_CurrTimer >= 0.5f)
    {
        m_IsShowCurr = true;
        if (m_CurrTimer >= 1.0f)
        {
            m_CurrTimer = 0;
        }
    }
    else
    {
        m_IsShowCurr = false;
    }
    m_PresentFontWidth = 0;
    vecFontWidth.clear();
    for (auto it = m_Text.begin(); it != m_Text.end(); it++)
    {
        if (!m_Font)
        {
            break;
        }
        vecFontWidth.push_back(m_Font->GetWidthFromCharacter(*it));
        m_PresentFontWidth += m_Font->GetWidthFromCharacter(*it);
    }
}

void EditBox::Reset()
{
}

bool EditBox::KeyClick(int key, int chr)
{
    if (m_Input->IsKey(KEY_UP) == Key_Down)
    {
        return true;
    }
    else if (m_Input->IsKey(KEY_DOWN) == Key_Down)
    {
        return true;
    }
    return false;
}

void EditBox::SetText(const std::string& strText)
{
    m_Text = CA2W(strText.c_str());
}

const std::wstring& EditBox::GetText() const
{
    return m_Text;
}