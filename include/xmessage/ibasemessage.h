#ifndef  VNOC_I_MESSAGE_BASE
#define  VNOC_I_MESSAGE_BASE

#include "iwritemessage.h"
#include "ireadmessage.h"

namespace VNOC
{
namespace Message
{

class IMessage
    : public IReadMessage
    , public IWriteMessage
{
public:
    IMessage(){}
    virtual ~IMessage(){}

public:
    virtual MsgStatus Read(
        IN const Define::MsgDataName& name,
        OUT MsgDataValue*& value) const = 0;

    virtual MsgStatus ReadArr(
        IN  const Define::MsgDataName& name,
        OUT ArrayData*& value) const = 0;

    virtual int MsgId() const = 0;

    virtual MsgStatus Write(
        IN const Define::MsgDataName& name,
        IN MsgDataValue* pValue) = 0;

    virtual MsgStatus WriteArr(
        IN const Define::MsgDataName& name,
        IN ArrayData* pValue) = 0;

    virtual bool IsValid() const = 0;
};

}// namespace Message
}// namespace VNOC

#endif