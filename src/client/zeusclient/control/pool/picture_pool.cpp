#include "picture_pool.h"

PicturePool* Singleton<PicturePool>::m_pInst = NULL;

PicturePool::PicturePool()
{
    for (auto it = CPictureXMLParse::Instance()->Begin();
        it != CPictureXMLParse::Instance()->End();
        it++)
    {
        TextureObject* pObject = new TextureObject;
        pObject->Load(it->second->PicturePath.c_str());
        m_Pool[it->first] = pObject;
    }
}

PicturePool::~PicturePool()
{
    Release();
}

bool PicturePool::Initialize()
{
    return false;
}

TextureObject* PicturePool::Get(const std::string& strId)
{
    auto it = m_Pool.find(strId);
    if (it != m_Pool.end())
    {
        return it->second;
    }
    return NULL;
}

void PicturePool::Release()
{
    for (auto it = m_Pool.begin();
        it != m_Pool.end();
        it++)
    {
        if (it->second)
        {
            delete it->second;
            it->second = NULL;
        }
    }
}