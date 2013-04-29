#ifndef VNOC_D_MESSSAGE_UNION_DEF
#define VNOC_D_MESSSAGE_UNION_DEF

namespace VNOC
{
namespace Message
{

typedef enum _VMsg
{
    MSG_TYPE_NULL = 0,
    MSG_RequestRegister_Id                 = 2100,
    MSG_AnswerRegister_Id                  = 2101,
    MSG_RequestVerificationCode_Id         = 3101,
    MSG_AnswerVerificationCode_Id          = 3102,
    MSG_RequestLogin_Id                    = 4101,
    MSG_AnswerLogin_Id                     = 4102,
    MSG_RequestProfileSync_Id              = 5101,
    MSG_AnswerProfileSync_Id               = 5102,
    MSG_RequestClassList_Id                = 6105,
    MSG_AnswerClassList_Id                 = 6106,
    MSG_RequestClassInfo_Id                = 6107,
    MSG_AnswerClassInfo_Id                 = 6108,
    MSG_RequestEnterClassroom_Id           = 6109,
    MSG_AnswerEnterClassroom_Id            = 6110,
    MSG_RequestSendChat_Id                 = 7101,
    MSG_AnswerSendChat_Id                  = 7102,
    MSG_DispatchChat_Id                    = 7103,
    MSG_TYPE_END,
}VMsg;

}
}

#endif