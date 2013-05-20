#ifndef IMAGE_BOX_
#define IMAGE_BOX_
#include "game_object\gui\gui_item.h"
#include "control\control_object\texture_object.h"
#include <string>
#include "control\pool\picture_pool.h"

class ImageBox
    : public GUIItem
{
public:
    ImageBox(int _id, float x, float y, const std::string normalTexID);
    
    ~ImageBox();

    virtual void Render();

    void SetTexture(const std::string focusTexID) { m_tex = PicturePool::Instance()->Get(focusTexID); }
    void SetPos(float x, float y) { m_x = x; m_y = y; }
    float GetX() const { return m_x; }
    float GetY() const { return m_y; }

private:
    TextureObject* m_tex;
    float m_x;
    float m_y;
};


#endif