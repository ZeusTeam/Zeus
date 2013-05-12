#ifndef INPUTENGINE_
#define INPUTENGINE_

#include "include\utils\singleton.h"
#include "import\hge\include\hge.h"
#include "iengine.h"
#include "game_object\sprite.h"
#include <vector>

typedef enum _KeyState
{
    Key_Down,
    Key_Up,
    Key_Fail,
}KeyState;

class InputEngine
    : public Singleton<InputEngine>
    , public IEngine
{
    friend class Singleton<Singleton>;
public:
    InputEngine();
    virtual ~InputEngine();

    virtual bool Initialize() {return false;};

    PeopleDirection Get() const;

    KeyState IsKey(int nKey);

    KeyState IsKey(int nFirstKey, int nSecondKey);

    void Update();

private:
    PeopleDirection m_Key;
    GameEngine* m_GameEngine_Ptr;
};

#endif