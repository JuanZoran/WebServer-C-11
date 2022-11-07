#pragma once
#include <queue>
#include <condition_variable>
#include <type_traits>
#include <utility>
#include <mutex>

// 任务队列
// 线程安全:
// 1. 无锁, 使用原子变量
// 2. 使用互斥锁

template <typename message>
class MessageQueue final
{
public:
    // 成员方法
    message pop() noexcept;
    void push(const message &val) noexcept;
    void push(message &&val) noexcept;
    size_t size() const noexcept;

public:
    MessageQueue() = default;
    ~MessageQueue() = default;

    MessageQueue(MessageQueue &) = delete;
    MessageQueue &operator=(MessageQueue &) = delete;

public:
    using size_t = std::size_t;

private:
    using Q_t = std::queue<message>;
    using lock_t = std::mutex;
    using cond_t = std::condition_variable;
    using guard_t = std::unique_lock<lock_t>;

private:
    // 创建任务队列
    Q_t queue;

    // 生产者消费者用到的条件变量
    cond_t consumer;
    lock_t q_lock;
};

template <typename message>
message MessageQueue<message>::pop() noexcept
{
    guard_t lk(q_lock);
    // 必须 queue内有元素
    consumer.wait(lk, [this]
                  { return !queue.empty(); });
    message res = queue.front();
    queue.pop();
    return res;
}

template <typename message>
void MessageQueue<message>::push(const message &val) noexcept
{
    {
        // 申请锁
        guard_t lk(q_lock);
        // 插入元素
        queue.push(val);
    }

    // 唤醒消费者
    consumer.notify_one();
}

template <typename message>
void MessageQueue<message>::push(message &&val) noexcept
{
    {
        // 申请锁
        guard_t lk(q_lock);
        // 插入元素
        if constexpr (std::is_nothrow_move_constructible<message>::value)
            queue.emplace(std::move(val));
        else
            queue.push(val);
    }

    // 唤醒消费者
    consumer.notify_one();
}

template <typename message>
size_t MessageQueue<message>::size() const noexcept
{
    return queue.size();
}
