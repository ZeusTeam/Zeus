#ifndef CREATEPLAYER_SCENE_
#define CREATEPLAYER_SCENE_

#include "scene.h"
#include "game_object\gui\editbox\edit_box.h"
#include "import\hge\include\hgegui.h"
#include "control\control_object\texture_object.h"
#include "game_object\gui\button\button.h"
#include "game_object\gui\static_box\static_box.h"
#include "engine\input_engine.h"

class CreatePlayerScene
    : public Scene
{
public:
    CreatePlayerScene();
    virtual ~CreatePlayerScene();

    virtual void Update();
    virtual void Output();
    virtual void Reset();
    virtual void DisposeCtrl(int _Id);

    void ButtonCreate();
    void ButtonReturn();

private:
    hgeGUI m_Gui;
    EditBox* m_EditPlayerName;
    Button* m_ButtonCreate;
    Button* m_ButtonReturn;
    StaticBox* m_PlayMessage;
    StaticBox* m_PlayName;
    TextureObject* m_PlayerImage;
    InputEngine* m_InputEngine;
};

#endif