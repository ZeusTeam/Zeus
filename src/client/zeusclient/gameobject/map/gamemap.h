#ifndef GAME_MAP
#define GAME_MAP
#include "control/controlobject/texture.h"
#include "globaldef.h"
#include "import\hge\include\hgeVector.h"
#include "import\hge\include\hgefont.h"

#include <string>
#include <vector>
using namespace std;

typedef hgeVector roleVector;
typedef hgeVector viewportVector;

typedef unsigned long DWORD;
#define ACCURACY 8              ///通过n个点来判断碰撞

class CoveringTex
    : public Texture
{
public:

    bool Load(string texPath, float x, float y)
    {
        if (Texture::Load(texPath, 0, 0))
        {
                m_x = x;
                m_y = y;
                return true;
        }
        else //Load失败
        {
            return false;
        }
    }

    void Render(viewportVector viewportPos)
    {
        ///这通过计算裁剪遮盖图片到屏幕上
        float x,y,tx,ty,w,h;
        x = m_x - viewportPos.x;        //在屏幕上的坐标
        y = m_y - viewportPos.y;
        tx = -x;                        //相对于纹理的坐标
        ty = -y;
        if (x < 0)
            x = 0;
        if (y < 0)
            y = 0;
        if (tx < 0)
            tx = 0;
        if (ty < 0)
            ty = 0;
        w = GetWidth() - tx;
        h = GetHeight() - ty;
        if (tx > GetWidth())
            w = 0;
        if (ty > GetHeight())
            h = 0;

        if (w > 0 && h > 0)
            Texture::Render(x, y, tx, ty, w, h);
    }

    CoveringTex(){}
    virtual ~CoveringTex()
    {

    }
private:
    float m_x;          ///相对于地图的坐标
    float m_y;          
};

class GameMap
{
public:
    
    GameMap();
    virtual ~GameMap();

    bool SetViewport(float x, float y, float width, float height, roleVector rolePos);

    bool Load(string mapTex, string collisionMapTex);
    ///绘制地图
    void Render();

    void Render(roleVector rolePos);

    ///绘制遮盖角色的部分 应该在角色绘制之后调用
    void RenderCovering();

    ///添加遮掩物
    bool PushCovering(string path, float x, float y);

    ///移除遮掩物
    void PopCovering();
    
    void PopCoveringAll();

    ///地图宽度
    float GetWidth() { return m_mapTex.GetWidth();}
    
    ///地图高度
    float GetHeight() { return m_mapTex.GetHeight();}

    //判断是否会碰撞到地图
    bool isCollision(roleVector v, int r, DWORD color);

    viewportVector GetViewportPos() { return m_viewportPos ;}
private:

    Texture m_mapTex;
    Texture m_collisionMapTex;
    vector<CoveringTex*> m_coveringTex;
    viewportVector m_viewportPos;
    roleVector m_previousPos;
    float m_viewportWidth;
    float m_viewportHeight;
    hgeFont* m_font;
};


#endif