#ifndef CPICTURE_XML_OBJECT_
#define CPICTURE_XML_OBJECT_

#include "parse_def.h"
#include <map>


struct CPictureXMLObject
{
    CPictureXMLObject()
    {
        Posx = 0;
        Posy = 0;
    }
    std::string PictureId;
    std::string PicturePath;
    int Posx;
    int Posy;
};

#endif