#include "globaldef.h"
#include "animation_object.h"

AnimationObject::AnimationObject()
    : m_start(0)
    , m_end(0)
    , m_frame(0)
    , m_present(0)
    , m_fps(0)
    , m_fps_present(0)
    , m_animation(NULL)
    , m_is_play(false)
    , m_is_loop(false)
    , m_is_playframe(false)
{
}

AnimationObject::~AnimationObject()
{
    if (m_animation)
    {
        delete m_animation;
        m_animation = NULL;
    }
}
void AnimationObject::Render(float x, float y)
{
    if (m_vecFrameSprite.empty() || (int)m_vecFrameSprite.size() > m_present)
    {
        m_vecFrameSprite[m_present]->Render(x, y);
    }
}

bool AnimationObject::Load(const std::string path, int frames,float FPS,
                           float x, float y, float w, float h)
{
    m_hTex.Load(path);
    for (int index = 0; index < frames; index++)
    {
        m_vecFrameSprite.push_back(
            new hgeSprite(m_hTex.GetObject(), index * w, y, w, h));
    }
    m_frame = m_vecFrameSprite.size();
    m_fps = (int)FPS;
    return true;
}

int AnimationObject::CurrentFrame()
{
    return m_present;
}

void AnimationObject::Play(int start, int end, bool loop)
{
    if (start < 0 || start > end || end < 0)
    {
        return;
    }
    m_start = start;
    m_present = start;
    m_end = end;
    m_is_play = true;
    m_is_loop = loop;
    m_is_playframe = false;
}

void AnimationObject::PlayFrame(int frame)
{
    if (frame < 0 || frame > (int)m_vecFrameSprite.size())
    {
        return;
    }
    m_start = frame;
    m_present = frame;
    m_end = m_vecFrameSprite.size();
    m_is_playframe = true;
}

void AnimationObject::Stop()
{
    m_is_play = false;
}
void AnimationObject::Update()
{
    if (m_is_play)
    {
        if (m_fps_present >= m_fps)
        {
            if (m_present < m_end)
            {
                if (!m_is_playframe)
                {
                    m_present++;
                }
            }
            else
            {
                if (m_is_loop)
                {
                    m_present = m_start;
                }
            }
            m_fps_present = 0;
        }
        else
        {
            m_fps_present++;
        }
    }
}

void AnimationObject::SetFPS(int FPS)
{
    m_fps = FPS;
}

int AnimationObject::GetFPS()
{
    return m_fps;
}

int AnimationObject::PresentFPS()
{
    return m_fps_present;
}

int AnimationObject::GetFrames()
{
    return m_frame;
}