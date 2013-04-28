#ifndef VNOC_MESSAGEPARSER
#define VNOC_MESSAGEPARSER

#include "messagedef.h"
#include "buffermessage.h"
#include "cmessage.h"

namespace VNOC
{
namespace Message
{

class CMessage2Parser
{
public:
    CMessage2Parser() : m_MsgId(0) {}
    virtual ~CMessage2Parser() {}

    MsgStatus Parser(OUT CMessage* pMsg, IN const CBufferMessage& pBuf);
    bool IsVaild(IN const CBufferMessage& pBuf);
    static Define::uint32 GetMessageLen(Define::uint8* pData, Define::uint32 nBufferSize);
    static int GetMsgType(IN const CBufferMessage& pBuf);

private:
    MsgStatus _ParserHead(CMessage* pMsg, const CBufferMessage& pBuf);
    MsgStatus _ParserTail(CMessage* pMsg, const CBufferMessage& pBuf);
    MsgStatus _ParserParam(CMessage* pMsg, const CBufferMessage& pBuf);
    int _ByteToInt(Define::uint8* pData);

private:
    int m_MsgId;
};

}
}

#endif