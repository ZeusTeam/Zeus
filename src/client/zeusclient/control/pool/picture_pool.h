#ifndef PICTURE_POOL_
#define PICTURE_POOL_

#include "resource\cpicturexml_parse.h"
#include "include\utils\singleton.h"
#include "control\control_object\texture_object.h"
#include <map>

typedef std::map<std::string,TextureObject*> PicPutrePool;

class PicturePool
    : public Singleton<PicturePool>
{
public:
    PicturePool();
    virtual ~PicturePool();

    bool Initialize();

    TextureObject* Get(const std::string& strId);

    void Release();

private:
    CPictureXMLParse* m_PictureXML;
    PicPutrePool m_Pool;
};

#endif