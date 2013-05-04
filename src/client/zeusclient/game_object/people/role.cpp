#include "role.h"
#include "control\pool\picture_pool.h"

Role::Role(float x, float y)
    : SpriteBase(x, y)
    , m_HP(0)
    , m_HPMax(0)
    , m_MP(0)
    , m_MPMax(0)
{
}

Role::~Role()
{
}

bool Role::LoadRoleImage(const std::string& strId,
        int frames, float FPS, float x, float w, float h)
{
    m_nWidth = (int)w;
    m_nHeight = (int)h;
    for (int index = 0; index < Direction_Tail; index++)
    {
        m_animation[index].Load(
            strId, frames,
            FPS, x, index * h, w, h);
    }
    return NULL;
}