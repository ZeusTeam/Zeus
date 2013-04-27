#include "globaldef.h"
#include "menuscene.h"
#include "playscene.h"

MenuScene::MenuScene()
{
    m_bgTexture.Load("res\\img\\menubg.png", 0, 0);
    m_bgMusic = hge->Effect_Load("res\\music\\bg.mp3");
    hge->Effect_PlayEx(m_bgMusic, 100, 0, 1.0, true);
}

MenuScene::~MenuScene()
{
    hge->Channel_Stop(m_bgMusic);
    hge->Effect_Free(m_bgMusic);
}

void MenuScene::Reset()
{
}

void MenuScene::Output()
{
    m_bgTexture.Render(0,0);
}

void MenuScene::Update()
{
    if (hge->Input_GetKeyState(KEY_ESCAPE))
    {
        SceneEngine_->Pop();
    }
    if (hge->Input_GetKeyState(KEY_ENTER))
    {
        SceneEngine_->Pop();
        SceneEngine_->Push(new PlayScene);
    }
}