#pragma once

#include <string.h>
#include <Windows.h>
#include "import\tinyxml-2.6.2\tinyxml.h"

namespace utils
{
    bool GetXmlStrAttributeA( TiXmlElement *pElement, char *pName, std::string &strData );
    bool GetXmlIntAttribute( TiXmlElement *pElement, char *pName, int &nData );
    bool InstallFont(const std::string path);
    bool UninstallFont(const std::string path);
    void ErrorMessage(const std::string text);
}