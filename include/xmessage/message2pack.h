#ifndef  VNOC_MESSAGE2PACK
#define  VNOC_MESSAGE2PACK

#include "messagedef.h"
#include "cmessage.h"
#include "buffermessage.h"

namespace VNOC
{
namespace Message
{

///> MSG转Pack
class CMessage2Pack
{
public:
    CMessage2Pack();
    ~CMessage2Pack();

    ///> size为按uint8（char）的个数算
    MsgStatus GetPackSize(IN const CMessage* pMsg, OUT int& nSize);
    MsgStatus PackMessage(IN const CMessage* pMsg, OUT CBufferMessage& pBuf);

private:
    int _GetDataSize(const Define::MsgDataName& strName, MsgDataType eType,const CMessage* pMsg);
    int _GetStringSize(MsgDataValue* pReadStr);
    int _GetArrSize(const Define::MsgDataName& strName, MsgDataType eType,const CMessage* pMsg);
    int _PackHead(int PackMsgId, CBufferMessage& pBuf);
    int _PackTail(int nPackPos, CBufferMessage& pBuf);
    MsgStatus _PushMessageDataParam(
        MsgDataType eType,
        const CMessage* pMsg,
        std::string ParamName,
        std::vector<int>& vecParamLen,
        std::vector<std::vector<Define::uint8> >& vecParamList);
    MsgStatus _PushMessageListParam(
        MsgDataType eType,
        const CMessage* pMsg,
        std::string ParamName,
        std::vector<int>& vecParamLen,
        std::vector<std::vector<Define::uint8> >& vecParamList);
    MsgStatus _PackParam(
        const CMessage* pMsg,
        CBufferMessage& pBuf,
        int& nPackPos,
        std::vector<int>& vecParamLen,
        std::vector<std::vector<Define::uint8> >& vecParamList);
    MsgStatus _Occupy(
        MsgDataType eType,
        std::vector<int>& vecParamLen,
        std::vector<std::vector<Define::uint8> >& vecParamList);
};

}// namespace Message
}// namespace VNOC

#endif