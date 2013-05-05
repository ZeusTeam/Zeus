#pragma once

#include <string.h>
#include "import\tinyxml-2.6.2\tinyxml.h"

namespace utils
{
    bool GetXmlStrAttributeA( TiXmlElement *pElement, char *pName, std::string &strData );
    bool GetXmlIntAttribute( TiXmlElement *pElement, char *pName, int &nData );
}