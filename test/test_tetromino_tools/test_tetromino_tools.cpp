///
/// @file @c src/tetromino/tetromino.cpp
///

#include "../../include/tetromino_tools.hpp"

namespace TetroTest {

    decltype(auto) operator<<(std::ostream& os, TetrominoType t_type) {
        switch(t_type){
            case TetrominoType::tetro_O: os << "tetro_O"; return os;
            case TetrominoType::tetro_I: os << "tetro_I"; return os;
            case TetrominoType::tetro_J: os << "tetro_J"; return os;
            case TetrominoType::tetro_S: os << "tetro_S"; return os;
            case TetrominoType::tetro_L: os << "tetro_L"; return os;
            case TetrominoType::tetro_T: os << "tetro_T"; return os;
            case TetrominoType::tetro_Z: os << "tetro_Z"; return os;
            case TetrominoType::empty: os << "empty"; return os;
            default: os << "\'invalid tetro!\'";
                return os;
        }
    }

    static void test_tetromino_tools(size_t attempt_times);

    void test_tetromino_tools() {
        test_tetromino_tools(100);
        test_tetromino_tools(100);
        test_tetromino_tools(100);
        test_tetromino_tools(1000);
        test_tetromino_tools(1000);
        test_tetromino_tools(1000);
        test_tetromino_tools(10000);
    }

    static void test_tetromino_tools(size_t attempt_times) {
        std::cout << "Generate " << attempt_times << " times:\n";

        // create tetrominoes with the function new_tetromino()
        std::vector<Tetromino> vec;
        for(int i = 0; i < attempt_times; ++i) {
            vec.emplace_back(TetrominoGenerator::new_tetromino(nullptr));
        }

        // frequency statistics of tetrominoes
        int statistics[8] = {};
        // input the values
        for(auto& x: vec){
            // std::cout << x.get_type() << ' ';
            ++statistics[static_cast<int>(x.get_type())];
        }
        // output the values
        for(int i = 1; i <= 7; ++i) {
            std::cout << statistics[i] << "\t";
        }
        std::cout << std::endl;
    }

}





