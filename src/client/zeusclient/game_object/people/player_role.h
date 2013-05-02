#ifndef PlayerRole_
#define PlayerRole_
#include "import\hge\include\hgevector.h"
#include "role.h"

#define MOVEFRAMEMAX 5
#define ROLLBODERSPACE 100
typedef hgeVector roleVector;

class PlayerRole : public Role
{
public:
    PlayerRole(float x = 0, float y = 0);
    virtual ~PlayerRole();

    virtual void Render();

    virtual void Update();

    virtual bool IsVaild();

    virtual RollBorder IsRollBorder();

    virtual roleVector GetNextPos();

    virtual void MoveTo(roleVector);

    virtual int GetAreaRadins();        //以人物脚步中心画圆 表示人物占地面积

    virtual void Stop();

    virtual roleVector GetPos();

    virtual void SetViewport(roleVector v);

protected:

    AnimationObject* m_animation;
    PeopleDirection m_Direction;
    PeopleDirection m_LastDir;
    bool m_bMoving;
    roleVector m_viewportPos;
};

#endif