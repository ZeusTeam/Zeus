#include "message2pack.h"

namespace VNOC
{
namespace Message
{

using namespace VNOC::Message::Define;

CMessage2Pack::CMessage2Pack()
{

}

CMessage2Pack::~CMessage2Pack()
{

}

/************************************************************************

Pack的内存结构为：

头部： | 总大小：uint32 | msg id：uint32 |
接下来为所有data（按xml定义的顺序）
uint： | uint8 | uint16 | uint32 |
string： | 长度 : uint32 | 字符串 |
array： | 元素个数 : uint32 | 数据s（按前面所述）

************************************************************************/

MsgStatus CMessage2Pack::GetPackSize(const CMessage* pMsg, int& nSize )
{
    if (!pMsg)
    {
        return MsgStatus_Err;
    }
    int nId = pMsg->MsgId();
    if (nId == 0)
    {
        return MsgStatus_Err;
    }
    int nLen = MSG_HEAD_LEN + MSG_TAIL_LEN; ///> 总大小+msg id
    int nAdd = 0;
    MsgDataValue* pReadStr = NULL;
    auto it = pMsg->PortBegin();
    for (; it != pMsg->PortEnd(); ++it)
    {
        switch (it->second.first)
        {
        case MsgDataMType_Data:
            nAdd = _GetDataSize(it->first, it->second.second, pMsg);
            if (nAdd == 0)
            {
                return MsgStatus_Err;
            }
            nLen += nAdd;
            break;
        case MsgDataMType_List:
            nAdd = _GetArrSize(it->first, it->second.second, pMsg);
            if (nAdd == 0)
            {
                return MsgStatus_Err;
            }
            nLen += nAdd + MSG_CLASS_PARAM_COUNT;
            break;
        default:
            return MsgStatus_Err;
        }
    }
    nSize = nLen;
    return MsgStatus_Ok;
}

MsgStatus CMessage2Pack::PackMessage(const CMessage* pMsg, CBufferMessage& pBuf)
{
    if (!pMsg)
    {
        return MsgStatus_Err;
    }
    int PackSize = 0;
    if (GetPackSize(pMsg, PackSize) != MsgStatus_Ok)
    {
        return MsgStatus_Err;
    }
    uint8* Buff = pBuf.Alloc(PackSize);
    if (Buff == NULL)
    {
        return MsgStatus_Err;
    }
    int nId = pMsg->MsgId();
    if (nId == 0)
    {
        return MsgStatus_Err;
    }
    int nPackPos = _PackHead(nId,pBuf);
    std::vector<int> vecParamLen;
    std::vector<std::vector<uint8> > vecParamList;
    for (auto It = pMsg->PortBegin(); It != pMsg->PortEnd(); It++)
    {
        switch (It->second.first)
        {
        case MsgDataMType_Data:
            _PushMessageDataParam(It->second.second, pMsg,It->first, vecParamLen, vecParamList);
            break;
        case MsgDataMType_List:
            _PushMessageListParam(It->second.second, pMsg,It->first, vecParamLen, vecParamList);
            break;
        default:
            return MsgStatus_Err;
        }
    }
    if (_PackParam(pMsg, pBuf, nPackPos, vecParamLen, vecParamList) != MsgStatus_Ok)
    {
        return MsgStatus_Err;
    }
    _PackTail(nPackPos, pBuf);
    return MsgStatus_Ok;
}

int CMessage2Pack::_GetDataSize(const Define::MsgDataName& strName, MsgDataType eType,const CMessage* pMsg )
{
    MsgDataValue* pReadStr = NULL;
    switch (eType)
    {
    case MsgDataType_String:
        if (pMsg->Read(strName, pReadStr) == MsgStatus_Ok)
            return _GetStringSize(pReadStr);
        break;
    case MsgDataType_Uint8:
        return 1;
        break;
    case MsgDataType_Uint16:
        return 2;
        break;
    case MsgDataType_Uint32:
        return 4;
        break;
    }
    return 0;
}

int CMessage2Pack::_GetStringSize( MsgDataValue* pReadStr )
{
    std::string strData;
    if (pReadStr && pReadStr->ToStr(strData) == MsgStatus_Ok)
    {
        if (strData.empty())
        {
            return 4 + 1;
        }
        else
        {
            return 4 + strData.size();
        }
    }
    else
    {
        return 4 + 1;
    }
    return 0;
}

int CMessage2Pack::_GetArrSize(const Define::MsgDataName& strName, MsgDataType eType,const CMessage* pMsg )
{
    int nSize = 0;
    int nAdd = 0;
    ArrayData* pReadArr = NULL;
    if (pMsg->ReadArr(strName, pReadArr) == MsgStatus_Ok)
    {
        switch (eType)
        {
        case MsgDataType_String:
            if (pReadArr == NULL)
            {
                return 1;
            }
            for (std::vector<MsgDataValue*>::const_iterator it = pReadArr->Begin();
                it != pReadArr->End();
                ++it)
            {
                nAdd = _GetStringSize(static_cast<MsgDataValue*>(*it));
                if (nAdd == 0)
                {
                    return 0;
                }
                nSize += nAdd;
            }
            break;
        case MsgDataType_Uint8:
            if (pReadArr == NULL)
            {
                return 1;
            }
            nSize = pReadArr->Size();
            break;
        case MsgDataType_Uint16:
            if (pReadArr == NULL)
            {
                return 2 * 1;
            }
            nSize = 2 * pReadArr->Size();
            break;
        case MsgDataType_Uint32:
            if (pReadArr == NULL)
            {
                return 4 * 1;
            }
            nSize = 4 * pReadArr->Size();
            break;
        }
    }
    return nSize;
}

MsgStatus CMessage2Pack::_PushMessageDataParam(
    MsgDataType eType,
    const CMessage* pMsg,
    std::string ParamName,
    std::vector<int>& vecParamLen,
    std::vector<std::vector<uint8> >& vecParamList
    )
{
    MsgDataValue* pReadValue = NULL;
    std::string strParam;
    uint8* pByteParam = NULL;
    uint8 uint8Param = 0;
    uint16 uint16Param = 0;
    uint32 uint32Param = 0;
    int strParamLen = 0;
    std::vector<uint8> vecParam;
    pMsg->Read(ParamName, pReadValue);
    if (pReadValue == NULL)
    {
        return _Occupy(eType, vecParamLen, vecParamList);
    }
    switch (eType)
    {
    case MsgDataType_String:
        pReadValue->ToStr(strParam);
        strParamLen = strParam.size();
        if (strParamLen == 0)
        {
            strParamLen = 1;
            vecParam.push_back(MsgPack_Unk);
        }
        else
        {
            pReadValue->ToStr(strParam);
            vecParam.resize(strParamLen);
            std::copy(strParam.begin(), strParam.end(), vecParam.begin());
        }
        vecParamLen.push_back(strParamLen);
        vecParamList.push_back(vecParam);
        break;
    case MsgDataType_Uint8:
        vecParamLen.push_back(sizeof(uint8));
        pReadValue->ToUInt8(uint8Param);
        vecParam.push_back(uint8Param);
        vecParamList.push_back(vecParam);
        break;
    case MsgDataType_Uint16:
        vecParamLen.push_back(sizeof(uint16));
        pReadValue->ToUInt16(uint16Param);
        pByteParam = (uint8*)&uint16Param;
        for (int index = 0; index < sizeof(uint16); index++)
        {
            vecParam.push_back(pByteParam[index]);
        }
        vecParamList.push_back(vecParam);
        break;
    case MsgDataType_Uint32:
        vecParamLen.push_back(sizeof(uint32));
        pReadValue->ToUInt32(uint32Param);
        pByteParam = (uint8*)&uint32Param;
        for (int index = 0; index < sizeof(uint32); index++)
        {
            vecParam.push_back(pByteParam[index]);
        }
        vecParamList.push_back(vecParam);
        break;
    default:
        return MsgStatus_Err;
    }
    return MsgStatus_Ok;
}

MsgStatus CMessage2Pack::_PushMessageListParam(
    MsgDataType eType,
    const CMessage* pMsg,
    std::string ParamName,
    std::vector<int>& vecParamLen,
    std::vector<std::vector<uint8> >& vecParamList
    )
{
    std::vector<uint8> vecParam;
    ArrayData* pReadArrValue = NULL;
    std::string strParam;
    uint8* pByteParam = NULL;
    uint8 uint8Param = 0;
    uint16 uint16Param = 0;
    uint32 uint32Param = 0;
    pMsg->ReadArr(ParamName, pReadArrValue);
    if (pReadArrValue == NULL)
    {
        vecParamLen.push_back(1);
        return _Occupy(eType, vecParamLen, vecParamList);
    }
    else if (pReadArrValue->Empty())
    {
        vecParamLen.push_back(1);
        return _Occupy(eType, vecParamLen, vecParamList);
    }
    vecParamLen.push_back(pReadArrValue->Size());
    switch(eType)
    {
    case MsgDataType_String:
        for (auto It = pReadArrValue->Begin();
            It != pReadArrValue->End();
            It++
            )
        {
            static_cast<MsgDataValue*>(*It)->ToStr(strParam);
            if (!strParam.empty())
            {
                vecParam.resize(strParam.size());
                vecParamLen.push_back(strParam.size());
                std::copy(strParam.begin(), strParam.end(), vecParam.begin());
            }
            else
            {
                vecParamLen.push_back(1);
            }
            vecParamList.push_back(vecParam);
            vecParam.clear();
        }
        break;
    case MsgDataType_Uint8:
        for (auto It = pReadArrValue->Begin();
            It != pReadArrValue->End();
            It++
            )
        {
            static_cast<MsgDataValue*>(*It)->ToUInt8(uint8Param);
            vecParam.push_back(uint8Param);
            vecParamLen.push_back(sizeof(uint8));
            vecParamList.push_back(vecParam);
            vecParam.clear();
        }
        break;
    case MsgDataType_Uint16:
        for (auto It = pReadArrValue->Begin();
            It != pReadArrValue->End();
            It++
            )
        {
            static_cast<MsgDataValue*>(*It)->ToUInt16(uint16Param);
            pByteParam = (uint8*)&uint16Param;
            for (uint32 index = 0; index < sizeof(uint16); index++)
            {
                vecParam.push_back(pByteParam[index]);
            }
            vecParamLen.push_back(sizeof(uint16));
            vecParamList.push_back(vecParam);
            vecParam.clear();
        }
        break;
    case MsgDataType_Uint32:
        for (auto It = pReadArrValue->Begin();
            It != pReadArrValue->End();
            It++
            )
        {
            static_cast<MsgDataValue*>(*It)->ToUInt32(uint32Param);
            pByteParam = (uint8*)&uint32Param;
            for (uint32 index = 0; index < sizeof(uint32); index++)
            {
                vecParam.push_back(pByteParam[index]);
            }
            vecParamLen.push_back(sizeof(uint32));
            vecParamList.push_back(vecParam);
            vecParam.clear();
        }
        break;
    default:
        return MsgStatus_Err;
    }
    return MsgStatus_Ok;
}

int CMessage2Pack::_PackHead(int PackMsgId, CBufferMessage& pBuf)
{
    int nPackSize = pBuf.GetSize();
    if (nPackSize <= MSG_HEAD_LEN)
    {
        return 0;
    }
    uint32 nPackPos = 0;
    uint8* pByte = NULL;
    uint8* Buff = pBuf.GetBuffer();
    ///>标记头
    Buff[nPackPos] = MSG_BEGIN;
    nPackPos++;
    ///>版本号 暂用一个字节存储
    Buff[nPackPos] = MSG_VER;
    nPackPos++;
    ///>包体大小 uint32
    pByte = (uint8*)&nPackSize;
    for (uint32 index = 0; index < MSG_CLASS_LEN; index++)
    {
        Buff[nPackPos] = pByte[index];
        nPackPos++;
    }
    ///>消息ID uint32
    pByte = (uint8*)&PackMsgId;
    for (uint32 index = 0; index < MSG_CLASS_COMMAND; index++)
    {
        Buff[nPackPos] = pByte[index];
        nPackPos++;
    }
    return nPackPos;
}

int CMessage2Pack::_PackTail(int nPackPos,CBufferMessage& pBuf)
{
    if (nPackPos == 0)
    {
        return 0;
    }
    uint8* Buff = pBuf.GetBuffer();
    if (pBuf.GetSize() < (uint32)(nPackPos + MSG_TAIL_LEN))
    {
        return 0;
    }
    Buff[nPackPos] = MSG_END;
    return nPackPos++;
}

MsgStatus CMessage2Pack::_PackParam(
    const CMessage* pMsg,
    CBufferMessage& pBuf,
    int& nPackPos,
    std::vector<int>& vecParamLen,
    std::vector<std::vector<uint8> >& vecParamList
    )
{
    if (vecParamLen.empty() || vecParamList.empty())
    {
        return MsgStatus_Err;
    }
    uint8* Buff = pBuf.GetBuffer();
    if (Buff == NULL)
    {
        return MsgStatus_Err;
    }
    uint8* pByte = NULL;
    uint32 ArrCount = 0;
    int nPackParamIndex = 0;
    int nPackParamLenIndex = 0;
    for (auto It = pMsg->PortBegin(); It != pMsg->PortEnd(); It++)
    {
        switch (It->second.first)
        {
        case MsgDataMType_Data:
            if (It->second.second == MsgDataType_String)
            {
                pByte = (uint8*)&vecParamLen[nPackParamLenIndex];
                for (int index = 0; index < sizeof(uint32); index++)
                {
                    Buff[nPackPos] = pByte[index];
                    nPackPos++;
                }
                for (uint32 index = 0; index < vecParamList[nPackParamLenIndex].size(); index++)
                {
                    Buff[nPackPos] = vecParamList[nPackParamIndex][index];
                    nPackPos++;
                }
            }
            else if (It->second.second == MsgDataType_Uint8)
            {
                Buff[nPackPos] = vecParamList[nPackParamIndex][0];
                nPackPos++;
            }
            else
            {
                for (int index = 0;
                    index < vecParamLen[nPackParamLenIndex];
                    index++
                    )
                {
                    Buff[nPackPos] = vecParamList[nPackParamIndex][index];
                    nPackPos++;
                }
            }
            nPackParamLenIndex++;
            nPackParamIndex++;
            break;
        case MsgDataMType_List:
            ///>元素个数
            ArrCount = vecParamLen[nPackParamLenIndex];
            nPackParamLenIndex++;
            if (ArrCount < 0)
            {
                ArrCount = 0;
            }
            pByte = (uint8*)&ArrCount;
            for (int index = 0; index < sizeof(uint32); index++)
            {
                Buff[nPackPos] = pByte[index];
                nPackPos++;
            }
            for (uint32 ArrIndex = 0; ArrIndex < ArrCount; ArrIndex++)
            {
                if (It->second.second == MsgDataType_String)
                {
                    pByte = (uint8*)&vecParamLen[nPackParamLenIndex];
                    for (int index = 0; index < sizeof(uint32); index++)
                    {
                        Buff[nPackPos] = pByte[index];
                        nPackPos++;
                    }
                    if (vecParamList[nPackParamIndex].empty())
                    {
                        Buff[nPackPos] = MsgPack_Unk;
                        nPackPos++;
                    }
                    else
                    {
                        for (uint32 index = 0; index < vecParamList[nPackParamIndex].size(); index++)
                        {
                            Buff[nPackPos] = vecParamList[nPackParamIndex][index];
                            nPackPos++;
                        }
                    }
                }
                else
                {
                    for (int index = 0;
                        index < vecParamLen[nPackParamLenIndex];
                        index++
                        )
                    {
                        Buff[nPackPos] = vecParamList[nPackParamIndex][index];
                        nPackPos++;
                    }
                }
                nPackParamIndex++;
                nPackParamLenIndex++;
            }
            break;
        default:
            return MsgStatus_Err;
        }
    }
    return MsgStatus_Ok;
}

MsgStatus CMessage2Pack::_Occupy(
    MsgDataType eType,
    std::vector<int>& vecParamLen,
    std::vector<std::vector<Define::uint8> >& vecParamList
    )
{
    std::vector<uint8> vecParam;
    switch (eType)
    {
    case MsgDataType_String:
        vecParamLen.push_back(1);
        vecParam.push_back(MsgPack_Unk);
        break;
    case MsgDataType_Uint8:
        vecParamLen.push_back(sizeof(uint8));
        for (int index = 0; index < sizeof(uint8); index++)
        {
            vecParam.push_back(MsgPack_Unk);
        }
        break;
    case MsgDataType_Uint16:
        vecParamLen.push_back(sizeof(uint16));
        for (int index = 0; index < sizeof(uint16); index++)
        {
            vecParam.push_back(MsgPack_Unk);
        }
        break;
    case MsgDataType_Uint32:
        vecParamLen.push_back(sizeof(uint32));
        for (int index = 0; index < sizeof(uint32); index++)
        {
            vecParam.push_back(MsgPack_Unk);
        }
        break;
    }
    vecParamList.push_back(vecParam);
    return MsgStatus_Ok;
}

}// namespace Message
}// namespace VNOC
