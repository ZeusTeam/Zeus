#include "globaldef.h"
#include "input_Engine.h"

template<> InputEngine* Singleton<InputEngine>::m_pInst = NULL;

InputEngine::InputEngine()
{
    m_Key = Direction_Tail;
    m_GameEngine_Ptr = NULL;
}

InputEngine::~InputEngine()
{
}

bool InputEngine::Initialize(GameEngine* pGameEngine)
{
    m_GameEngine_Ptr = pGameEngine;
    if (!m_GameEngine_Ptr)
    {
        return false;
    }
    return true;
}

KeyState InputEngine::IsKey(int nKey)
{
    if (!m_GameEngine_Ptr)
    {
        return Key_Fail;
    }
    if (m_GameEngine_Ptr->Input_GetKeyState(nKey))
    {
        return Key_Down;
    }
    return Key_Up;
}

KeyState InputEngine::IsKey(int nFirstKey, int nSecondKey)
{
    if (!m_GameEngine_Ptr)
    {
        return Key_Fail;
    }
    if (m_GameEngine_Ptr->Input_GetKeyState(nFirstKey))
    {
        if (m_GameEngine_Ptr->Input_GetKeyState(nSecondKey))
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