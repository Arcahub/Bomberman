#ifndef CONCURRENTQUEUE_HPP_
#define CONCURRENTQUEUE_HPP_

#include <mutex>
#include <optional>
#include <queue>

template <typename T>
class ConcurrentQueue {
public:
    ConcurrentQueue() = default;
    ~ConcurrentQueue() = default;

    void push(T value)
    {
        std::lock_guard<std::mutex> lock(m_mut);

        m_queue.push(value);
    }

    size_t size()
    {
        std::lock_guard<std::mutex> lock(m_mut);

        return m_queue.size();
    }

    std::optional<T> pop()
    {
        std::lock_guard<std::mutex> lock(m_mut);

        if (m_queue.size() == 0)
            return std::nullopt;
        T ret = m_queue.front();

        m_queue.pop();
        return std::optional<T>(ret);
    }

protected:
private:
    std::mutex m_mut;
    std::queue<T> m_queue;
};

#endif /* !CONCURRENTQUEUE_HPP_ */
