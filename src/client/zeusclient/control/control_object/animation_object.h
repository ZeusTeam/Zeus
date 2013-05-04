#ifndef ANIMATION_OBJECT_
#define ANIMATION_OBJECT_

#include "import\hge\include\hge.h"
#include "import\hge\include\hgesprite.h"
#include "texture_object.h"
#include <string>
#include <vector>

typedef std::vector<hgeSprite*> AnimationFrame;

class AnimationObject
{
public:
    AnimationObject();
    virtual ~AnimationObject();

    void Render(float x, float y);
    void Update();

    bool Load(const std::string path
        , int frames                   //��֡��
        , float FPS                    //���������ٶ� ֡/��
        , float x                      //��һ֡����
        , float y
        , float w                      //ÿ֡��С
        , float h
        );

    int  CurrentFrame();
    void Play(int start, int end, bool loop);
    void PlayFrame(int frame);
    void Stop();

    void SetFPS(int FPS);
    int GetFPS();
    int PresentFPS();

private:
    hgeSprite* m_animation;
    AnimationFrame m_vecFrameSprite;
    TextureObject m_hTex;
    int m_start;            //��ʼ��֡
    int m_present;          //�����е�֡
    int m_end;              //������֡
    int m_fps;
    int m_fps_present;
    int m_frame;
    bool m_is_play;
    bool m_is_loop;
    bool m_is_playframe;
};


#endif