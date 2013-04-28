#include "CMessage.h"

namespace VNOC
{
namespace Message
{

using namespace VNOC::Message::Define;

MsgStatus CMessage::Read(
    IN const MsgDataName& name,
    OUT MsgDataValue*& value
    ) const
{
    if (IsRegister(name))
    {
        auto tmpItr = m_mapMsgData.find(name);
        if (tmpItr != m_mapMsgData.end())
        {
            value = tmpItr->second;
            return MsgStatus_Ok;
        }
    }
    return MsgStatus_Err;
}

MsgStatus CMessage::ReadArr(
    IN const MsgDataName& name,
    OUT ArrayData*& value
    ) const
{
    if (IsRegister(name))
    {
        auto tmpItr = m_mapMsgDataArr.find(name);
        if (tmpItr != m_mapMsgDataArr.end())
        {
            value = tmpItr->second;
            return MsgStatus_Ok;
        }
    }
    return MsgStatus_Err;
}

MsgStatus CMessage::Write(
    IN const MsgDataName& name,
    IN MsgDataValue* pValue
    )
{
    if (IsRegister(name))
    {
        auto itFind = m_mapMsgData.find(name);
        if (itFind == m_mapMsgData.end())
        {
            return MsgStatus_Err;
        }
        delete itFind->second;
        itFind->second = pValue;
        return MsgStatus_Ok;
    }
    return MsgStatus_Err;
}

MsgStatus CMessage::WriteArr(
    IN const MsgDataName& name,
    IN ArrayData* pValue
    )
{
    if (IsRegister(name))
    {
        auto itFind = m_mapMsgDataArr.find(name);
        if (itFind == m_mapMsgDataArr.end())
        {
            return MsgStatus_Err;
        }
        delete itFind->second;
        itFind->second = pValue;
        return MsgStatus_Ok;
    }
    return MsgStatus_Err;
}

CMessage::CMessage() : m_MsgId(0)
{

}

CMessage::CMessage( int nId )
{
    m_MsgId = nId;
    _InitDataMap();
}

void CMessage::InitializeMessage( int nId )
{
    m_MsgId = nId;
    _InitDataMap();
}

bool CMessage::IsRegister(const MsgDataName& name) const
{
    auto tmpItr = m_mapPort.find(name);
    if (tmpItr != m_mapPort.end())
    {
        return true;
    }
    return false;
}

void CMessage::RegisterPort(
    const Define::MsgDataName& strName,
    const Define::MsgMType& strMType,
    const Define::MsgType& strType
    )
{
    m_mapPort[strName] = std::make_pair(strMType, strType);
}

std::map<Define::MsgDataName,
    std::pair<Define::MsgMType,
    Define::MsgType> >::const_iterator CMessage::PortBegin() const
{
    return m_mapPort.begin();
}

std::map<Define::MsgDataName,
    std::pair<Define::MsgMType,
    Define::MsgType> >::const_iterator CMessage::PortEnd() const
{
    return m_mapPort.end();
}

CMessage::~CMessage()
{
    _ReleaseMap();
}

bool CMessage::IsValid() const
{
    if (m_MsgId == 0)
    {
        return false;
    }
    return true;
}

void CMessage::_InitDataMap()
{
    if (!m_mapPort.empty())
    {
        auto it = m_mapPort.begin();
        for (; it != m_mapPort.end(); ++it)
        {
            if (it->second.first == MsgDataMType_Data)
            {
                m_mapMsgData[it->first] = NULL;
            }
            if (it->second.first == MsgDataMType_List)
            {
                m_mapMsgDataArr[it->first] = NULL;
            }
        }
    }
}

void CMessage::_ReleaseMap()
{
    auto itData = m_mapMsgData.begin();
    for (; itData != m_mapMsgData.end(); ++ itData)
    {
        delete itData->second;
    }
    m_mapMsgData.clear();
    auto itList = m_mapMsgDataArr.begin();
    for (; itList != m_mapMsgDataArr.end(); ++ itList)
    {
        delete itList->second;
    }
    m_mapMsgDataArr.clear();
}

int CMessage::MsgId() const
{
    return m_MsgId;
}

CMessage& CMessage::CopyPort(const CMessage& lhs)
{
    m_MsgId = lhs.MsgId();
    for (auto It = lhs.PortBegin(); It != lhs.PortEnd(); It++)
    {
        m_mapPort[It->first] = It->second;
    }
    m_mapMsgData.clear();
    auto it = m_mapPort.begin();
    for (; it != m_mapPort.end(); ++it)
    {
        if (it->second.first == MsgDataMType_Data)
        {
            m_mapMsgData[it->first] = NULL;
        }
        if (it->second.first == MsgDataMType_List)
        {
            m_mapMsgDataArr[it->first] = NULL;
        }
    }
    return (*this);
}

CMessage& CMessage::Copy(const CMessage& lhs, int MessageId /* = 0 */)
{
    if (MessageId = 0)
    {
        InitializeMessage(lhs.MsgId());
    }
    else
    {
        InitializeMessage(MessageId);
    }
    MsgDataValue* lpReadValue = NULL;
    ArrayData* lpReadValueArr = NULL;
    m_mapMsgData.clear();
    m_mapMsgDataArr.clear();
    m_mapPort.clear();
    CopyPort(lhs);
    for (auto It = lhs.PortBegin(); It != lhs.PortEnd(); It++)
    {
        switch (It->second.first)
        {
        case MsgDataMType_Data:
            lhs.Read(It->first, lpReadValue);
            switch (It->second.second)
            {
            case MsgDataType_String:
                if (lpReadValue != NULL)
                {
                    std::string strValute;
                    lpReadValue->ToStr(strValute);
                    Write(It->first, new StringData(strValute));
                }
                break;
            case MsgDataType_Uint8:
                if (lpReadValue != NULL)
                {
                    uint8 NumValute = 0;
                    lpReadValue->ToUInt8(NumValute);
                    Write(It->first, new NumData<uint8>(NumValute));
                }
                break;
            case MsgDataType_Uint16:
                if (lpReadValue != NULL)
                {
                    uint16 NumValute = 0;
                    lpReadValue->ToUInt16(NumValute);
                    Write(It->first, new NumData<uint16>(NumValute));
                }
                break;
            case MsgDataType_Uint32:
                if (lpReadValue != NULL)
                {
                    uint32 NumValute = 0;
                    lpReadValue->ToUInt32(NumValute);
                    Write(It->first, new NumData<uint32>(NumValute));
                }
                break;
            }
            break;
        case MsgDataMType_List:
            lhs.ReadArr(It->first, lpReadValueArr);
            if (lpReadValueArr != NULL)
            {
                ArrayData* lpWriteArr = new ArrayData;
                for (auto ArrIt = lpReadValueArr->Begin();
                    ArrIt != lpReadValueArr->End();
                    ArrIt++
                    )
                {
                    lpWriteArr->Push((*ArrIt));
                }
                WriteArr(It->first, lpWriteArr);
            }
            break;
        }
    }
    return (*this);
}

}// namespace Message
}// namespace VNOC
