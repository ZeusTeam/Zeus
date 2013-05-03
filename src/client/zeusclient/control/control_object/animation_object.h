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
        , int frames                   //总帧数
        , float FPS                    //动画播放速度 帧/秒
        , float x                      //第一帧坐标
        , float y
        , float w                      //每帧大小
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
    int m_start;            //开始的帧
    int m_present;          //进行中的帧
    int m_end;              //结束的帧
    int m_fps;
    int m_fps_present;
    int m_frame;
    bool m_is_play;
    bool m_is_loop;
    bool m_is_playframe;
};


#endif