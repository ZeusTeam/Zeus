#ifndef  VNOC_I_MESSAGE_WRITE
#define  VNOC_I_MESSAGE_WRITE

#include "messagedef.h"
#include "msgdatavalue/msgdatavalue.h"
#include "msgdatavalue/arraydata.h"

namespace VNOC
{
namespace Message
{

class ArrayData;

class IWriteMessage
{
public:
    IWriteMessage(){}
    virtual ~IWriteMessage(){}

public:
    virtual MsgStatus Write(
        IN const Define::MsgDataName& name,
        IN MsgDataValue* pValue) = 0;

    virtual MsgStatus WriteArr(
        IN const Define::MsgDataName& name,
        IN ArrayData* pValue) = 0;
};

}// namespace Message
}// namespace VNOC

#endif