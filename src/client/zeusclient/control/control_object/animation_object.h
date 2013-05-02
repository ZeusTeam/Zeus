#ifndef ANIMATION_OBJECT_
#define ANIMATION_OBJECT_
#include "import\hge\include\hge.h"
#include "import\hge\include\hgeanim.h"
#include <string>

class AnimationObject
{
public:
    AnimationObject();
    virtual ~AnimationObject();
    bool Load(const std::string path
        ,  int frames                   //总帧数
        ,  float FPS                    //动画播放速度 帧/秒
        ,  float x                      //第一帧坐标
        ,  float y
        ,  float w                      //每帧大小
        ,  float h
        );

    void SetFrame(int index);
    int  GetCurrentFrame(); //失败返回-1
    void Play(int start, int end, bool loop);
    void Stop();
    void Update();
    void SetFPS(float FPS);
    void Render(float x, float y);

private:
    hgeAnimation* m_animation;
    HTEXTURE m_hTex;
    int m_start;            //开始的帧
    int m_end;              //结束的帧
};


#endif