#ifndef ROLE_SELECT_SCENE_
#define ROLE_SELECT_SCENE_

#include "game_object\gui\role_select\role_select.h"
#include "scene\play_scene.h"
#include "control/control_object/texture_object.h"
#include "scene.h"

class RoleSelectScene
    :public Scene
{
public:
    RoleSelectScene();
    ~RoleSelectScene();

    virtual void Update();
    virtual void Output();
    virtual void Reset();
private:
    RoleSelect m_roleSelectGUI;
};

#endif