#ifndef CPICTURE_XML_
#define CPICTURE_XML_

#include "parse_def.h"
#include <map>


struct CPictureXML
{
	std::string PictureId;
	std::string PicturePath;
    int Posx;
    int Posy;
};

#endif