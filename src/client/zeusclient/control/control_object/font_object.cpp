#include "font_object.h"
#include "engine\texture_engine.h"
///>暂时使用ATL
#include <atlbase.h>

///>使用微妙的平衡(BOGY)字体代码 进行小幅度修改
__inline float _floor(float f)
{
    static int _n;
    _asm fld f
    _asm fistp _n
    return (float)_n;
}

const unsigned char g_byAlphaLevel[65] =
{
      0,  4,  8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48,
     52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96,100,
    104,108,112,116,120,124,128,132,136,140,144,148,152,
    156,160,164,168,172,176,180,184,188,192,196,200,204,
    208,212,216,220,224,228,232,236,240,244,248,252,255
};


FontObject::FontObject(const std::string& strFontName,
                       int nFaceSize,
                       bool bBold,
                       bool bItalic,
                       bool bAntialias)
{
    m_Graphics = GraphicsEngine::Instance();
    m_Hdc = 0;
    if (!m_Graphics)
    {
        return;
    }
    m_Hdc = ::CreateCompatibleDC(m_Graphics->WindowDC());
    ::SetMapMode(m_Hdc, MM_TEXT);
    ::SetTextColor(m_Hdc,RGB(255,255,255));
    ::SetBkColor(m_Hdc,RGB(0,0,0));

    m_hFont = ::CreateFont(
        -nFaceSize,
        0,
        0,
        0,
        (bBold) ? FW_BOLD : FW_NORMAL,
        bItalic,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        FF_DONTCARE | DEFAULT_PITCH,
        strFontName.c_str());

    if (!m_hFont)
    {
        return;
    }

    ::SelectObject(m_Hdc, m_hFont);

    m_nAntialias = bAntialias ? GGO_GRAY8_BITMAP : GGO_BITMAP;
    TEXTMETRIC tm;
    ::GetTextMetrics(m_Hdc,&tm);
    m_nAscent = tm.tmAscent;

    m_nFontSize = static_cast<float>(nFaceSize);
    m_nKerningWidth = 0;
    m_nKerningHeight = 0;

    m_pSprite = new hgeSprite(0, 0, 0, 0, 0);
    m_pSprite->SetColor(ARGB(255, 255, 255, 255));
}

void FontObject::Print( float x, float y, const char *format, ... )
{
    char sBuffer[10240] = {0};
    char *lpsArg=(char*)&format+sizeof(format);
    vsprintf_s(sBuffer, format, lpsArg);

    Render(x, y, sBuffer);
}

unsigned int FontObject::GetGlyphByCharacter( wchar_t c )
{
    unsigned int idx = (unsigned int)c;
    if (NULL == (m_Glyphs[idx].t)) CacheCharacter(idx,c);
    return idx;
}

inline float FontObject::GetWidthFromCharacter( wchar_t c,
                                                bool original)
{
    unsigned int idx = GetGlyphByCharacter(c);
    if (original && idx > 0 && idx < Font_Count) return m_Glyphs[idx].c;
    return	(idx >= 0x2000) ? m_nFontSize : _floor(m_nFontSize / 2);
}

inline void FontObject::CacheCharacter(unsigned int idx, wchar_t c)
{
    if (idx < Font_Count && NULL == m_Glyphs[idx].t)
    {
        UINT nChar = (UINT)c;

        MAT2 mat2 = {{0,1},{0,0},{0,0},{0,1}};
        GLYPHMETRICS gm;
        DWORD nLen = ::GetGlyphOutlineW(m_Hdc,nChar,m_nAntialias,&gm,0,NULL,&mat2);

        GameTexture hTex = TextureEngine::Instance()->Create(
            (float)gm.gmBlackBoxX,
            (float)gm.gmBlackBoxY);

        if (NULL == hTex) return;

        if((signed)nLen > 0)
        {
            LPBYTE lpBuf = new BYTE[nLen];

            if (nLen == ::GetGlyphOutlineW(m_Hdc,nChar,m_nAntialias,&gm,nLen,lpBuf,&mat2))
            {
                BYTE* lpSrc = lpBuf;
                DWORD* lpDst = TextureEngine::Instance()->Lock(hTex,FALSE);

                if (GGO_BITMAP == m_nAntialias)
                {
                    LONG nSrcPitch = (gm.gmBlackBoxX / 32 + (gm.gmBlackBoxX % 32 == 0 ? 0 : 1)) * 4;
                    LONG nDstPitch = TextureEngine::Instance()->GetWidth(hTex);

                    for (UINT y = 0; y < gm.gmBlackBoxY; ++y)
                    {
                        for (UINT x = 0; x < gm.gmBlackBoxX; ++x)
                        {
                            for(UINT k = 0; k < 8; ++k)
                            {
                                UINT i = 8 * x + k;
                                if (i >= gm.gmBlackBoxX)
                                {
                                    x+=7;
                                    break;
                                }
                                lpDst[i] = ((lpSrc[x] >> (7 - k)) & 1) ? 0xFFFFFFFF : 0x0;
                            }
                        }

                        lpSrc += nSrcPitch;
                        lpDst += nDstPitch;
                    }
                }
                else
                {
                    LONG nSrcPitch = (gm.gmBlackBoxX / 4 + (gm.gmBlackBoxX % 4 == 0 ? 0 : 1)) * 4;
                    LONG nDstPitch = TextureEngine::Instance()->GetWidth(hTex);

                    for (UINT y = 0; y < gm.gmBlackBoxY; ++y)
                    {
                        for (UINT x = 0; x < gm.gmBlackBoxX; ++x)
                        {
                            lpDst[x] = ARGB(g_byAlphaLevel[lpSrc[x]],0xFF,0xFF,0xFF);
                        }

                        lpSrc += nSrcPitch;
                        lpDst += nDstPitch;
                    }
                }

                TextureEngine::Instance()->Unlock(hTex);
            }

            delete lpBuf;
        }
        else
        {
            
        }

        m_Glyphs[idx].t = hTex;
        m_Glyphs[idx].w = static_cast<float>(gm.gmBlackBoxX);
        m_Glyphs[idx].h = static_cast<float>(gm.gmBlackBoxY);
        m_Glyphs[idx].x = static_cast<float>(-gm.gmptGlyphOrigin.x);
        m_Glyphs[idx].y = static_cast<float>(-m_nAscent + gm.gmptGlyphOrigin.y);
        m_Glyphs[idx].c = static_cast<float>(gm.gmCellIncX);
    }
}

FontObject::~FontObject()
{
    if (m_hFont) ::DeleteObject(m_hFont);
    if (m_Hdc) ::DeleteDC(m_Hdc);
    if(m_pSprite) delete m_pSprite;
}

void FontObject::Render(float x, float y, const std::string& strText)
{
    float offsetX = x;
    float offsetY = y;
    std::wstring strwText(CA2W(strText.c_str()));
    for (auto it = strwText.begin();
        it != strwText.end();
        it++)
    {
        if (*it == L'\n' || *it == L'\r')
        {
            offsetX = x;
            offsetY += (m_nFontSize + m_nKerningHeight);
        }
        else
        {
            unsigned int idx = GetGlyphByCharacter(*it);
            if (idx > 0)
            {
                m_pSprite->SetTexture(m_Glyphs[idx].t);
                m_pSprite->SetTextureRect(0, 0, m_Glyphs[idx].w, m_Glyphs[idx].h);
                m_pSprite->Render(offsetX - m_Glyphs[idx].x, offsetY - m_Glyphs[idx].y);
                offsetX += (GetWidthFromCharacter(*it) + m_nKerningWidth);
            }
            else
            {
                offsetX += (GetWidthFromCharacter(*it) + m_nKerningWidth);
            }
        }
    }
}

void FontObject::SetColor( DWORD dwColor, int i)
{
    if (!m_pSprite)
    {
        return;
    }
    m_pSprite->SetColor(dwColor,i);
}

DWORD FontObject::GetColor(int i) const
{
    if (!m_pSprite)
    {
        return -1;
    }
    return m_pSprite->GetColor(i);
}

void FontObject::SetKerningWidth(float kerning)
{
    m_nKerningWidth = kerning;
}

void FontObject::SetKerningHeight(float kerning)
{
    m_nKerningHeight = kerning;
}

float FontObject::GetKerningWidth()
{
    return m_nKerningWidth;
}

float FontObject::GetKerningHeight()
{
    return m_nKerningHeight;
}

float FontObject::GetFontSize()
{
    return m_nFontSize;
}