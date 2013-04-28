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
#define ACCURACY 8              ///ͨ��n�������ж���ײ

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
        Texture::Render(m_x, m_y, 0, 0, 0, 0);
    }

    CoveringTex(){}
    virtual ~CoveringTex()
    {

    }
private:
    float m_x;          ///�ӿ�����
    float m_y;          
};

class GameMap
{
public:
    
    GameMap();
    virtual ~GameMap();

    bool SetViewport(float x, float y, float width, float height, roleVector rolePos);

    bool Load(string mapTex, string collisionMapTex);
    ///���Ƶ�ͼ
    void Render();

    void Render(roleVector rolePos);

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