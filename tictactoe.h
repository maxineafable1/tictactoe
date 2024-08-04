#include <iostream>
#include <array>

#ifndef TICTACTOE_H
#define TICTACTOE_H

constexpr std::size_t size = 9;

class TicTacToe
{
private:
    std::array<char, size> board;
    const int rows{3};
    const int cols{3};
    // unsigned int score;
    bool x_turn;

    void print_board() const;
    const int get_input() const;
    bool valid_index(const int &c) const;
    bool winner(const char &player) const;
    const char set_char_on_board(const int &i);
    bool draw() const;
    const char play_again() const;

public:
    TicTacToe();
    void start();
};

#endif