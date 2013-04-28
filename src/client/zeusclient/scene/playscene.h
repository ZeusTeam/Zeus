#ifndef PLAY_SCENE
#define PLAY_SCENE

#include "import\hge\include\hgesprite.h"
#include "control/controlobject/texture.h"
#include "gameobject/people/playerrole.h"
#include "scene.h"
#include "gameobject/map/gamemap.h"
class PlayScene
    :public Scene
{
public:
    PlayScene();
    ~PlayScene();

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
};

#endif