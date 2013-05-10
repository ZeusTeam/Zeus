#ifndef PLAY_SCENE
#define PLAY_SCENE

#include "import\hge\include\hgesprite.h"
#include "control/control_object/texture_object.h"
#include "game_object/people/player_role.h"
#include "scene.h"
#include "game_object/map/game_map.h"
#include "control\control_object\font_object.h"
#include "game_object\gui\editbox\edit_box.h"
#include "import\hge\include\hgegui.h"

class PlayScene
    : public Scene
{
public:
    PlayScene();
    virtual ~PlayScene();

    void Update();
    void Output();
    void Reset();
private:

    void _RollMap(roleVector& nextPos);

    float m_MapX;
    float m_MapY;
    int m_ViewPosX;
    int m_ViewPosY;
    GameMap* m_Map;
    PlayerRole* m_PlayerRole;
    FontObject* m_Font;
    EditBox* m_Edit;
    hgeGUI m_Gui;
};

#endif