#include "Buffer.h"
#include <utility>

using namespace Zoran;

Buffer::Buffer(Buffer &&other) noexcept : buf(std::move(other.buf))
{
}

Buffer &Buffer::operator=(Buffer &&other) noexcept
{
    this->buf = std::move(other.buf);
    return *this;
}