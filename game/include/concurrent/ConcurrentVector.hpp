/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** ConcurrentVector
*/

#ifndef CONCURRENTVECTOR_HPP_
#define CONCURRENTVECTOR_HPP_

#include <mutex>
#include <optional>
#include <vector>

template <typename T>
class ConcurrentVector {
public:
    ConcurrentVector() = default;
    ~ConcurrentVector() = default;

    void push_back(T value)
    {
        std::lock_guard<std::mutex> lock(m_mut);

        m_vec.push_back(value);
    }

    size_t size()
    {
        std::lock_guard<std::mutex> lock(m_mut);

        return m_vec.size();
    }

    T& at(size_t index)
    {
        std::lock_guard<std::mutex> lock(m_mut);

        return m_vec.at(index);
    }

    std::vector<T> copy()
    {
        std::lock_guard<std::mutex> lock(m_mut);
        std::vector<T> ret(m_vec);

        return ret;
    }

    void clear()
    {
        std::lock_guard<std::mutex> lock(m_mut);

        m_vec.clear();
    }

    void performSafeThreadAction(std::function<void(std::vector<T>&)> func)
    {
        std::lock_guard<std::mutex> lock(m_mut);

        func(m_vec);
    }

    void remove(T value)
    {
        std::lock_guard<std::mutex> lock(m_mut);
        size_t index = 0;
        bool found = false;

        for (long i = 0; i < (long)m_vec.size(); i++) {
            if (m_vec.at(i) == value) {
                found = true;
                index = i;
                break;
            }
        }
        if (found) {
            m_vec.erase(m_vec.begin() + index);
        }
    }

    T operator[](size_t index)
    {
        std::lock_guard<std::mutex> lock(m_mut);

        return m_vec[index];
    }

protected:
private:
    std::vector<T> m_vec;
    std::mutex m_mut;
};

#endif /* !CONCURRENTVECTOR_HPP_ */
