#ifndef IENGINE_
#define IENGINE_

#include "game_engine.h"

class IEngine
{
public:
    IEngine() {}
    virtual ~IEngine() {}

public:

    virtual bool Initialize(GameEngine* engine) = 0;

};

#endif