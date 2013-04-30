#ifndef XML_LIST_
#define XML_LIST_

#include <map>
#include <Parse_def.h>
#include "include\utils\singleton.h"
#include "import\tinyxml-2.6.2\tinyxml.h"



typedef std::map<std::string, std::string> mapXMLList;

class CXMLResource : public Singleton<CXMLResource>
{
		friend Singleton<CXMLResource>;
public:
		virtual ~CXMLResource();

		//bool loadXML(const std::string& strPath);

		virtual bool Initialize();

private:
		CXMLResource();

		mapXMLList* _Parse(TiXmlDocument& tiDoc);

		//bool _LoadGameXML(mapXMLList& mapXMLList);

		mapXMLList m_mapXMLList;
};
#endif