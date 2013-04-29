#ifndef  VNOC_I_MESSAGE_DATA_ARRAY
#define  VNOC_I_MESSAGE_DATA_ARRAY

#include "../messagedef.h"
#include "numdata.hpp"
#include "stringdata.h"

namespace VNOC
{
namespace Message
{

class MsgDataValue;

class ArrayData
{
public:
    ArrayData();
    virtual ~ArrayData();

    size_t Size();

    bool Empty();

    std::vector<MsgDataValue*>::const_iterator Begin() const;

    std::vector<MsgDataValue*>::const_iterator End() const;

    void Push(IN MsgDataValue* pValue);

    template<typename T>
    void Push(const std::vector<T>& vecArr);

    template<typename T>
    void GetArr_vec(std::vector<T>& vecArr);

private:
    std::vector<MsgDataValue*> m_arrValuePtr;
};

}// namespace Message
}// namespace VNOC

#endif