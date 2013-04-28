#ifndef VNOC_C_MESSAGE_UINT
#define VNOC_C_MESSAGE_UINT

#include "msgdatavalue.h"
#include <typeinfo>

namespace VNOC
{
namespace Message
{

template<typename TUIntType>
class NumData;

typedef NumData<Define::int8>    Int8Data;
typedef NumData<Define::int16>   Int16Data;
typedef NumData<Define::int32>   Int32Data;
typedef NumData<Define::uint8>   UInt8Data;
typedef NumData<Define::uint16>  UInt16Data;
typedef NumData<Define::uint32>  UInt32Data;

template<typename TUIntType>
class NumData : public MsgDataValue
{
public:
    NumData(TUIntType Value) : m_Value(Value) {}
    virtual ~NumData() {}

    MsgStatus ToUInt8(Define::uint8& Value)
    {
        if(typeid(*this) == typeid(UInt8Data))
        {
            Value = (uint8)m_Value;
            return MsgStatus_Ok;
        }
        return MsgStatus_Err;
    }

    MsgStatus ToUInt16(Define::uint16& Value)
    {
        if(typeid(*this) == typeid(UInt16Data))
        {
            Value = (uint16)m_Value;
            return MsgStatus_Ok;
        }
        return MsgStatus_Err;
    }

    MsgStatus ToUInt32(Define::uint32& Value)
    {
        if(typeid(*this) == typeid(UInt32Data))
        {
            Value = (uint32)m_Value;
            return MsgStatus_Ok;
        }
        return MsgStatus_Err;
    }

    MsgStatus ToInt8(Define::int8& Value)
    {
        if(typeid(*this) == typeid(Int8Data))
        {
            Value = (int8)m_Value;
            return MsgStatus_Ok;
        }
        return MsgStatus_Err;
    }

    MsgStatus ToInt16(Define::int16& Value)
    {
        if(typeid(*this) == typeid(Int16Data))
        {
            Value = (int16)m_Value;
            return MsgStatus_Ok;
        }
        return MsgStatus_Err;
    }

    MsgStatus ToInt32(Define::int32& Value)
    {
        if(typeid(*this) == typeid(Int32Data))
        {
            Value = (int32)m_Value;
            return MsgStatus_Ok;
        }
        return MsgStatus_Err;
    }

    void SetValue(IN TUIntType& Value)
    {
        m_Value = Value;
    }

private:
    DISALLOW_ASSIGN(NumData);
    TUIntType m_Value;
};

}// namespace Message
}// namespace VNOC

#endif
