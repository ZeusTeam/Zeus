#ifndef PlayerRole_
#define PlayerRole_

#include "import\hge\include\hgevector.h"
#include "engine\input_engine.h"
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


protected:
    PeopleDirection m_Direction;
    int m_nPresentFrame;
    int m_nTimeFrame;
    bool m_bMoving;
    InputEngine* m_InputEngine;
};

#endif