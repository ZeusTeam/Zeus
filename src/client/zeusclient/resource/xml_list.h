#ifndef XML_LIST_
#define XML_LIST_

#include <map>
#include "include\utils\singleton.h"
#include "include\utils\utils.h"
#include "import\tinyxml-2.6.2\tinyxml.h"
#include "xml_list_object.h"

typedef std::map<std::string, XMLFileObject*> mapXMLList;

class CXMLResource : public Singleton<CXMLResource>
{
    friend Singleton<CXMLResource>;
public:
    virtual ~CXMLResource();

    bool LoadXML(const std::string& strPath);

    virtual bool Initialize();

    const mapXMLList::const_iterator Begin() const;

    const mapXMLList::const_iterator End() const;

    int Size() const;

private:
    CXMLResource();

    bool _Parse(TiXmlDocument& tiDoc);

    mapXMLList m_mapXMLList;
};

#endif