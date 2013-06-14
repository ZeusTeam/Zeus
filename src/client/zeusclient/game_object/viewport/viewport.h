#ifndef VIEWPORT_
#define VIEWPORT_
#include "include\utils\Singleton.h"
#include "import\hge\include\hgevector.h"

typedef hgeVector viewportVector;

class Viewport
    : public Singleton<Viewport>
{
public:
    Viewport();
    ~Viewport();

    //取视口坐标向量
    viewportVector GetPos();
    void SetPos(float x, float y);

private:
    viewportVector m_pos;
};
#endif