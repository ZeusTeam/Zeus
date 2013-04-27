#ifndef PlayerRole_
#define PlayerRole_
#include "import\hge\include\hgevector.h"
#include "people.h"

#define MOVEFRAMEMAX 5
typedef hgeVector roleVector;

class PlayerRole : public People
{
public:
    PlayerRole(float x = 0, float y = 0);
    virtual ~PlayerRole();

    virtual void Render();

    virtual void Update();

    virtual bool IsVaild();

    virtual roleVector GetNextPos();

    virtual void MoveTo(roleVector);

protected:
    PeopleDirection m_Direction;
    int m_nPresentFrame;
    int m_nTimeFrame;
};

#endif