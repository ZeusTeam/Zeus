#include "out_text.h"

int PrintText::m_Pos = 0;

PrintTextFont* PrintText::m_Font = NULL;

bool PrintText::Print(int x, int y,
        TextRect rect, char* strText, ...)
{
    //无资源池 暂时这样
    m_Font = new PrintTextFont("res\\font1.fnt");
    va_list argptr;  //参数列表
    va_start(argptr,strText);
    vsprintf_s(szBuffer , nBufferLen, strText, argptr);

    m_Font->printf(x, y, rect, szBuffer);


    va_end(argptr);
    delete m_Font;
    return true;
}