#include "pch.h"
#include "GameClass.h"

#include <iostream>

using namespace std;

GameClass::GameClass() {	}

void GameClass::display_board() {
	cout << this->board_game[0][0] << " | " << this->board_game[0][1] << " | " << this->board_game[0][2] << endl;
	cout << this->board_game[1][0] << " | " << this->board_game[1][1] << " | " << this->board_game[1][2] << endl;
	cout << this->board_game[2][0] << " | " << this->board_game[2][1] << " | " << this->board_game[2][2] << endl;
}

void GameClass::evaluate_winner(string check_turn) {
	if (check_turn == "player_computer") {
		cout << "[ System Message ] [ Computer has won! ]" << endl;
	}
	else if (check_turn == "player_one") {
		cout << "[ System Message ] [ Player One has won! ]" << endl;
	}
	else if (check_turn == "player_two") {
		cout << "[ System Message ] [ Player Two has won! ]" << endl;
	}
}

void GameClass::initialise_game(char board_game[][3], int total_moves[]) {
	int array_traversed = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->board_game[i][j] = this->letter_array[array_traversed];
			array_traversed++;
		}
	}

	for (int i = 0; i < 9; i++) {
		total_moves[i] = i;
	}
}

