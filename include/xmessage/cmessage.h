#ifndef  VNOC_C_MESSAGE_BASE
#define  VNOC_C_MESSAGE_BASE

#include "ibasemessage.h"
#include <map>
#include "messagedef.h"

namespace VNOC
{
namespace Message
{

class CMessage : public IMessage
{
public:
    CMessage(int nId);
    virtual ~CMessage();

    virtual MsgStatus Read(
        IN const Define::MsgDataName& name,
        OUT MsgDataValue*& value) const;

    virtual MsgStatus ReadArr(
        IN  const Define::MsgDataName& name,
        OUT ArrayData*& value) const;

    virtual int MsgId() const;

    virtual MsgStatus Write(
        IN const Define::MsgDataName& name,
        IN MsgDataValue* pValue);

    virtual MsgStatus WriteArr(
        IN const Define::MsgDataName& name,
        IN ArrayData* pValue);

    virtual bool IsValid() const;

    CMessage& Copy(const CMessage& lhs, int MessageId = 0);

    CMessage& CopyPort(const CMessage& lhs);

    std::map<Define::MsgDataName,
        std::pair<Define::MsgMType,
        Define::MsgType> >::const_iterator PortBegin() const;

    std::map<Define::MsgDataName,
        std::pair<Define::MsgMType,
        Define::MsgType> >::const_iterator PortEnd() const;

protected:
    CMessage();

    void InitializeMessage(int nId);

    bool IsRegister(const Define::MsgDataName& name) const;

    virtual void RegisterPort(
        const Define::MsgDataName& strName,
        const Define::MsgMType& strMType,
        const Define::MsgType& strType);

private:
    void _InitDataMap();
    void _ReleaseMap();

    std::map<Define::MsgDataName, std::pair<Define::MsgMType, Define::MsgType> > m_mapPort;
    std::map<Define::MsgDataName, MsgDataValue*> m_mapMsgData;
    std::map<Define::MsgDataName, ArrayData*>    m_mapMsgDataArr;
    Define::uint32 m_MsgId;
};

}// namespace Message
}// namespace VNOC

#endif