#include "../../../include/time_event_system.hpp"
#include <optional>


OperationQueue::OperationQueue() : m_mtx(),
                                   m_op_queue() {}

std::optional<Operation> OperationQueue::try_pop() {
    // get the mutex
    std::lock_guard<std::mutex> lock(m_mtx);
    // check if there is ready
    if (m_op_queue.empty()) {
        // return null value
        return std::nullopt;
    }
    // get the pop the front operation
    Operation op = m_op_queue.front();
    m_op_queue.pop();

    return op;
}

void OperationQueue::push(Operation operation) {
    std::lock_guard<std::mutex> lock(m_mtx);
    m_op_queue.push(operation);
}