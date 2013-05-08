#include "edit_box.h"
#include "engine\game_engine.h"
#include "globaldef.h"
#include <atlbase.h>

WNDPROC g_lpLastHgeWndProc = NULL; ///> 原有程序回调
EditBox* g_lpFocusEditPtr = NULL; ///> 当前获得焦点的Edit

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

        if (g_lpFocusEditPtr && WM_KEYDOWN == nMsg)
        {
            switch(wParam)
            {
            case VK_DELETE: //key delete
            case VK_LEFT: //key left
            case VK_RIGHT: //key right
            case VK_HOME: //key home
            case VK_END: //key end
                g_lpFocusEditPtr->OnChar(static_cast<UINT>(wParam),
                    LOWORD(lParam), HIWORD(lParam));
                break;

            }
        }
    }
    else if (WM_CHAR == nMsg )
    {
        if (g_lpFocusEditPtr)
        {
            g_lpFocusEditPtr->OnChar(static_cast<UINT>(wParam),
                LOWORD(lParam), HIWORD(lParam));
            return TRUE;
        }
    }
    else if (WM_IME_CHAR == nMsg)
    {
        if (g_lpFocusEditPtr)
        {
            g_lpFocusEditPtr->OnCharHZ(static_cast<UINT>(wParam),
                LOWORD(lParam), HIWORD(lParam));
            return TRUE;
        }
    }

    return g_lpLastHgeWndProc
        ? g_lpLastHgeWndProc(hWnd,nMsg,wParam,lParam)
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
        }
    }
    else if ((m_Input->IsKey(KEY_SHIFT) == Key_Down)
        && (m_Input->IsKey(KEY_LEFT) == Key_Down))
    {
        if (m_CharPos <= vecFontWidth.size())
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
        if ((int)m_CharPos <= (int)vecFontWidth.size())
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
        if (m_CharPos <= vecFontWidth.size())
        {
            if ((int)m_bgFontPos != (int)m_PresentFontWidth)
            {
                m_bgFontPos += vecFontWidth[(int)m_CharPos - 1];
                m_IsSelect = false;
            }
        }
    }
    else if (m_Input->IsKey(KEY_RIGHT) == Key_Down)
    {
        if ((int)m_CharPos <= (int)vecFontWidth.size())
        {
            if (m_bgFontPos != 0)
            {
                m_bgFontPos -= (float)vecFontWidth[(int)m_CharPos - 1];
                m_IsSelect = false;
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

void EditBox::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
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

    //LastDtTime=0.5f;
}

void EditBox::CatStr(const std::string& strText)
{
    m_Text += CA2W(strText.c_str());
}

void EditBox::OnCharHZ( UINT nChar, UINT nRepCnt, UINT nFlags )
{
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

    //LastDtTime=0.5f;
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

    if (!g_lpLastHgeWndProc)
    {
        g_lpLastHgeWndProc = (WNDPROC)::GetWindowLong(g_hWnd, GWL_WNDPROC);
        ::SetWindowLong(g_hWnd, GWL_WNDPROC, (LONG)EditWndProc);
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
    if (g_lpFocusEditPtr == this)
    {
        m_pSprite->Render(m_PresentFontWidth - m_bgFontPos, y);
    }
    m_Font->Render(x, y, (LPCSTR)CW2A(m_Text.c_str()));
    if (g_lpFocusEditPtr == this && m_IsSelect)
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
    this->Render(m_Edit_Pos_x, m_Edit_Pos_y);
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
        g_lpFocusEditPtr = this;
    }
    else
    {
        g_lpFocusEditPtr = NULL;
    }
    return true;
}

void EditBox::Focus(bool bFocused)
{
    if (bFocused)
    {
        g_lpFocusEditPtr = this;
    }
    else
    {
        g_lpFocusEditPtr = NULL;
    }
}

void EditBox::Update(float dt)
{
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

bool EditBox::KeyClick(int key, int chr)
{
    return false;
}

void EditBox::SetText(const std::string& strText)
{
    m_Text = CA2W(strText.c_str());
}

const std::string& EditBox::GetText() const
{
    return (LPCSTR)CW2A(m_Text.c_str());
}