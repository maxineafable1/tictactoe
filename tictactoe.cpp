#include "tictactoe.h"
#include <limits>

TicTacToe::TicTacToe()
{
	board.fill(' ');
	x_score = 0;
	o_score = 0;
	x_turn = true;
}

void TicTacToe::print_board() const
{
	for (size_t i{}; i < rows; i++)
	{
		for (size_t j{}; j < cols; j++)
		{
			int index = i * cols + j;
			std::cout << "| " << board[index] << " |" << ' ';
		}
		std::cout << '\n';
		std::cout << "-----------------" << '\n';
	}
}

bool TicTacToe::valid_index(int c) const
{
	bool valid = false;
	for (size_t i{}; i < size; i++)
	{
		// check if the input is a valid number
		if (std::cin.fail())
		{
			// clear errror flags and ignore invalid input
			std::cin.clear();
			// discard invalid input
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a valid number." << '\n';
		}
		else
		{
			// if current index is empty
			if (board[i] == ' ' && i == c)
			{
				// clears remaining chars in input buffer
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				valid = true;
			}
		}
	}
	return valid;
}

const int TicTacToe::get_input() const
{
	int index;
	do
	{
		std::cout << "Enter a number (1-9): ";
		std::cin >> index;
		index--;
	} while (!valid_index(index));
	return index;
}

const char TicTacToe::set_char_on_board(int i)
{
	// char x{'x'};
	// char o{'o'};

	if (x_turn)
	{
		board[i] = x;
		x_turn = false;
		return x;
	}
	else
	{
		board[i] = o;
		x_turn = true;
		return o;
	}
}

bool TicTacToe::draw() const
{
	int count{};
	for (size_t i{}; i < size; i++)
	{
		if (board[i] != ' ')
			count++;
	}
	return count == size;
}

bool TicTacToe::winner(char player)
{
	// winning combinations
	const int arr_size{8};
	int winning_combinations[arr_size][3] = {
			{0, 1, 2}, // top row
			{3, 4, 5}, // mid row
			{6, 7, 8}, // bot row
			{0, 3, 6}, // left column
			{1, 4, 7}, // mid column
			{2, 5, 8}, // right column
			{0, 4, 8}, // diagonal from top left
			{2, 4, 6}	 // diagonal from top right
	};

	for (size_t i{}; i < arr_size; i++)
	{
		if (board[winning_combinations[i][0]] == player &&
				board[winning_combinations[i][1]] == player &&
				board[winning_combinations[i][2]] == player)
		{
			if (player == x)
				x_score++;
			else
				o_score++;
			return true;
		}
	}

	return false;
}

const char TicTacToe::play_again() const
{
	std::string input;
	do
	{
		std::cout << "Play again (y/n): ";
		std::cin >> input;
	} while (input.size() != 1);
	char res = tolower(input[0]);
	return res;
}

void TicTacToe::compare_score() const
{
	std::cout << "X Score: " << x_score << " | " << "O Score: " << o_score << '\n';
	if (x_score > o_score)
		std::cout << "X wins!" << '\n';
	else if (x_score < o_score)
		std::cout << "O wins!" << '\n';
	else
		std::cout << "It's a tie!" << '\n';
}

void TicTacToe::start()
{
	char response;
	do
	{
		board.fill(' ');
		x_turn = true;
		print_board();

		while (true)
		{
			std::cout << (x_turn ? "X's Turn" : "O's Turn") << '\n';
			int index = get_input();
			char player = set_char_on_board(index);
			print_board();
			if (winner(player))
			{
				std::cout << (x_turn ? "O Wins" : "X Wins") << '\n';
				break;
			}

			if (draw())
			{
				std::cout << "Draw" << '\n';
				break;
			}
		}
		response = play_again();
	} while (response == 'y');

	compare_score();
	std::cout << "thanks for playing" << '\n';
}