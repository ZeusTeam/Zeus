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
    : public Texture
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
        else //Loadʧ��
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
    ///���Ƶ�ͼ
    void Render();

    void Render(float x, float y);

    ///�����ڸǽ�ɫ�Ĳ��� Ӧ���ڽ�ɫ����֮�����
    void RenderCovering();

    ///���������
    bool PushCovering(string path, float x, float y);

    ///�Ƴ�������
    void PopCovering();
    
    void PopCoveringAll();

    ///��ͼ���
    float GetWidth() { return m_mapTex.GetWidth();}
    
    ///��ͼ�߶�
    float GetHeight() { return m_mapTex.GetHeight();}

    //�ж��Ƿ����ײ����ͼ
    bool isCollision(roleVector v, DWORD color);    ///int roleSpeed, DWORD color);
private:

    Texture m_mapTex;
    Texture m_collisionMapTex;
    vector<CoveringTex*> m_coveringTex;
};


#endif