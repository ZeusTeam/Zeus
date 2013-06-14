#include "globaldef.h"
#include "player_role.h"
#include "game_object\viewport\viewport.h"
PlayerRole::PlayerRole(float x, float y)
    : Role(x, y)
    , m_Direction(Direction_Up)
{
    LoadRoleImage("res\\img\\self.png", 8, MOVEFRAMEMAX, 0, 128, 128);
    m_nSpeed = 3;
    m_nPresentFrame = 0;
    m_nTimeFrame = 0;
    m_nFrameCount = 8 - 1;
    m_InputEngine = InputEngine::Instance();
}

PlayerRole::~PlayerRole()
{
}

void PlayerRole::Render()
{
    /// 世界坐标转换为视口坐标 同时将坐标计算到左上角
    viewportVector viewportPos = Viewport::Instance()->GetPos();
    m_animation[m_Direction].Render(
        (float)m_nPosX - viewportPos.x - m_nWidth / 2,
        (float)m_nPosY - viewportPos.y - m_nHeight * 3 / 4);
}


void PlayerRole::Update()
{
    if (m_nPresentFrame != 0 || m_bMoving)///不动的时候恢复脚的动作
    {
        ++m_nTimeFrame;
    }
    if (m_nPresentFrame == m_nFrameCount)
    {
        m_nPresentFrame = 0;
    }
    if (m_nTimeFrame >= m_animation[m_Direction].GetFPS())
    {
        m_nPresentFrame++;
        m_nTimeFrame = 0;
    }
    m_bMoving  = false;
}

bool PlayerRole::IsVaild()
{
    return true;
}

roleVector PlayerRole::GetNextPos()
{
    roleVector nextPos(m_nPosX, m_nPosY);

    if (m_InputEngine->IsKey(KEY_UP) == Key_Down && 
        m_InputEngine->IsKey(KEY_LEFT) != Key_Down &&
        m_InputEngine->IsKey(KEY_RIGHT) != Key_Down) ///向上走
    {
        m_Direction = Direction_Up;
        nextPos.y = m_nPosY - m_nSpeed;
    }
    if (m_InputEngine->IsKey(KEY_DOWN) == Key_Down && 
        m_InputEngine->IsKey(KEY_LEFT) != Key_Down &&
        m_InputEngine->IsKey(KEY_RIGHT) != Key_Down) ///向下走
    {
        m_Direction = Direction_Down;
        nextPos.y = m_nPosY + m_nSpeed;
    }
    if (m_InputEngine->IsKey(KEY_LEFT) == Key_Down && 
        m_InputEngine->IsKey(KEY_DOWN) != Key_Down &&
        m_InputEngine->IsKey(KEY_UP) != Key_Down) ///向左走
    {
        m_Direction = Direction_Left;
        nextPos.x = m_nPosX - m_nSpeed;
    }
    if (m_InputEngine->IsKey(KEY_RIGHT) == Key_Down && 
        m_InputEngine->IsKey(KEY_DOWN) != Key_Down &&
        m_InputEngine->IsKey(KEY_UP) != Key_Down) ///向右走
    {
        m_Direction = Direction_Right;
        nextPos.x = m_nPosX + m_nSpeed;
    }
    if (m_InputEngine->IsKey(KEY_UP) == Key_Down && 
        m_InputEngine->IsKey(KEY_LEFT) == Key_Down) ///向左上走
    {
        m_Direction = Direction_LeftUp;
        nextPos.x = m_nPosX - 0.707f * m_nSpeed; /// cos45° = 0.707
        nextPos.y = m_nPosY - 0.707f * m_nSpeed;
    }
    if (m_InputEngine->IsKey(KEY_UP) == Key_Down && 
        m_InputEngine->IsKey(KEY_RIGHT) == Key_Down) ///向右上走
    {
        m_Direction = Direction_RightUp;
        nextPos.x = m_nPosX + 0.707f * m_nSpeed; /// cos45° = 0.707
        nextPos.y = m_nPosY - 0.707f * m_nSpeed;
    }
    if (m_InputEngine->IsKey(KEY_DOWN) == Key_Down && 
        m_InputEngine->IsKey(KEY_LEFT) == Key_Down) ///向左下走
    {
        m_Direction = Direction_LeftDown;
        nextPos.x = m_nPosX - 0.707f * m_nSpeed; /// cos45° = 0.707
        nextPos.y = m_nPosY + 0.707f * m_nSpeed;
    }
    if (m_InputEngine->IsKey(KEY_DOWN) == Key_Down && 
        m_InputEngine->IsKey(KEY_RIGHT) == Key_Down) ///向右下走
    {
        m_Direction = Direction_RightDown;
        nextPos.x = m_nPosX + 0.707f * m_nSpeed; /// cos45° = 0.707
        nextPos.y = m_nPosY + 0.707f * m_nSpeed;
    }
    m_animation[m_Direction].PlayFrame(m_nPresentFrame);
    return nextPos;
}

RollBorder PlayerRole::IsRollBorder()
{
    if ((WINDOW_WIDTH - ROLLBODERSPACE) <= m_nPosX)
    {
        return Border_Right;
    }
    else if ((WINDOW_HEIGHT - ROLLBODERSPACE) <= m_nPosY)
    {
        return Border_Bottom;
    }
    else if (m_nPosX <= ROLLBODERSPACE)
    {
        return Border_Left;
    }
    else if (m_nPosY <= ROLLBODERSPACE)
    {
        return Border_Top;
    }
    return Border_NULL;
}

void PlayerRole::MoveTo(roleVector v)
{
    if (m_nPosX != v.x || m_nPosY != v.y)
    {
        m_nPosX = v.x;
        m_nPosY = v.y;
        m_bMoving  = true;
        ///角色移动后 视口坐标跟着移动
        viewportVector v = Viewport::Instance()->GetPos(); 
        v.x = m_nPosX - WINDOW_WIDTH / 2;
        v.y = m_nPosY - WINDOW_HEIGHT /2;
        Viewport::Instance()->SetPos(v.x, v.y);
    }
}

int PlayerRole::GetAreaRadins()
{
    return m_nWidth / 16; ///人物所占面积的半径 根据人物的大小而不同 与 人物贴图宽度有关
}

void PlayerRole::Stop()
{
    m_bMoving = false;
}

roleVector PlayerRole::GetPos()
{
    roleVector v(m_nPosX, m_nPosY);
    return v;
}