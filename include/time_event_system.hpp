//
// Created by pilip on 2025/9/15.
//

#ifndef TETRIS_time_event_system_HPP
#define TETRIS_time_event_system_HPP

#include <chrono>
#include <functional>
#include <thread>
#include "operation.hpp"
#include "matrix_state_manager.hpp"

template <size_t frame>
class TickCircle {
private:

    // timing widgets
    using FrameDuration = std::chrono::duration<int64_t, std::ratio<1, frame>>;
    FrameDuration m_target_duration;
    FrameDuration m_current_duration;
    std::chrono::steady_clock::time_point m_start_time;
    size_t m_frame_count;
    double m_smoothing_factor;
    size_t m_forced_operation_frame;

    // callback functions
    using ProcessData = MatrixStateManager::ProcessData;
    using CommandFunc = std::function<Operation()>;
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
            m_target_duration(tick_count),
            m_current_duration(tick_count),
            m_frame_count(0),
            m_smoothing_factor(smoothing),
            // forced
            m_forced_operation_frame(forced_operation_time / FrameDuration(1)),
            // initialize the callback functions
            m_command_func(std::move(command_func)),
            m_process_func(std::move(process_func)),
            m_render_func(std::move(render_func)) {}

    void game_loop();
};

template<size_t frame>
void TickCircle<frame>::game_loop() {
    bool is_game_over;
    auto init_data = m_process_func(Operation::None);
    m_render_func(init_data);

    do {
        Operation operation;
        if(m_frame_count == m_forced_operation_frame) {
            operation = Operation::Down;
            m_frame_count = 0;
        } else {
            operation = m_command_func();
        }
        auto data = m_process_func(operation);
        m_render_func(data);
        // check if the game is over
        is_game_over = data.is_game_over;
        wait_for_next_frame();
    } while(!is_game_over);
}

template<size_t frame>
void TickCircle<frame>::wait_for_next_frame() {
    // increase the frame count
    m_frame_count++;

    // compare time of next frame and current time
    auto next_frame_time = m_start_time + m_frame_count * m_target_duration;
    auto current_time = std::chrono::steady_clock::now();

    // wait until time of next frame
    if (current_time < next_frame_time) {
        std::this_thread::sleep_until(next_frame_time);
    }

    // adapt
    auto actual_duration = current_time - (next_frame_time - m_target_duration);
    auto actual_duration_cast = std::chrono::duration_cast<FrameDuration>(actual_duration);

    // smoothly update the current time
    m_current_duration = FrameDuration(
            static_cast<int64_t>(
                    m_smoothing_factor * actual_duration_cast.count() +
                    (1 - m_smoothing_factor) * m_current_duration.count()
            )
    );

    // 如果持续超时，适当放宽目标
    if (actual_duration > m_target_duration * 1.1) { // 超时10%
        m_target_duration = FrameDuration(
                static_cast<int64_t>(m_target_duration.count() * 1.05) // 放宽5%
        );
    }
        // 如果运行很快，可以尝试提高要求
    else if (actual_duration < m_target_duration * 0.9) { // 提前10%
        m_target_duration = FrameDuration(
                static_cast<int64_t>(m_target_duration.count() * 0.95) // 收紧5%
        );
    }
}

#endif //TETRIS_time_event_system_HPP
