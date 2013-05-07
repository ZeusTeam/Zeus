#include "globaldef.h"
#include "about_scene.h"
AboutScene::AboutScene()
{
    m_bg = PicturePool::Instance()->Get("aboutbg");
}

AboutScene::~AboutScene()
{
}
void AboutScene::Update()
{
    if (InputEngine::Instance()->IsKey(KEY_ESCAPE) == Key_Down)
    {
        SceneEngine_->Pop();
    }
}
void AboutScene::Output()
{
    if (m_bg)
    {
        m_bg->Render(0, 0);
    }
}
void AboutScene::Reset()
{
    GraphicsEngine::Instance()->Clear(ARGB(1,0,0,0));
}