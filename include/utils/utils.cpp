#include "utils.h"
#include <cstdio>

bool utils::GetXmlStrAttributeA( TiXmlElement *pElement, char *pName, std::string &strData )
{
    if (pElement)
    {
        const char *pStr = pElement->Attribute(pName);
        if (pStr)
        {
            strData = std::string(pStr);
            return true;
        }
    }
    return false;
}
bool utils::GetXmlIntAttribute( TiXmlElement *pElement, char *pName, int &nData )
{
    if (pElement)
    {
        const char *pStr = pElement->Attribute(pName);
        if (pStr)
        {
            nData = atoi(pStr);
            return true;
        }
    }
    return false;
}