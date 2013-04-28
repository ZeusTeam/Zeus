#include "gamemap.h"
#include <math.h>

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

///���Ƶ�ͼ
void GameMap::Render()
{
    m_mapTex.Render(0, 0);
}

void GameMap::Render(float x, float y)
{
    m_mapTex.Render(x, y);
}

///�����ڸǽ�ɫ�Ĳ��� Ӧ���ڽ�ɫ����֮�����
void GameMap::RenderCovering()
{
    for (int i = 0; i < (int)m_coveringTex.size(); i++)
    {
        m_coveringTex[i]->Render();
    }
}

///���������
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

///�Ƴ�������
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
                          int r, ///��λ��ռ����İ뾶
                          DWORD color ///��ײ����ɫ
                          )
{
    for (int i = 0; i < ACCURACY; i++)
    {
        DWORD* pClr = m_collisionMapTex.CheckColor(\
            nextPos.x + sin(2 * PI * i / ACCURACY) * r, 
            nextPos.y + cos(2 * PI * i / ACCURACY) * r, 1, 1);
        if (!pClr)
        {
            return true;
        }
        if (*pClr == color)
        {
            return true;
        }
    }
    return false;
}