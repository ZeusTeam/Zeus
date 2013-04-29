#ifndef PICTURE_PARSERXML_
#define PICTURE_PARSERXML_

#include <Parse_def.h>
#include <map>
#include <CPictureXML.h>
#include "import\tinyxml-2.6.2\tinyxml.h"

typedef std::map<std::string, CPictureXML*> MapPitureList;

class CPictureXMLParse
{
public:
		~CPictureXMLParse();

		static CPictureXMLParse& GetInstance();
		bool LoadXML(const std::string& strPath);
		CPictureXML* Get(std::string nId) const;

		const MapPitureList::const_iterator Begin() const;
		const MapPitureList::const_iterator End() const;

		int Size() const;
		bool Empty() const;

private:
    void _Close();
    bool _Parse(TiXmlDocument& TinyXML);

private:
    CPictureXMLParse();
    CPictureXMLParse(CPictureXMLParse&);
    CPictureXMLParse& operator = (CPictureXMLParse&);

private:
    MapPitureList m_mapPiture;
};

#endif