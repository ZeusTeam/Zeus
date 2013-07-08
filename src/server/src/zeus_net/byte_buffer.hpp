#ifndef ZEUS_BASE_BYTE_BUFFER_H_
#define ZEUS_BASE_BYTE_BUFFER_H_

#include "common.h"

namespace zeus{
namespace base{

class ByteBuffer
{
    const static uint32 EMPTY_BUFFER = 0x0000;
    const static uint32 DEFAULT_SIZE = 0x1000;

public:
	ByteBuffer() 
        : _rpos(0), _wpos(0)
    {
		_buffer.reserve(EMPTY_BUFFER);
	}

	ByteBuffer(size_t size)
        : _rpos(0), _wpos(0)
    {
		_buffer.reserve(size);
	}

    ByteBuffer(const char* src, size_t size)
        : _rpos(0), _wpos(0)
    {
        ByteBuffer((const byte*)src, size);
    }

    ByteBuffer(const byte* src, size_t size)
        : _rpos(0), _wpos(0)
    {
        _buffer.reserve(size);
        memcpy(&_buffer[0], src, size);
    }

	ByteBuffer(const ByteBuffer& buf) 
        : _rpos(buf._rpos), _wpos(buf._wpos), _buffer(buf._buffer) 
    {
    }

public:
    const byte* buffer() const
    {
        return &_buffer[0];
    }

    inline size_t size() const
    {
        return _buffer.size();
    }

	void clear()
    {
		_buffer.clear();
		_rpos = _wpos = 0;
	}

protected:
    size_t _rpos, _wpos;
    std::vector<byte> _buffer;
};

}
}
#endif