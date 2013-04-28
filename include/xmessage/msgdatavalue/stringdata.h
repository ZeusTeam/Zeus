#ifndef  VNOC_I_MESSAGE_DATA_STRING
#define  VNOC_I_MESSAGE_DATA_STRING

#include "msgDatavalue.h"

namespace VNOC
{
namespace Message
{

class StringData : public MsgDataValue
{
public:
    virtual ~StringData(){}
    StringData();
    StringData(const std::string& Value);

    virtual MsgStatus ToStr(OUT std::string& Value);

    void SetValue(IN const std::string& Value);

private:
    DISALLOW_ASSIGN(StringData);
    std::string m_Value;
};

}// namespace Message
}// namespace VNOC

#endif