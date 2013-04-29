#ifndef OUTTEXT_
#define OUTTEXT_

#include "import\hge\include\hgefont.h"

typedef hgeFont PrintTextFont;

#include <string>

typedef enum _TextRect
{
    Text_Left,
    Text_Right,
    Text_Centre,
}TextRect;

class PrintText
{
public:
    PrintText();
    ~PrintText();

    static bool Print(int x, int y,
        TextRect rect, char*strText, ...);

private:
    static int m_Pos;
    static PrintTextFont* m_Font;
};

#endif