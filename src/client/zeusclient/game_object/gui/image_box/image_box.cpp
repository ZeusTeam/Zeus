#include "image_box.h"


ImageBox::ImageBox(int _id, float x, float y, const std::string normalTexID)
    : m_x(x)
    , m_y(y)
{
    this->id = _id;
    this->bEnabled = true;
    this->bStatic = false;
    this->bVisible = true;

    m_tex = PicturePool::Instance()->Get(normalTexID);
    if (m_tex) 
    {
        this->rect.Set(x, y, x + m_tex->GetWidth(), y + m_tex->GetHeight());
    }
}

ImageBox::~ImageBox()
{
}

void ImageBox::Render()
{
    if (m_tex)
    {
        m_tex->Render(m_x, m_y);
    }
}