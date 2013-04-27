#include "gamemap.h"

GameMap::GameMap()
{

}
bool GameMap::Load(string mapTex, string collisionMapTex)
{
    if (!m_mapTex.Load(mapTex, 0, 0))
    {
        return false;
    }
    if (!m_collisionMapTex.Load(collisionMapTex, 0, 0))
    {
        return false;
    }
    return true;
}
GameMap::~GameMap()
{
    for (int i = 0; i < (int)m_coveringTex.size(); i++)
    {
        delete m_coveringTex[i];
    }
}

///绘制地图
void GameMap::Render()
{
    m_mapTex.Render(0, 0);
}

///绘制遮盖角色的部分 应该在角色绘制之后调用
void GameMap::RenderCovering()
{
    for (int i = 0; i < (int)m_coveringTex.size(); i++)
    {
        m_coveringTex[i]->Render();
    }
}

///添加遮掩物
bool GameMap::PushCovering(string path, float x, float y)
{
    CoveringTex* tex = new CoveringTex;
    if (!tex->Load(path, x, y))
    {
        delete tex;
        return false;
    }
    m_coveringTex.push_back(tex);
    return true;

}

///移除遮掩物
void GameMap::PopCovering()
{
    if (m_coveringTex.size() > 0)
    {
        m_coveringTex.pop_back();
    }
}

    
void GameMap::PopCoveringAll()
{
    if (m_coveringTex.size() > 0)
    {
        m_coveringTex.clear();
    }
}

bool GameMap::isCollision(roleVector nextPos, 
                          ///int roleSpeed, ///每帧移动的像素数
                          DWORD color ///碰撞的颜色
                          )
{
    DWORD* pClr = m_collisionMapTex.CheckColor(nextPos.x , nextPos.y, 1, 1);
    if (!pClr)
    {
        return true;
    }
    if (*pClr == color)
    {
        return true;
    }
    return false;
}