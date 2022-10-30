#pragma once
#include <vector>
#include <stdint.h>
#include <string.h>
#include <type_traits>

namespace Zoran
{
    //  ____         __  __
    // | __ ) _   _ / _|/ _| ___ _ __
    // |  _ \| | | | |_| |_ / _ \ '__|
    // | |_) | |_| |  _|  _|  __/ |
    // |____/ \__,_|_| |_|  \___|_|
    // TODO:实现自己的数据结构
    // 用于接受数据的Buffer数据结构
    // 能够设置缓冲区的大小范围
    // 模仿类似 char* 的行为, 并且可以强转成char *
    // 可以动态设置缓冲区的大小
    //
    class Buffer
    {
        // 属性相关操作
        // size => Buffer的空闲大小
        // dataSize => Buffer内存储的数据大小
        // capacity => Buffer的总共大小
        // data     => Buffer的数据
        // buffer => Buffer的空闲位置
    public:
        // 获取Buffer剩余空间大小
        std::size_t size() const noexcept
        {
            return buf.capacity() - buf.size();
        }

        // 获取Buffer数据大小
        std::size_t dataSize() const noexcept
        {
            return buf.size();
        }

        // 获取容量  [总大小]
        std::size_t capacity() const noexcept
        {
            return buf.capacity();
        }

        // 获取数据
        char *data() noexcept
        {
            return buf.data();
        }

        // 获取空闲Buffer
        char *buffer() noexcept
        {
            return buf.data() + this->dataSize();
        }
        // 行为相关操作
        // reserve => 设置Buffer能够存储数据的大小
        // update  => 接受数据后, 更新Buffer内数据的大小   [无参数, 则使用strlen()自动计算]
    public:
        // 设置容量大小
        void reserve(std::size_t capacity) noexcept
        {
            buf.reserve(buf.size() + capacity);
        }

        // 更新接收后的的长度
        void update(int64_t size) noexcept
        {
            buf.resize(buf.size() + size);
        }

        // 接收完了以后更新size大小
        void update() noexcept
        {
            buf.resize(strlen(buf.data()));
        }

        // 模仿类似 char* 的行为, 并且可以强转成char *
        operator char *()
        {
            //返回空闲位置的指针
            return this->buffer();
        }

        // TODO: 重载流运算符>> 来输出Buffer的数据
        template <typename T>
        friend Buffer &operator<<(Buffer &buffer, T &val)
        {
            static_assert(std::is_standard_layout_v<T>, "Your DataType is too complex!");

            // 获取原本数据的位置
            auto pos = buffer.dataSize();

            // 更新buffer的数据大小
            buffer.update(sizeof(T));
            // 拷贝内存到Buffer
            memcpy(buffer.data() + pos, &val, sizeof(T));

            return buffer;
        }

        template <typename T>
        friend Buffer &operator>>(Buffer &buffer, T &val)
        {
            // 判断类型能否是标准布局
            static_assert(std::is_standard_layout_v<T>, "Your DataType is too complex!");

            // 计算该内存的位置
            char *pos = buffer.buffer() - sizeof(T);

            // 拷贝数据到变量中
            memcpy(&val, pos, sizeof(T));

            // 更新数据大小
            buffer.update(-sizeof(T));
            return buffer;
        }

        // 默认函数
    public:
        ~Buffer() = default;
        explicit Buffer(std::size_t capacity = 1) noexcept
        {
            buf.reserve(capacity);
        }

        Buffer(Buffer &buf) = delete;
        Buffer operator=(Buffer &buf) = delete;

        Buffer(Buffer &&buf) noexcept;
        Buffer &operator=(Buffer &&buf) noexcept;

    private:
        std::vector<char> buf;
    };
}