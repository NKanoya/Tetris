//
// Created by pilip on 2025/9/7.
//

#ifndef TETRIS_ADJACENT_STATES_HPP
#define TETRIS_ADJACENT_STATES_HPP

#include "rotate.hpp"
#include <memory>
#include <mutex>
#include <shared_mutex>

/**
 *
 * @tparam T : the value type
 */
template<typename T>
class AdjacentStates {
public:
    using value_type = T;

    template<typename... Args>
    explicit AdjacentStates(Args&&... args){
        m_current = std::make_unique<value_type>(std::forward<Args>(args)...);
        m_previous = std::make_unique<value_type>(*m_current);
    }

    const T& read_current() const;

    const T& read_previous() const;

    std::pair<const T&, const T&> read_both() const;

    template<typename Func>
    const T& update_current(Func&& write_func);

    AdjacentStates(AdjacentStates&& oth) noexcept:
        m_current(std::move(oth.m_current)),
        m_previous(std::move(oth.m_previous))
    {}
    AdjacentStates& operator=(AdjacentStates&& oth) noexcept {
        m_current = std::move(oth.m_current);
        m_previous = std::move(oth.m_previous);
    }


protected:
    mutable std::shared_mutex mutex;

    std::unique_ptr<value_type> m_current;
    std::unique_ptr<value_type> m_previous;

    // for derived class to customize the initialization
    AdjacentStates() = default;
};

template<typename T>
const T &AdjacentStates<T>::read_current() const {
    std::shared_lock lock(mutex);
    return *m_current;
}

template<typename T>
const T &AdjacentStates<T>::read_previous() const {
    std::shared_lock lock(mutex);
    return *m_previous;
}

template<typename T>
template<typename Func>
const T& AdjacentStates<T>::update_current(Func&& write_func) {
    std::unique_lock lock(mutex);
    m_current.swap(m_previous);
    write_func(*m_current);
    return *m_current;
}

template<typename T>
std::pair<const T &, const T &> AdjacentStates<T>::read_both() const {
    std::shared_lock lock(mutex);
    return {m_current, m_previous};
}

#endif //TETRIS_ADJACENT_STATES_HPP
