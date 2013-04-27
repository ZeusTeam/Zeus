#ifndef GAME_MAP
#define GAME_MAP
#include "control/controlobject/texture.h"
#include "globaldef.h"
#include "import\hge\include\hgeVector.h"

#include <string>
#include <vector>
using namespace std;

typedef hgeVector roleVector;
typedef unsigned long DWORD;

class CoveringTex
    :public Texture
{
public:

    bool Load(string texPath, float x, float y)
    {
        if (Texture::Load(texPath, 0, 0))
        {
            if ( x <= GetWidth() && x > 0 && y <= GetHeight() && y > 0)
            {
                m_x = x;
                m_y = y;
                return true;
            }
            else
            {
                return false;
            }
        }
        else //Load失败
        {
            return false;
        }
    }

    void Render()
    {
        Texture::Render(m_x, m_y);
    }

    CoveringTex(){}
    virtual ~CoveringTex()
    {

    }
private:
    float m_x;
    float m_y;
};

class GameMap
{
public:
    
    GameMap();
    virtual ~GameMap();


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

    //判断是否会碰撞到地图
    bool isCollision(roleVector v, DWORD color);    ///int roleSpeed, DWORD color);
private:

    Texture m_mapTex;
    Texture m_collisionMapTex;
    vector<CoveringTex*> m_coveringTex;
};


#endif