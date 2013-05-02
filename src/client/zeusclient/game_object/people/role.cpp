#include "role.h"

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

AnimationObject* Role::LoadRoleImage(const std::string& strPath,
        int frames, float FPS, float x, float y, float w, float h)
{
    if (m_roleAnimation.Load(strPath, frames, FPS, x, y, w, h))
        return &m_roleAnimation;
    return NULL;
}