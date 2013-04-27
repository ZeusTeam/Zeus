#include "globaldef.h"
#include "playerrole.h"

PlayerRole::PlayerRole(float x, float y)
    : People(x, y)
    , m_Direction(Direction_Up)
{
    LoadPeopleImage("res\\img\\self.png", 8, 128, 128);
    m_nSpeed = 3;
    m_nPresentFrame = 0;
    m_nTimeFrame = 0;
}

PlayerRole::~PlayerRole()
{
}

void PlayerRole::Render()
{
    m_DirectionTex[m_Direction].RenderFrame(
        m_nPresentFrame,
        (float)m_nPosX - m_nWidth / 2,
        (float)m_nPosY - m_nHeight / 2); /// 绘制在左上角 坐标表示中心
}


void PlayerRole::Update()
{
    if (m_nPresentFrame == m_nFrameCount)
    {
        m_nPresentFrame = 0;
    }
    if (m_nTimeFrame >= MOVEFRAMEMAX)
    {
        m_nPresentFrame++;
        m_nTimeFrame = 0;
    }
}

bool PlayerRole::IsVaild()
{
    return true;
}

roleVector PlayerRole::GetNextPos()
{
    roleVector nextPos(m_nPosX, m_nPosY);

    if (InputEngine_->IsKey(KEY_UP) == Key_Down && 
        InputEngine_->IsKey(KEY_LEFT) != Key_Down &&
        InputEngine_->IsKey(KEY_RIGHT) != Key_Down) ///向上走
    {
        m_Direction = Direction_Up;
        nextPos.y = m_nPosY - m_nSpeed;
        ++m_nTimeFrame;
    }
    if (InputEngine_->IsKey(KEY_DOWN) == Key_Down && 
        InputEngine_->IsKey(KEY_LEFT) != Key_Down &&
        InputEngine_->IsKey(KEY_RIGHT) != Key_Down) ///向下走
    {
        m_Direction = Direction_Down;
        nextPos.y = m_nPosY + m_nSpeed;
        ++m_nTimeFrame;
    }
    if (InputEngine_->IsKey(KEY_LEFT) == Key_Down && 
        InputEngine_->IsKey(KEY_DOWN) != Key_Down &&
        InputEngine_->IsKey(KEY_UP) != Key_Down) ///向左走
    {
        m_Direction = Direction_Left;
        nextPos.x = m_nPosX - m_nSpeed;
        ++m_nTimeFrame;
    }
    if (InputEngine_->IsKey(KEY_RIGHT) == Key_Down && 
        InputEngine_->IsKey(KEY_DOWN) != Key_Down &&
        InputEngine_->IsKey(KEY_UP) != Key_Down) ///向右走
    {
        m_Direction = Direction_Right;
        nextPos.x = m_nPosX + m_nSpeed;
        ++m_nTimeFrame;
    }
    if (InputEngine_->IsKey(KEY_UP) == Key_Down && 
        InputEngine_->IsKey(KEY_LEFT) == Key_Down) ///向左上走
    {
        m_Direction = Direction_LeftUp;
        nextPos.x = m_nPosX - 0.707f * m_nSpeed; /// cos45° = 0.707
        nextPos.y = m_nPosY - 0.707f * m_nSpeed;
        ++m_nTimeFrame;
    }
    if (InputEngine_->IsKey(KEY_UP) == Key_Down && 
        InputEngine_->IsKey(KEY_RIGHT) == Key_Down) ///向右上走
    {
        m_Direction = Direction_RightUp;
        nextPos.x = m_nPosX + 0.707f * m_nSpeed; /// cos45° = 0.707
        nextPos.y = m_nPosY - 0.707f * m_nSpeed;
        ++m_nTimeFrame;
    }
    if (InputEngine_->IsKey(KEY_DOWN) == Key_Down && 
        InputEngine_->IsKey(KEY_LEFT) == Key_Down) ///向左下走
    {
        m_Direction = Direction_LeftDown;
        nextPos.x = m_nPosX - 0.707f * m_nSpeed; /// cos45° = 0.707
        nextPos.y = m_nPosY + 0.707f * m_nSpeed;
        ++m_nTimeFrame;
    }
    if (InputEngine_->IsKey(KEY_DOWN) == Key_Down && 
        InputEngine_->IsKey(KEY_RIGHT) == Key_Down) ///向右下走
    {
        m_Direction = Direction_RightDown;
        nextPos.x = m_nPosX + 0.707f * m_nSpeed; /// cos45° = 0.707
        nextPos.y = m_nPosY + 0.707f * m_nSpeed;
        ++m_nTimeFrame;
    }
    return nextPos;
}

void PlayerRole::MoveTo(roleVector v)
{
    m_nPosX = v.x;
    m_nPosY = v.y;
}