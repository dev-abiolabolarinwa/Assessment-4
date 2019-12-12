#include "pch.h"
#include "Computer_Ai.h"

#include<algorithm>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>

using namespace std::chrono_literals;

// Checks to see if there are unmarked spaces
// on the board.
bool Computer_Ai::check_moves(char board_game[3][3], char board_index[9]) {
	int index_pos = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board_game[i][j] == board_index[index_pos]) {
				return true;
			}
			index_pos++;
		}
	}
	return false;
}

// Minimax algorithm, looks for the best max value,
// or min value .
int Computer_Ai::minimax(char board_game[3][3], int tree_depth, bool min_or_max, char board_index[9]) {
	int current_score = evaluate_winner(board_game);

	if (current_score == 10) {
		return current_score;
	}
	else if (current_score == -10) {
		return current_score;
	}

	if (check_moves(board_game, board_index) == false) {
		return 0;
	}

	if (min_or_max) {
		int best_move = -1000;

		int index_pos = 0;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board_game[i][j] == board_index[index_pos]) {
					board_game[i][j] = '0';

					best_move = std::max(best_move, minimax(board_game, tree_depth + 1, !min_or_max, board_index));

					board_game[i][j] = board_index[index_pos];
				}
				index_pos++;
			}
		}
		return best_move;
	}
	else {
		int best_move = 1000;

		int index_pos = 0;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board_game[i][j] == board_index[index_pos]) {
					board_game[i][j] = 'X';

					best_move = std::max(best_move, minimax(board_game, tree_depth + 1, !min_or_max, board_index));

					board_game[i][j] = board_index[index_pos];
				}
				index_pos++;
			}
		}
		return best_move;
	}

	return 0;
	
}

// Will check the board to see who is winning and
// then return a value, + or - 10.
int Computer_Ai::evaluate_winner(char board_game[3][3]) {
	for (int row = 0; row < 3; row++) {
		if (board_game[row][0] == board_game[row][1] &&
			board_game[row][1] == board_game[row][2]) {
			if (board_game[row][0] == 'X') {
				return +10;
			}
			else if (board_game[row][0] == '0') {
				return -10;
			}

		}
	}

	for (int column = 0; column < 3; column++) {
		if (board_game[0][column] == board_game[1][column] &&
			board_game[1][column] == board_game[2][column]) {
			if (board_game[0][column] == 'X') {
				return +10;
			}
			else if (board_game[0][column] == '0') {
				return -10;
			}
		}
	}

	if (board_game[0][0] == board_game[1][1] && board_game[1][1] == board_game[2][2]) {
		if (board_game[0][0] == 'X') {
			return +10;
		}
		else if (board_game[0][0] == '0') {
			return -10;
		}
	}

	if (board_game[0][2] == board_game[1][1] && board_game[1][1] == board_game[2][0]) {
		if (board_game[0][2] == 'X') {
			return +10;
		}
		else if (board_game[0][2] == '0') {
			return -10;
		}
	}
	return 0;
}

// Get function
int Computer_Ai::get_comp_row() {
	return this->comp_row;
}

// Get function
int Computer_Ai::get_comp_column() {
	return this->comp_column;
}

// This function will traverse through the whole
// board, calling the minimax function, then returns
// the best move of the computer.
void Computer_Ai::best_move(char board_game[3][3], char board_index[9], bool min_or_max) {

	int index_pos = 0;
	int best_move = -1000;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board_game[i][j] == board_index[index_pos]) {
				board_game[i][j] = this->move_array[index_pos];

				int move = minimax(board_game, 0, min_or_max, board_index);

				board_game[i][j] = board_index[index_pos];

				if (move > best_move) {
					this->comp_row = i;
					this->comp_column = j;
					best_move = move;
				}
			}
			index_pos++;
		}
	}
	return;
}
