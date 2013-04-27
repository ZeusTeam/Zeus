#ifndef PEOPLE_
#define PEOPLE_

#include "gameobject\sprite.h"
#include "control/controlobject/texture.h"
#include <string>

class People : public SpriteBase
{
public:
    People(float x = 0, float y = 0);
    virtual ~People();

    virtual bool LoadPeopleImage(const std::string& strPath,
        int nFrame, int nWidth, int nHeight);

    virtual bool IsVaild() {return true;}

protected:
    int m_HP;
    int m_HPMax;
    int m_MP;
    int m_MPMax;
    Texture m_DirectionTex[Direction_Tail];
};

#endif