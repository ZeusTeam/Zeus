#ifndef  VNOC_MESSAGE_DEF
#define  VNOC_MESSAGE_DEF

#ifndef IN
#define  IN
#define  OUT
#endif

#ifndef EMPTY_TEMPTALE_DEFINE
#define  EMPTY_TEMPTALE_DEFINE template<>
#endif

// 短整型大小端互换
#define BigLittleSwap16(A)        ((((ushort)(A) & 0xff00) >> 8) | \
    (((ushort)(A) & 0x00ff) << 8))

// 长整型大小端互换
#define BigLittleSwap32(A)        ((((uint)(A) & 0xff000000) >> 24) | \
    (((uint)(A) & 0x00ff0000) >> 8) | \
    (((uint)(A) & 0x0000ff00) << 8) | \
    (((uint)(A) & 0x000000ff) << 24))

#include <string>
#include <vector>
#include "messageuniondef.h"

namespace VNOC
{
namespace Message
{

typedef enum _MsgDataType
{
    MsgDataType_Null,
    MsgDataType_String,
    MsgDataType_Uint8,
    MsgDataType_Uint16,
    MsgDataType_Uint32,
}MsgDataType;

typedef enum _MsgDataMType
{
    MsgDataMType_Null,
    MsgDataMType_Data,
    MsgDataMType_List,
}MsgDataMType;

namespace Define
{

typedef std::string         MsgDataName;
typedef MsgDataMType        MsgMType;
typedef MsgDataType         MsgType;
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef char                int8;
typedef short               int16;
typedef int                 int32;

}
#define MSG_BEGIN    0x56 // 'V' 标记消息的开始
#define MSG_END      0x43 // 'C' 标记消息的结束
#define MSG_VER      1 // 版本号

#define MSG_HEAD_LEN 10
#define MSG_TAIL_LEN 1

#define MSG_CLASS_BEGIN                1
#define MSG_CLASS_END                  1
#define MSG_CLASS_LEN                  4
#define MSG_CLASS_VER                  1
#define MSG_CLASS_SERIAL               2
#define MSG_CLASS_GUID                 16
#define MSG_CLASS_COMMAND              4
#define MSG_CLASS_OBL                  4
#define MSG_CLASS_PARAMCONST           1
#define MSG_CLASS_VERIFY               2 // 效验码 未定默认为2个字节
#define MSG_CLASS_PARAM                4
#define MSG_CLASS_PARAM_COUNT          4

#define MSG_PACKSIZE_INDEX  MSG_CLASS_VER + MSG_CLASS_BEGIN
#define MSG_COMMAND_INDEX MSG_PACKSIZE_INDEX + MSG_CLASS_LEN

#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);             \
    void operator=(const TypeName&);
#endif

#ifndef DISALLOW_ASSIGN
#define DISALLOW_ASSIGN(TypeName) \
    void operator=(const TypeName&);
#endif

#define MsgDataMType_XML_Data     "data"
#define MsgDataMType_XML_List     "list"

#define MsgDataObject_XML_Name    "name"
#define MsgDataObject_XML_Id      "id"
#define MsgDataObject_XML_MType   "mtype"
#define MsgDataObject_XML_Type    "type"
#define MsgDataObject_XML_Root    "vnoc"
#define MsgDataObject_XML_Msg     "msg"

#define MsgDataType_XML_Uint32    "uint32"
#define MsgDataType_XML_Uint16    "uint16"
#define MsgDataType_XML_Uint8     "uint8"
#define MsgDataType_XML_String    "string"

#define MsgPack_Unk 0

typedef enum _MsgStatus
{
   MsgStatus_Ok,
   MsgStatus_Err,
   MsgStatus_Unk,
   MsgStatus_FormatFailure,
   MsgStatus_TypeErr,
}MsgStatus;

}// namespace Message
}// namespace VNOC

#endif