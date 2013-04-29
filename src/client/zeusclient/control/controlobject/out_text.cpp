#include "out_text.h"

int PrintText::m_Pos = 0;

PrintTextFont* PrintText::m_Font = NULL;

bool PrintText::Print(int x, int y,
        TextRect rect, char* strText, ...)
{
    //����Դ�� ��ʱ����
    m_Font = new PrintTextFont("res\\font1.fnt");
    va_list argptr;  //�����б�
    va_start(argptr,strText);
    m_Font->printf(x, y, rect, strText, argptr);
    va_end(argptr);
    delete m_Font;
    return true;
}