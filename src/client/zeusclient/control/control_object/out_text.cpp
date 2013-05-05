#include "out_text.h"
#include <cstdio>

int PrintText::m_Pos = 0;

PrintTextFont* PrintText::m_Font = NULL;

bool PrintText::Print(float x, float y,
        TextRect rect, char* strText, ...)
{
    //无资源池 暂时这样
    int nBufferLen = strlen(strText) + 80;
    char* szBuffer = new char[nBufferLen];
    memset(szBuffer, 0, nBufferLen);
    m_Font = new PrintTextFont("res\\font1.fnt");

    va_list argptr;  //参数列表
    va_start(argptr,strText);
    vsprintf_s(szBuffer , nBufferLen, strText, argptr);
    m_Font->printf(x, y, rect, szBuffer);
    va_end(argptr);
    if (m_Font)
    {
        delete m_Font;
    }
    if (szBuffer)
    {
        delete[] szBuffer;
    }
    return true;
}