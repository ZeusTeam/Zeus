#ifndef GFXENGINE_
#define GFXENGINE_

#include "include\utils\singleton.h"
#include "iengine.h"

class GraphicsEngine
    : public IEngine
    , public Singleton<GraphicsEngine>
{
    friend class Singleton<GraphicsEngine>;
public:
    GraphicsEngine();
    virtual ~GraphicsEngine();

    bool Initialize() { return false;}

    bool Initialize(GameEngine* pGameEngine);

public:
    void BeginScene();

    void EndScene();

    HDC WindowDC();

    void Clear(DWORD color);

    void RenderLine(float x1, float y1,
        float x2, float y2,
        DWORD color = 0xFFFFFFFF,
        float z = 0.5f);


    void RenderQuad(const hgeQuad *quad);

private:
    GameEngine* m_GameEngine_Ptr;
    HDC m_HDC;
};

#endif