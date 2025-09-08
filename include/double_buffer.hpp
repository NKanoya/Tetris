//
// Created by pilip on 2025/9/7.
//

#ifndef TETRIS_DOUBLE_BUFFER_HPP
#define TETRIS_DOUBLE_BUFFER_HPP

#include "rotate.hpp"
#include <memory>
#include <mutex>
#include <shared_mutex>

template<typename T>
class DoubleBuffer {
public:
    using value_type = T;

    template<typename... Args>
    explicit DoubleBuffer(Args&&... args)
            : m_current(std::make_unique<value_type>(std::forward<Args>(args)...)),
              m_previous(std::make_unique<value_type>(std::forward<Args>(args)...)) {}

    const T& read_current() const;

    const T& read_previous() const;

    template<typename Func>
    const T& update_current(Func&& write_func);

private:
    mutable std::shared_mutex mutex;

    std::unique_ptr<value_type> m_current;
    std::unique_ptr<value_type> m_previous;
};


template<typename T>
const T &DoubleBuffer<T>::read_current() const {
    std::shared_lock lock(mutex);
    return *m_current;
}

template<typename T>
const T &DoubleBuffer<T>::read_previous() const {
    std::shared_lock lock(mutex);
    return *m_previous;
}

template<typename T>
template<typename Func>
const T& DoubleBuffer<T>::update_current(Func&& write_func) {
    std::unique_lock lock(mutex);
    m_current.swap(m_previous);
    write_func(*m_current);
    return *m_current;
}

#endif //TETRIS_DOUBLE_BUFFER_HPP
