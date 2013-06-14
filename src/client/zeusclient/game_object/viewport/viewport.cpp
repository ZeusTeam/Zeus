#include "viewport.h"
#include "globaldef.h"

Viewport* Singleton<Viewport>::m_pInst = NULL;

Viewport::Viewport()
{
}

Viewport::~Viewport()
{
}

viewportVector Viewport::GetPos()
{
   return m_pos;
}

void Viewport::SetPos(float x, float y)
{
    m_pos.x = x;
    m_pos.y = y;
}
