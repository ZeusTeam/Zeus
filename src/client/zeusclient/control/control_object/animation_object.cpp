#include "globaldef.h"
#include "animation_object.h"
AnimationObject::AnimationObject()
    : m_start(0)
    , m_end(0)
    , m_hTex(NULL)
    , m_animation(NULL)
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
    if (m_animation)
    {
        m_animation->Render(x, y);
    }
}
bool AnimationObject::Load(const std::string path,  int frames, float FPS, float x, float y, float w, float h)
{
    m_hTex = hge->Texture_Load(path.c_str());
    if (m_hTex == NULL)
    {
        return false;
    }
    m_animation = new hgeAnimation(m_hTex, frames, FPS, x, y, w, h);
    if (m_animation)
    {
        return true;
    }
    return false;
}

void AnimationObject::SetFrame(int index)
{
    if (!m_animation)
    {
        return;
    }
    m_animation->SetFrame(index);
}
int AnimationObject::GetCurrentFrame()
{
    if (!m_animation)
    {
        return -1;
    }
    return m_animation->GetFrame();
}
void AnimationObject::Play(int start, int end, bool loop)
{
    if (!m_animation)
    {
        return;
    }
    if (start < 0 || start > end || end < 0 || end > m_animation->GetFrames())
    {
        return;
    }
    m_start = start;
    m_end = end;
    if (loop)
    {
        m_animation->SetMode(HGEANIM_LOOP|HGEANIM_FWD);
    }
    else
    {
        m_animation->SetMode(HGEANIM_NOLOOP|HGEANIM_FWD);
    }
    m_animation->SetFrame(start);
    m_animation->Play();
}
void AnimationObject::Stop()
{
    if (!m_animation)
    {
        return;
    }
    m_animation->Stop();
}
void AnimationObject::Update()
{
    if (!m_animation)
    {
        return;
    }
    if (m_animation->GetFrame() >= m_end)
    {
        m_animation->SetFrame(m_start);
    }
    m_animation->Update(hge->Timer_GetDelta());
}

void AnimationObject::SetFPS(float FPS)
{
    if (!m_animation)
    {
        return;
    }
    m_animation->SetSpeed(FPS);
}