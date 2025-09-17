//
// Created by pilip on 2025/9/13.
//

#ifndef TETRIS_console_player_HPP
#define TETRIS_console_player_HPP

#include "../../include/matrix_state_manager.hpp"
#include "../../include/time_event_system.hpp"
#include <thread>                 // for std::thread and std::mutex

class Score {
    int m_score;
public:
    Score() : m_score(0) {}

    inline int get_score() const {
        return m_score;
    }

    inline void add_score(int score) {
        m_score += score;
    }

};

namespace ConsolePlayer {

    class ConsolePrinter {
    public:
        using ProcessData = MatrixStateManager::ProcessData;

        void output(const ProcessData& data) const noexcept;

        void output_matrix(const RunningBlockMatrix& matrix) const noexcept;

        ConsolePrinter();

        mutable Score m_score;

    private:
        const size_t* prop_x_axis_ptr;
        const size_t* prop_y_axis_ptr;
        const size_t* prop_buffer_size_ptr;
    };

    class ConsoleScanner {
    public:
        OperationQueue shared_operation_queue;
    private:
        std::atomic<bool> m_scan_over;
        std::thread m_scan_thread;
    public:

        ConsoleScanner();
        ~ConsoleScanner();

        void receive_command();

        inline OperationQueue& get_operation_queue(){
            return shared_operation_queue;
        };
    };


}

#endif //TETRIS_console_player_HPP
