#pragma once
#include <cstring>
// #include <iostream>
#include <stdint.h>
#include <cassert>

namespace Zoran
{
    template <int N>
    class Buffer
    {

    private:
        uint32_t m_dataSize = 0;
        char tot[N] = {0};

    public:
        uint32_t size() const noexcept { return N - m_dataSize; }
        uint32_t capacity() const noexcept { return N; }
        uint32_t dataSize() const noexcept { return m_dataSize; }

        char *data() noexcept { return tot; }
        char *buffer() noexcept { return tot + m_dataSize; }
        void update(int size) noexcept { m_dataSize += size; }

    public:
        operator char *() { return tot + m_dataSize; }

        template <typename T>
        Buffer &operator<<(T &&value) noexcept
        {
            assert(N - m_dataSize >= sizeof(T));
            memcpy(tot + m_dataSize, &value, sizeof(T));
            // std::cout << "拷贝完成" << value << std::endl;
            m_dataSize += sizeof(T);
            return *this;
        }

        template <typename T>
        Buffer &operator>>(T &&value) noexcept
        {
            assert(m_dataSize >= sizeof(T));
            uint32_t i = m_dataSize - sizeof(T);
            memcpy(&value, tot + i, sizeof(T));
            m_dataSize -= sizeof(T);
            return *this;
        }
    };
} // namespace Zoran
