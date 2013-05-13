#ifndef FONT_OBJECT_
#define FONT_OBJECT_

#include "engine\game_engine.h"
#include "engine\graphics_engine.h"
#include "import\hge\include\hgesprite.h"
#include "engine\texture_engine.h"
#include <string>

static const int Font_Count = 0xFFFF;

typedef struct _FontGraphObject
{
    _FontGraphObject()
    {
        w = 0.0f;
        h = 0.0f;
        x = 0.0f;
        y = 0.0f;
        c = 0.0f;
        t = NULL;
    }
    GameTexture t;
    float w;
    float h;
    float x;
    float y;
    float c;
}FontGraphObject;

class FontObject
{
public:
    FontObject(const std::string& strFontName,
                       int nFaceSize,
                       bool bBold = false,
                       bool bItalic = false,
                       bool bAntialias = true);

    virtual ~FontObject();

    virtual void Print( float x, float y, const char *format, ... );

    virtual void Render(float x, float y, const std::string& strText);

    virtual void SetColor( DWORD dwColor, int i = -1 );

    virtual DWORD GetColor( int i = 0 ) const;

    virtual void SetKerningWidth( float kerning );

    virtual void SetKerningHeight( float kerning );

    virtual float GetKerningWidth();

    virtual int TextKerningWidth(const std::string& strText);

    virtual float GetKerningHeight();

    virtual float GetFontSize();

public:
    inline void CacheCharacter(unsigned int idx, wchar_t c);

    inline float GetWidthFromCharacter( wchar_t c, bool original = false );

    unsigned int GetGlyphByCharacter( wchar_t c );

private:
    HDC m_Hdc;
    FontGraphObject m_Glyphs[Font_Count];
    HFONT m_hFont;
    UINT m_nAntialias;
    long m_nAscent;
    float m_nFontSize;
    float m_nKerningWidth;
    float m_nKerningHeight;
    GraphicsEngine* m_Graphics;
    hgeSprite* m_pSprite;
};

#endif