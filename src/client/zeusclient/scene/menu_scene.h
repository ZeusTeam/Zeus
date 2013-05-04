#ifndef MENU_SCENE
#define MENU_SCENE

#include "game_object\gui\start_menu\start_menu.h"
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
    StartMenu m_startMenu;
    TextureObject* m_bgRenderer;
};

#endif