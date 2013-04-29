#ifndef  VNOC_I_MESSAGE_DATA
#define  VNOC_I_MESSAGE_DATA

#include "../messagedef.h"

namespace VNOC
{
namespace Message
{

class MsgDataValue
{
public:
    MsgDataValue();
    virtual ~MsgDataValue();

    virtual MsgStatus ToStr(OUT std::string& Value);

    virtual MsgStatus ToUInt8(OUT Define::uint8& Value);

    virtual MsgStatus ToUInt16(OUT Define::uint16& Value);

    virtual MsgStatus ToUInt32(OUT Define::uint32& Value);

    virtual MsgStatus ToInt8(OUT Define::int8& Value);

    virtual MsgStatus ToInt16(OUT Define::int16& Value);

    virtual MsgStatus ToInt32(OUT Define::int32& Value);
};

}// namespace Message
}// namespace VNOC

#endif