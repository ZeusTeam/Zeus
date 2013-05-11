#ifndef CREATEPLAYER_SCENE_
#define CREATEPLAYER_SCENE_

#include "scene.h"
#include "game_object\gui\editbox\edit_box.h"
#include "import\hge\include\hgegui.h"
#include "control\control_object\texture_object.h"
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

private:
    hgeGUI m_Gui;
    EditBox* m_EditPlayerName;
    TextureObject* m_PlayerImage;
    InputEngine* m_InputEngine;
};

#endif