#ifndef ABOUT_SCENE_
#define ABOUT_SCENE_
#include "scene.h"

class AboutScene
    : public Scene
{
public:
    AboutScene();
    ~AboutScene();

    void Update();
    void Output();
    void Reset();

private:

};


#endif