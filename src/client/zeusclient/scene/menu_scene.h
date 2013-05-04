#ifndef MENU_SCENE
#define MENU_SCENE

#include "import\hge\include\hgesprite.h"
#include "control/control_object/texture_object.h"
#include "scene.h"

class MenuScene
    :public Scene
{
public:
    MenuScene();
    ~MenuScene();
    void Update();
    void Output();
    void Reset();
private:
    TextureObject* m_bgRenderer;
};

#endif