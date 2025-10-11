///
/// @file @c src/tetromino/tetromino.cpp
///

#include "tetromino_tools.hpp"
#include <algorithm>


std::mt19937 TetrominoGenerator::rng(std::random_device{}());
std::uniform_int_distribution<int> TetrominoGenerator::dist(0, 6);

static void init_random_unique(int * begin);
static bool unique_in_history_queue(int random_result);


TetrominoType TetrominoGenerator::get_random_type() noexcept {
    int random_num;

    // loop check: avoid repeated type
    do {
        random_num = dist(rng);
    }
    while (!unique_in_history_queue(random_num));

    return static_cast<TetrominoType>(random_num + 1);
}

auto x_begin = 2;
auto y_begin = BlockMatrixProperties::instance_read_only().y_size / 2 - 2;

const Axis axis = {static_cast<ptrdiff_t>(x_begin),static_cast<ptrdiff_t>(y_begin)};

Tetromino TetrominoGenerator::new_tetromino(MatrixAdjacentStates * matrix_pair) noexcept {
    auto type = TetrominoGenerator::get_random_type();
    return {type, axis, matrix_pair};
}

TetrominoesPair::TetrominoesPair(Tetromino&& tetro_current, Tetromino&& tetro_upcoming):
        AdjacentStates<std::shared_ptr<Tetromino>>(),
        m_current_tetro(m_previous),
        m_upcoming_tetro(m_current) {
    m_upcoming_tetro = std::make_unique<value_type>(std::make_shared<Tetromino>(std::move(tetro_upcoming)));
    m_current_tetro = std::make_unique<value_type>(std::make_shared<Tetromino>(std::move(tetro_current)));
}

Tetromino& TetrominoesPair::get_current() noexcept {
    return **m_current_tetro;
}

TetrominoType TetrominoesPair::get_upcoming_type() const noexcept {
    return (*m_upcoming_tetro) -> get_type();
}

Tetromino &TetrominoesPair::replace_and_update(Tetromino &&new_upcoming) noexcept {
    // moves the upcoming tetromino to become the new current
    // the previous tetromino will be destructed
    m_current_tetro = std::move(m_upcoming_tetro);
    // accepts the provided tetromino as the new upcoming tetromino
    
    m_upcoming_tetro = std::make_unique<TetrominoPtr>(
                    std::make_shared<Tetromino>(std::move(new_upcoming))
                );
    // return the new current tetromino
    return **m_current_tetro;
}

bool TetrominoesPair::is_current_bottom_out() const noexcept {
    return (**(m_current_tetro)).is_bottom_out();
}


static bool unique_in_history_queue(int random_result) {
    static int list[3];
    static bool is_list_init = false;
    static int front_index = 0;

    if(!is_list_init) {
        init_random_unique(list);
        is_list_init = true;
    }

    for(int x: list) {
        if(random_result == x) {             // the random result exists in the queue
            return false;                    // failed, return false
        }
    }

    // if it succeeds
    list[front_index] = random_result;       // pop the rear value
    front_index = (front_index + 1) % 3;     // sign the new queue front
    return true;

}



static void init_random_unique(int * begin) {
    int all_numbers[] = {0, 1, 2, 3, 4, 5, 6};
    std::random_device rd;
    std::mt19937 rng(rd());
    int* current = begin;

    std::shuffle(all_numbers, all_numbers + 7, rng);
    for(int i = 0; i < 3; ++i) {
        *current = all_numbers[i];
        ++current;
    }
}





