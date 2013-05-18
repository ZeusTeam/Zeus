#ifndef ZEUS_BASE_BUFFER_H_
#define ZEUS_BASE_BUFFER_H_

#include "common.h"

namespace zeus
{
namespace base
{
class buffer
{
public:
    // Construct an empty buffer.
    buffer()
    {
    }

    // Construct a buffer to represent a given memory range.
    buffer(const byte* data, std::size_t size)
    {
        _buffer.data = data;
    }

public:
    const byte* data() const
    {
        return &_buffer.front();
    }

    std::size_t size() const
    {
        return _buffer.size();
    }

    bool empty() const
    {
        return _buffer.empty();
    }

private:
    std::vector<byte> _buffer;
};
}
}
#endif