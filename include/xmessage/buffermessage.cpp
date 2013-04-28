#include "buffermessage.h"
#include <stdlib.h>
#include <cstring>

namespace VNOC
{
namespace Message
{

using namespace Define;

CBufferMessage::CBufferMessage()
    : m_attachtag(false)
    , m_Size(0)
    , m_pBuffer(NULL)
{
}

CBufferMessage::~CBufferMessage()
{
    _Free();
}

uint8* CBufferMessage::Alloc(IN uint32 nSize)
{
    void* ptmp = realloc(m_pBuffer, nSize);
    if (ptmp != NULL)
    {
        m_pBuffer = (uint8*)ptmp;
        m_Size = nSize;
    }
    return m_pBuffer;
}

uint8* CBufferMessage::GetBuffer() const
{
    return m_pBuffer;
}

uint32 CBufferMessage::GetSize() const
{
    return m_Size;
}

const CBufferMessage& CBufferMessage::Copy(
    IN const void* Src,
    IN uint32 nSize
    )
{
    if (nSize > m_Size)
    {
        Alloc(nSize);
        m_Size = nSize;
    }
    SetValue(0);
    if (m_pBuffer != NULL)
    {
        ::memcpy(m_pBuffer, Src, nSize);
    }
    return *this;
}

const CBufferMessage& CBufferMessage::Copy(IN const CBufferMessage& Src)
{
    CBufferMessage::Copy(Src.GetBuffer(), Src.GetSize());
    return *this;
}

void CBufferMessage::Attach(IN void* lpBuff, IN uint32 nSize)
{
    if ((lpBuff != NULL) || nSize > 0)
    {
        _Free();
        m_attachtag = true;
        m_pBuffer = (uint8*)lpBuff;
        m_Size = nSize;
    }
}

void CBufferMessage::_Free()
{
    if (m_attachtag)
    {
        m_attachtag = false;
        m_pBuffer = NULL;
        m_Size = 0;
    }
    if (m_pBuffer != NULL)
    {
        ::free(m_pBuffer);
        m_pBuffer = NULL;
        m_Size = 0;
    }
}

void CBufferMessage::Detach()
{
    _Free();
}

void CBufferMessage::Clear()
{
    _Free();
}

void CBufferMessage::SetValue(IN uint8 Value)
{
    if (m_pBuffer != NULL)
    {
        ::memset(m_pBuffer, Value, m_Size);
    }
}

bool CBufferMessage::Empty()
{
    if (!m_pBuffer && !m_attachtag)
    {
        return true;
    }
    return false;
}

}// namespace Message
}// namespace VNOC
