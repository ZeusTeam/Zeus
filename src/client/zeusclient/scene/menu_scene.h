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

    ///> todo: 重载或者实现父类的函数，前面的virtual不要丢
    virtual void Update();
    void Output();
    void Reset();
private:
    StartMenu m_startMenu;
    TextureObject* m_bgRenderer;
};

#endif