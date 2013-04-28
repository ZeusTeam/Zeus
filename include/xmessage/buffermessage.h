#ifndef  VNOC_C_MESSAGE_BUFFER
#define  VNOC_C_MESSAGE_BUFFER

#include "messagedef.h"

namespace VNOC
{
namespace Message
{

class CBufferMessage
{
public:
    CBufferMessage();
    virtual ~CBufferMessage();

    Define::uint8* Alloc(IN Define::uint32 nSize);

    Define::uint8* GetBuffer() const;

    Define::uint32 GetSize() const;

    const CBufferMessage& Copy(IN const void* Src, Define::uint32 nSize);

    const CBufferMessage& Copy(IN const CBufferMessage& Src);

    void SetValue(Define::uint8 Value);

    void Attach(IN void* lpBuff, IN Define::uint32 nSize);

    void Detach();

    void Clear();

    bool Empty();

private:
    void _Free();

private:
    DISALLOW_COPY_AND_ASSIGN(CBufferMessage);
    Define::uint32 m_Size;
    Define::uint8* m_pBuffer;
    bool m_attachtag;
};

}// namespace Message
}// namespace VNOC

#endif