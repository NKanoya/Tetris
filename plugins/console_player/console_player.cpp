#include "console_player.hpp"
#include "../../include/operation.hpp"
#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif


/**
 * <p>implementations of functions of class @c BitMask
 *
 * <p>declared at @c matrix_state_manager.hpp
 */

namespace ConsolePlayer {
    static const char * const block_figure_ = "█▉";

    void ConsolePrinter::output_matrix(const RunningBlockMatrix& matrix) const noexcept {
        // clear previous output
        std::cout << "\033[2J\033[H";

        // traverse all blocks
        for(size_t x = *prop_buffer_size_ptr; x < *prop_x_axis_ptr; ++x) {
            for(size_t y = 0; y < *prop_y_axis_ptr; ++y) {
                // check the type of the block
                if( matrix.get_block(x,y) != TetrominoType::empty) {
                    std::cout << block_figure_;
                } else {
                    std::cout << "··";
                }
            }
            // enter the row
            std::cout << '\n';
        }

    }

    ConsolePrinter::ConsolePrinter() :
            prop_x_axis_ptr(&(BlockMatrixProperties::instance_read_only().x_size)),
            prop_y_axis_ptr(&(BlockMatrixProperties::instance_read_only().y_size)),
            prop_buffer_size_ptr(&(BlockMatrixProperties::instance_read_only().x_buffer_size)) {

    }

    void ConsolePrinter::output(const ConsolePrinter::ProcessData &data) const noexcept {
        output_matrix(data.matrix);
    }

    //
    // ConsoleScanner
    //
    Operation ConsoleScanner::input() {
        char c;
#ifdef _WIN32
        c = _getch();
#else
        termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);

        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);

        newt.c_cc[VMIN] = 1;
        newt.c_cc[VTIME] = 0;

        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        read(STDIN_FILENO, &c, 1);

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

        switch(c) {
            case 'A':
            case 'a':
                return Operation::Left;
            case 'D':
            case 'd':
                return Operation::Right;
            case 'E':
            case 'e':
                return Operation::RotateCCW;
            case 'Q':
            case 'q':
                return Operation::RotateCCW;
            case 'S':
            case 's':
                return Operation::Drop;
            default: return Operation::None;
        }

    }
}
