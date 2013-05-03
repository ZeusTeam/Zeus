#ifndef TEXTUTEENGINE_
#define TEXTUTEENGINE_

#include "iengine.h"
#include "include\utils\singleton.h"
#include "engine\game_engine.h"
#include <string>

class TextureEngine
    : public Singleton<TextureEngine>
    , public IEngine
{
    friend class Singleton<TextureEngine>;
public:
    TextureEngine();
    virtual ~TextureEngine();

    bool Initialize() { return false; }

    bool Initialize(GameEngine* pGameEngine);

public:
    GameTexture Load(const std::string& path);

    int GetWidth(GameTexture tex);

    int GetHeight(GameTexture tex);

    void Release(GameTexture tex);

    DWORD* Lock(GameTexture tex,
                      bool bReadOnly = true,
                      int left = 0,
                      int top = 0,
                      int width = 0,
                      int height = 0);
    void Unlock(GameTexture tex);

public:
    GameEngine* m_GameEngine_Ptr;
};

#endif