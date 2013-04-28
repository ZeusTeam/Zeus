#ifndef  VNOC_I_MESSAGE_READ
#define  VNOC_I_MESSAGE_READ

#include "messagedef.h"
#include "msgdatavalue/msgdatavalue.h"
#include "msgdatavalue/arraydata.h"

namespace VNOC
{
namespace Message
{

class ArrayData;

class IReadMessage
{
public:
    IReadMessage(){}
    virtual ~IReadMessage(){}

public:
    virtual MsgStatus Read(
        IN const Define::MsgDataName& name,
        OUT MsgDataValue*& value) const = 0;

    virtual MsgStatus ReadArr(
        IN  const Define::MsgDataName& name,
        OUT ArrayData*& value) const = 0;

    virtual int MsgId() const = 0;
};

}// namespace Message
}// namespace VNOC

#endif