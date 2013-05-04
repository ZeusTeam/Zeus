#ifndef ROLE_
#define ROLE_

#include "game_object\sprite.h"
#include "control/control_object/animation_object.h"
#include <string>

class Role : public SpriteBase
{
public:
    Role(float x = 0, float y = 0);
    virtual ~Role();

    virtual bool LoadRoleImage(const std::string& strId,
        int frames, float FPS, float x, float w, float h);

    virtual bool IsVaild() {return true;}

protected:
    int m_HP;
    int m_HPMax;
    int m_MP;
    int m_MPMax;
    AnimationObject m_animation[Direction_Tail];
};

#endif