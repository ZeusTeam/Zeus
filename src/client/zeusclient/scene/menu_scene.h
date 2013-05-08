#ifndef MENU_SCENE
#define MENU_SCENE

#include "game_object\gui\start_menu\start_menu.h"
#include "scene\about_scene.h"
#include "control/control_object/texture_object.h"
#include "scene.h"

class MenuScene
    :public Scene
{
public:
    MenuScene();
    ~MenuScene();

    virtual void Update();
    virtual void Output();
    virtual void Reset();
private:
    StartMenu m_startMenu;
    TextureObject* m_bgRenderer;
};

#endif