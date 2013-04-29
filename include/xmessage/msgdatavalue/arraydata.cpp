#include "arraydata.h"

namespace VNOC
{
namespace Message
{

using namespace Define;

ArrayData::ArrayData()
{

}

ArrayData::~ArrayData()
{

}

size_t ArrayData::Size()
{
    return m_arrValuePtr.size();
}

bool ArrayData::Empty()
{
    return m_arrValuePtr.empty();
}

std::vector<MsgDataValue*>::const_iterator ArrayData::Begin() const
{
    return m_arrValuePtr.begin();
}

std::vector<MsgDataValue*>::const_iterator ArrayData::End() const
{
    return m_arrValuePtr.end();
}

void ArrayData::Push( MsgDataValue* pValue )
{
    return m_arrValuePtr.push_back(pValue);
}


template<>
void ArrayData::Push<std::string>( const std::vector<std::string>& vecArr )
{
    if (vecArr.empty())
    {
        Push(new StringData(""));
        return;
    }
    for (auto It = vecArr.begin(); It != vecArr.end(); It++)
    {
        Push(new StringData(*It));
    }
}

template<>
void ArrayData::Push<uint8>( const std::vector<uint8>& vecArr )
{
    if (vecArr.empty())
    {
        Push(new NumData<uint8>(0));
        return;
    }
    for (auto It = vecArr.begin(); It != vecArr.end(); It++)
    {
        Push(new NumData<uint8>(*It));
    }
}

template<>
void ArrayData::Push<uint16>( const std::vector<uint16>& vecArr )
{
    if (vecArr.empty())
    {
        Push(new NumData<uint16>(0));
        return;
    }
    for (auto It = vecArr.begin(); It != vecArr.end(); It++)
    {
        Push(new NumData<uint16>(*It));
    }
}

template<>
void ArrayData::Push<uint32>( const std::vector<uint32>& vecArr )
{
    if (vecArr.empty())
    {
        Push(new NumData<uint32>(0));
        return;
    }
    for (auto It = vecArr.begin(); It != vecArr.end(); It++)
    {
        Push(new NumData<uint32>(*It));
    }
}

template<>
void ArrayData::GetArr_vec<std::string>( std::vector<std::string>& vecArr )
{
    for (auto It = m_arrValuePtr.begin(); It != m_arrValuePtr.end(); It++)
    {
        std::string strValue;
        (*It)->ToStr(strValue);
        vecArr.push_back(strValue);
        strValue = "";
    }
}

template<>
void ArrayData::GetArr_vec<uint8>( std::vector<uint8>& vecArr )
{
    for (auto It = m_arrValuePtr.begin(); It != m_arrValuePtr.end(); It++)
    {
        uint8 strValue;
        (*It)->ToUInt8(strValue);
        vecArr.push_back(strValue);
        strValue = 0;
    }
}

template<>
void ArrayData::GetArr_vec<uint16>( std::vector<uint16>& vecArr )
{
    for (auto It = m_arrValuePtr.begin(); It != m_arrValuePtr.end(); It++)
    {
        uint16 strValue;
        (*It)->ToUInt16(strValue);
        vecArr.push_back(strValue);
        strValue = 0;
    }
}

template<>
void ArrayData::GetArr_vec<uint32>( std::vector<uint32>& vecArr )
{
    for (auto It = m_arrValuePtr.begin(); It != m_arrValuePtr.end(); It++)
    {
        uint32 strValue;
        (*It)->ToUInt32(strValue);
        vecArr.push_back(strValue);
        strValue = 0;
    }
}

}// namespace Message
}// namespace VNOC
