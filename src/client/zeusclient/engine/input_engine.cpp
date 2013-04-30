#include "globaldef.h"
#include "input_Engine.h"

template<> InputEngine* Singleton<InputEngine>::m_pInst = NULL;

InputEngine::InputEngine()
{
    m_Key = Direction_Tail;
    m_HGE = NULL;
}

InputEngine::~InputEngine()
{
}

bool InputEngine::Initialize(HGE* pHGE)
{
    m_HGE = pHGE;
    if (!m_HGE)
    {
        return false;
    }
    return true;
}

KeyState InputEngine::IsKey(int nKey)
{
    if (!m_HGE)
    {
        return Key_Fail;
    }
    if (m_HGE->Input_GetKeyState(nKey))
    {
        return Key_Down;
    }
    return Key_Up;
}

KeyState InputEngine::IsKey(int nFirstKey, int nSecondKey)
{
    if (!m_HGE)
    {
        return Key_Fail;
    }
    if (m_HGE->Input_GetKeyState(nFirstKey))
    {
        if (m_HGE->Input_GetKeyState(nSecondKey))
        {
            return Key_Down;
        }
    }
    return Key_Up;
}

PeopleDirection InputEngine::Get() const
{
    return m_Key;
}

void InputEngine::Update()
{

}