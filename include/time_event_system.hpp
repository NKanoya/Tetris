//
// Created by pilip on 2025/9/15.
//

#ifndef TETRIS_time_event_system_HPP
#define TETRIS_time_event_system_HPP

#include <chrono>
#include <functional>
#include <thread>
#include "operation.hpp"
#include <optional>
#include <queue>
#include "matrix_state_manager.hpp"

/**
 * @brief a shared queue of operation between command input thread and render operation
 */
class OperationQueue {
    std::queue<Operation> m_op_queue;
    std::mutex m_mtx;
public:
    OperationQueue();

    void push(Operation operation);

    std::optional<Operation> try_pop();
};

template <size_t frame>
class TickCircle {
private:
    // timing widgets
    using FrameDuration = std::chrono::duration<int64_t, std::ratio<1, frame>>;
    FrameDuration m_target_duration;
    FrameDuration m_current_duration;
    std::chrono::steady_clock::time_point m_start_time;
    std::chrono::steady_clock::time_point m_prev_frame_time;
    size_t m_frame_count;
    double m_smoothing_factor;
    size_t m_forced_operation_frame;

    // callback functions
    using ProcessData = MatrixStateManager::ProcessData;
    using CommandFunc = std::function<OperationQueue&()>;
    using ProcessFunc = std::function<ProcessData(Operation)>;
    using RenderFunc = std::function<void(const ProcessData&)>;
    CommandFunc m_command_func;
    ProcessFunc m_process_func;
    RenderFunc m_render_func;

    void wait_for_next_frame();

public:
    TickCircle(std::chrono::milliseconds forced_operation_time,
               CommandFunc command_func,
               ProcessFunc process_func,
               RenderFunc render_func,
               size_t tick_count = 1,
               double smoothing = 0.1):
    // initialize the properties of time count
            m_target_duration(FrameDuration(tick_count)),
            m_current_duration(FrameDuration(tick_count)),
            m_frame_count(0),
            m_smoothing_factor(smoothing),
            // forced
            m_forced_operation_frame(static_cast<size_t>(forced_operation_time / FrameDuration(1))),
            // initialize the callback functions
            m_command_func(std::move(command_func)),
            m_process_func(std::move(process_func)),
            m_render_func(std::move(render_func)) {
        m_start_time = std::chrono::steady_clock::now();
        m_prev_frame_time = m_start_time;
    }

    void game_loop();
};

template<size_t frame>
void TickCircle<frame>::game_loop() {
    bool is_game_over;
    auto init_data = m_process_func(Operation::None);
    m_render_func(init_data);

    // reset timing for the main loop
    m_start_time = std::chrono::steady_clock::now();
    m_prev_frame_time = m_start_time;
    m_frame_count = 0;

    do {
        Operation operation;
        if(m_forced_operation_frame > 0 && m_frame_count % m_forced_operation_frame == 0) {
            operation = Operation::Down;
        } else {
            // recieve the queue
            auto& queue = m_command_func();
            auto opt = queue.try_pop();
            if(opt.has_value()) {
                operation = opt.value();
            } else {
                operation = Operation::None;
            }
        }

        auto data = m_process_func(operation);
        m_render_func(data);

        // check if the game is over
        is_game_over = data.is_game_over;

        wait_for_next_frame();
        m_frame_count++;
    } while(!is_game_over);
}

template<size_t frame>
void TickCircle<frame>::wait_for_next_frame() {
    // calculate when the next frame should start
    auto next_frame_time = m_start_time + std::chrono::duration_cast<std::chrono::steady_clock::duration>((m_frame_count + 1) * m_target_duration);
    auto current_time = std::chrono::steady_clock::now();

    // wait until it's time for the next frame
    if (current_time < next_frame_time) {
        std::this_thread::sleep_until(next_frame_time);
        current_time = std::chrono::steady_clock::now();
    }

    // calculate the actual time taken for this frame
    auto frame_start = m_prev_frame_time;
    auto frame_end = current_time;
    auto actual_duration = std::chrono::duration_cast<FrameDuration>(frame_end - frame_start);

    // update smoothed duration
    m_current_duration = FrameDuration(
            static_cast<int64_t>(
                    m_smoothing_factor * actual_duration.count() +
                    (1 - m_smoothing_factor) * m_current_duration.count()
            )
    );

    // update previous frame time for next iteration
    m_prev_frame_time = current_time;
}

#endif //TETRIS_time_event_system_HPP
