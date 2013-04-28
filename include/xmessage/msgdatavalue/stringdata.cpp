#include "stringdata.h"

namespace VNOC
{
namespace Message
{

void StringData::SetValue(IN const std::string& Value)
{
    m_Value = Value;
}

MsgStatus StringData::ToStr(OUT std::string& Value)
{
    Value = m_Value;
    return MsgStatus_Ok;
}

StringData::StringData( const std::string& Value )
{
    SetValue(Value);
}

StringData::StringData() : m_Value("")
{
}

}// namespace Message
}// namespace VNOC
