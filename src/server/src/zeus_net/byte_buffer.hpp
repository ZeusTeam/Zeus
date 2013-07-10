#ifndef ZEUS_BASE_BYTE_BUFFER_H_
#define ZEUS_BASE_BYTE_BUFFER_H_

#include "common.h"

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

	explicit ByteBuffer(size_t size)
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
        //_buffer.reserve(size);
        //memcpy(&_buffer[0], src, size);
        append(src, size);
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

public:
    template <typename TYPE> void append(TYPE value)
    {
        append((const byte*)&value, sizeof(value));
    }

    void append(const std::string& value)
    {
        append((byte*)value.c_str(), value.size() + 1);
    }

    void append(const char* value, size_t size)
    {
        append((byte*)value, size);
    }

    void append(const byte* value, size_t size)
    {
        if (size == 0) return;
        size_t wsize = _wpos + size;

        //buffer空间不够则扩大
        if (this->size() < wsize)
            _buffer.resize(wsize);

        memcpy(&_buffer[_wpos], value, size);
        _wpos += size;
    }

    void append(const ByteBuffer& value)
    {
        if (value.size() > 0)
        {
            append(value.buffer(), value.size());
        }
    }

public:
    template <typename TYPE> void put(size_t pos, TYPE value)
    {
        put(pos, (const byte*)&value, sizeof(value));
    }

    void put(size_t pos, const byte* src, size_t size)
    {
		assert(pos + size <= this->size());
		memcpy(&_buffer[pos], src, size);
	}

public:
	template <typename T> T read()
    {
		T r=read<T>(_rpos);
		_rpos += sizeof(T);
		return r;
	}

	template <typename T> T read(size_t pos) const
    {
		if(pos + sizeof(T) > size())
		{
			return (T)0;
		} else {
			return *((T*)&_buffer[pos]);
		}
	}

	void read(uint8 *dest, size_t len)
    {
		if (_rpos + len <= size()) {
			memcpy(dest, &_buffer[_rpos], len);
		} else {
			//throw error();
			memset(dest, 0, len);
		}
		_rpos += len;
	}

public:
    void resize(size_t new_size)
    {
	    _buffer.resize(new_size);
	    _rpos = 0;
	    _wpos = size();
    }

	void reserve(size_t reserve_size)
    {
		if (reserve_size > size())
            _buffer.reserve(reserve_size);
	};

protected:
    std::vector<byte> _buffer;
    size_t _rpos, _wpos;
};

#endif