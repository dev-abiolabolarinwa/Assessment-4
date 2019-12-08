#include "pch.h"
#include "GameClass.h"
#include "Computer_Ai.h"

#include <iostream>
#include <string>

using namespace std;

GameClass::GameClass() {
	this->player_one = 'X';
	this->player_two = 'O';
	this->player_computer = '0';
}

void GameClass::display_board() {
	std::cout << this->board_game[0][0] << " | " << this->board_game[0][1] << " | " << this->board_game[0][2] << std::endl;
	std::cout << this->board_game[1][0] << " | " << this->board_game[1][1] << " | " << this->board_game[1][2] << std::endl;
	std::cout << this->board_game[2][0] << " | " << this->board_game[2][1] << " | " << this->board_game[2][2] << std::endl;
}

void GameClass::player_input(char player_symbol) {
	char condition;	

	std::cout << "Please select one of the following conditions from A - I that have not been selected: ";
	std::cin >> condition;

	while (!cin) {
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "[ System Message ] [ Please enter a letter from A - Z ]" << std::endl << std::endl;
		std::cout << "Please select one of the following conditions from A - I that have not been selected: ";
		std::cin >> condition;
	}

	bool wrong_input = true;

	for (int i = 0; i < 9; i++) {
		if (toupper(condition) == this->letter_array[i]) {
			wrong_input = false;
		}
	}

	if (wrong_input) {
		player_input(player_symbol);
	}

	int index = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (toupper(condition) == this->board_game[i][j] && toupper(condition) != 'X' && toupper(condition) != 'O' && toupper(condition) != '0') {
				this->board_game[i][j] = player_symbol;
			}
			index++;
		}
	}
}

void GameClass::evaluate_winners(string check_turn) {
	if (check_turn == "player_computer") {
		std::cout << "[ System Message ] [ Computer has won! ]" << std::endl;
	}
	else if (check_turn == "player_one") {
		std::cout << "[ System Message ] [ Player One has won! ]" << std::endl;
	}
	else if (check_turn == "player_two") {
		std::cout << "[ System Message ] [ Player Two has won! ]" << std::endl;
	}
}

void GameClass::initialise_play(string set_turn, bool two_players) {
	int positions_remaining = 0;

	initialise_new_game();

	display_board();

	while (!is_game_over() && positions_remaining != 9) {
		if (set_turn == "player_computer" && two_players == false) {
			Computer_Ai cp;
			
			cp.best_move(this->board_game, this->letter_array);
			this->board_game[cp.get_comp_row()][cp.get_comp_column()] = this->player_computer;
			display_board();
			positions_remaining++;
			set_turn = "player_one";
		}
		else if (set_turn == "player_one") {
			player_input('X');
			display_board();
			positions_remaining++;
			if (two_players == false) {
				set_turn = "player_computer";
			}
			else {
				set_turn = "player_two";
			}
		}
		else if (set_turn == "player_two" && two_players == true) {
			player_input('O');
			display_board();
			positions_remaining++;
			set_turn = "player_one";
		}
	}

	if (!is_game_over() && positions_remaining == 9) {
		std::cout << "[ System Message ] [ Game Has Drawn! ]" << std::endl;
	}
	else {
		if (set_turn == "player_computer" && two_players == false) {
			set_turn = "player_one";
		}
		else if (set_turn == "player_one") {
			if (two_players == false) {
				set_turn = "player_computer";
			}
			else {
				set_turn = "player_two";
			}
		}
		else if (set_turn == "player_two" && two_players == true) {
			set_turn = "player_one";
		}

		evaluate_winners(set_turn);
	}
}

void GameClass::initialise_new_game() {
	int array_traversed = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->board_game[i][j] = this->letter_array[array_traversed];
			array_traversed++;
		}
	}
}

bool GameClass::is_game_over() {
	return(row_traversed(this->board_game) || column_traversed(this->board_game) || diagonal_traversed(this->board_game));
}

bool GameClass::row_traversed(char board_game[][3]) {
	for (int i = 0; i < 3; i++) {
		if ((this->board_game[i][0] == this->board_game[i][1]) &&
			(this->board_game[i][1] == this->board_game[i][2]) &&
			(this->board_game[i][0] != ' ' )) {
			return true;
		}
	}

	return false;
}

bool GameClass::column_traversed(char board_game[][3]) {
	for (int i = 0; i < 3; i++) {
		if ((this->board_game[0][i] == this->board_game[1][i]) &&
			(this->board_game[1][i] == this->board_game[2][i]) &&
			(this->board_game[0][i] != ' ')) {
			return true;
		}
	}

	return false;
}

bool GameClass::diagonal_traversed(char board_game[][3]) {
	if ((this->board_game[0][0] == this->board_game[1][1]) &&
		(this->board_game[1][1] == this->board_game[2][2]) &&
		(this->board_game[0][0] != ' ')) {
		return true;
	}

	if ((this->board_game[0][2] == this->board_game[1][1]) &&
		(this->board_game[1][1] == this->board_game[2][0]) &&
		(this->board_game[0][2] != ' ')) {
		return true;
	}

	return false;
}



GameClass::~GameClass() {	}
