#ifndef OBJECT_
#define OBJECT_

#define ElapsedTime 0.0166666f

typedef enum _PeopleDirection
{
    Direction_Left,
    Direction_LeftUp,
    Direction_Up,
    Direction_RightUp,
    Direction_Right,
    Direction_RightDown,
    Direction_Down,
    Direction_LeftDown,
    Direction_Tail,
}PeopleDirection;

typedef enum _RollBorder
{
    Border_NULL,
    Border_Top,
    Border_Left,
    Border_Bottom,
    Border_Right,
}RollBorder;

class ISprite
{
public:
    ISprite() {}
    virtual ~ISprite() {}

    virtual void Render() = 0;

    virtual void Update() = 0;

    virtual bool IsVaild() = 0;
};


class SpriteBase : public ISprite
{
public:
    //����λ��
    SpriteBase(float x = 0, float y = 0)
        : m_nPosX(x)
        , m_nPosY(y)
        , m_bIsVisible(true)
    {
        m_nFrameStartX      = 0;
        m_nCurrentFrame     = 0;
        m_nWidth            = 0;
        m_nHeight           = 0;
        m_nFrameCount       = 0;
    }
    virtual ~SpriteBase() {}

public:

    //����Ϊ���úͻ�ȡλ�ú���
    float GetX(){ return m_nPosX; }
    float GetY(){ return m_nPosY; }
    void SetX(float x){ m_nPosX = x; }
    void SetY(float y){ m_nPosY = y; }

protected:
    float     m_nPosX;
    float     m_nPosY;
    int     m_nFrameStartX;     //ͼƬ��ʼ��ͼ��X����
    int     m_nCurrentFrame;    //��ǰ֡
    int     m_nSpeed;           //�����ٶ�
    int     m_nFrameCount;      //֡������һ���ӵ��м���ͼ��
    int     m_nWidth;
    int     m_nHeight;
    float   m_fAngle;
    bool    m_bIsVisible;
};

#endif