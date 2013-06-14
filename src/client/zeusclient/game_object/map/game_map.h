#ifndef GAME_MAP
#define GAME_MAP
#include "control/control_object/texture_object.h"
#include "globaldef.h"
#include "import\hge\include\hgeVector.h"
#include "import\hge\include\hgefont.h"

#include <string>
#include <vector>
using namespace std;

typedef hgeVector roleVector;

typedef unsigned long DWORD;
#define ACCURACY 8              ///通过n个点来判断碰撞

class CoveringTex
    : public TextureObject
{
public:
    
    bool Load(string texPath, float x, float y);

    void Render();

    CoveringTex() {}
    virtual ~CoveringTex() {}
private:
    float m_x;          ///相对于地图的坐标
    float m_y;          
};

class GameMap
{
public:
    
    GameMap();
    virtual ~GameMap();

    ///从ZeusMap文件中读取地图信息
    bool LoadFromZMap(string zMap);

    bool Load(string mapTex, string collisionMapTex);
    ///绘制地图

    void Render();

    ///绘制遮盖角色的部分 应该在角色绘制之后调用
    void RenderCovering();

    ///添加遮掩物
    bool PushCovering(string path, float x, float y);

    ///移除遮掩物
    void PopCovering();
    
    void PopCoveringAll();

    ///地图宽度
    float GetWidth() { return m_mapTex->GetWidth();}
    
    ///地图高度
    float GetHeight() { return m_mapTex->GetHeight();}

    //判断是否会碰撞到地图
    bool isCollision(roleVector v, int r, DWORD color);

private:
    TextureObject* m_mapTex;
    TextureObject* m_collisionMapTex;
    vector<CoveringTex*> m_coveringTex;
    roleVector m_previousPos;
};


#endif