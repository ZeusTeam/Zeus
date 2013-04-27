#include "people.h"

People::People(float x, float y)
    : SpriteBase(x, y)
    , m_HP(0)
    , m_HPMax(0)
    , m_MP(0)
    , m_MPMax(0)
{
}

People::~People()
{
}

bool People::LoadPeopleImage(const std::string& strPath,
        int nFrame, int nWidth, int nHeight)
{
    if (strPath.empty())
    {
        return false;
    }
    m_nFrameCount = nFrame;
    m_nWidth = nWidth;
    m_nHeight = nHeight;
    for (int index = 0; index < Direction_Tail; index++)
    {
        m_DirectionTex[index].LoadFrame(strPath, (float)index * nHeight,
            (float)nWidth, (float)nHeight);
    }
    return true;
}