#ifndef ABOUT_SCENE_
#define ABOUT_SCENE_
#include "scene.h"
#include "control\pool\picture_pool.h"
#include "control\control_object\texture_object.h"

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
    TextureObject * m_bg;
};


#endif