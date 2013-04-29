#ifndef VNOC_C_MESSAGE_PARSERXML
#define VNOC_C_MESSAGE_PARSERXML

#include <string>
#include <vector>
#include <map>
#include "messagedef.h"
#include "xmlobject.h"

class TiXmlDocument;

namespace VNOC
{
namespace Message
{

class ParserMessageXML
{
public:
    static ParserMessageXML& Instance();

    virtual ~ParserMessageXML();

    MsgStatus LoadFile(const char* strPath);

    XMLObject* GetMsgObject(const std::string& strName);
    XMLObject* GetMsgObject(int nId);

    std::map<int, XMLObject>::iterator ObjectBegin()
    {
        return m_MsgObjectList.begin();
    }
    std::map<int, XMLObject>::iterator ObjectEnd()
    {
        return m_MsgObjectList.end();
    }

private:
    ParserMessageXML();
    bool _Parser(TiXmlDocument& xmlTiny);

    std::map<std::string, int> m_MsgIdList;
    std::map<int, XMLObject> m_MsgObjectList;
};

}// namespace Message
}// namespace VNOC

#endif
