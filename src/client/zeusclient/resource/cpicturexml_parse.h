#ifndef PICTURE_PARSERXML_
#define PICTURE_PARSERXML_

#include "parse_def.h"
#include <map>
#include "cpicturexml.h"
#include "include\utils\Singleton.h"
#include "include\utils\utils.h"
#include "import\tinyxml-2.6.2\tinyxml.h"

typedef std::map<std::string, CPictureXMLObject*> MapPitureList;

class CPictureXMLParse : public Singleton<CPictureXMLParse>
{
    friend class Singleton<CPictureXMLParse>;
public:
    ~CPictureXMLParse();

    bool LoadXML(const std::string& strPath);
    CPictureXMLObject* Get(std::string nId) const;

    const MapPitureList::const_iterator Begin() const;
    const MapPitureList::const_iterator End() const;

    int Size() const;
    bool Empty() const;

private:
    void _Close();
    bool _Parse(TiXmlDocument& TinyXML);
 
private:
    CPictureXMLParse();
    CPictureXMLParse( CPictureXMLParse& );
    CPictureXMLParse& operator = (CPictureXMLParse&);

private:
    MapPitureList m_mapPiture;
};

#endif