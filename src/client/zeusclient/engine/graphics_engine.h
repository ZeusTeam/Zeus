#ifndef GFXENGINE_
#define GFXENGINE_

#include "include\utils\singleton.h"
#include "iengine.h"

class GraphicsEngine
    : public Singleton<GraphicsEngine>
    , public IEngine
{
    friend class Singleton<GraphicsEngine>;
public:
    GraphicsEngine();
    virtual ~GraphicsEngine();

    bool Initialize() { return false;}

public:
    void BeginScene();

    void EndScene();

    HDC WindowDC();

    void Clear(DWORD color);

    void RenderLine(float x1, float y1,
        float x2, float y2,
        DWORD color = 0xFFFFFFFF,
        float z = 0.5f);

    void SetClipping( int x, int y, int w, int h);

    void SetClipping();

    void RenderQuad(const hgeQuad *quad);

private:
    GameEngine* m_GameEngine_Ptr;
    HDC m_HDC;
};

#endif