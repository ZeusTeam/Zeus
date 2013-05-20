#ifndef ROLE_SELECT_SCENE_
#define ROLE_SELECT_SCENE_

#include "import\hge\include\hgegui.h"
#include "scene\play_scene.h"
#include "control/control_object/texture_object.h"
#include "control\control_object\font_object.h"
#include "game_object\gui\button\button.h"
#include "game_object\gui\image_box\image_box.h"
#include "game_object\gui\select_view\select_view.h"
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

protected:

    void OnReturnBtnClick();
    void OnCreateRoleBtnClick();
    void OnDeleteRoleBtnClick();
    void OnStartGameBtnClick();

private:
    hgeGUI m_gui;
    SelectView* m_selectView;
    ImageBox* m_roleBox1;
    ImageBox* m_roleBox2;
    ImageBox* m_roleBox3;
    Button* m_returnBtn;
    Button* m_createRoleBtn;
    Button* m_deleteRoleBtn;
    Button* m_startGameBtn;
};

#endif