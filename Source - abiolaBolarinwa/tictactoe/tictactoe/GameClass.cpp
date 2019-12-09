#include "pch.h"
#include "GameClass.h"
#include "Computer_Ai.h"

#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>

using namespace std;

GameClass::GameClass() {
	this->player_one = 'X';
	this->player_two = 'O';
	this->player_computer = '0';
}

void GameClass::display_board() {
	system("cls");
	std::cout << "   Please Press [ R ] to Restart Game !   " << std::endl;
	std::cout << " _________________________________________" << std::endl;
	std::cout << "|                                         |" << std::endl;
	std::cout << "|      " << this->board_game[0][0] << "      |      " << this->board_game[0][1] << "      |      " << this->board_game[0][2] << "      |" << std::endl;
	std::cout << "|                                         |" << std::endl;
	std::cout << "|      " << this->board_game[1][0] << "      |      " << this->board_game[1][1] << "      |      " << this->board_game[1][2] << "      |" << std::endl;
	std::cout << "|                                         |" << std::endl;
	std::cout << "|      " << this->board_game[2][0] << "      |      " << this->board_game[2][1] << "      |      " << this->board_game[2][2] << "      |" << std::endl;
	std::cout << "|_________________________________________|" << std::endl;
	std::cout << std::endl << "Please Press [ Q ] to Return to Main Menu !" << std::endl;
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

		if (toupper(condition) == 'R') {
			wrong_input = false;
			break;
		}

		if (toupper(condition) == 'Q') {
			wrong_input = false;
			break;
		}
	}

	if (wrong_input) {
		player_input(player_symbol);
	}

	if (toupper(condition) == 'R') {
		this->restart = true;
		system("CLS");
		return;
	}
	
	if (toupper(condition) == 'Q') {
		this->back_menu = true;
		system("CLS");
		return;
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

void GameClass::evaluate_winners(string check_turn, bool two_player, int comp_wins_loses[2], int player_one_history[2], int player_two_history[2]) {
	if (check_turn == "player_computer") {
		std::cout << "[ System Message ] [ Computer has won! ]" << std::endl;
		save_game_history("player_computer", comp_wins_loses, player_one_history, player_two_history);
	}
	else if (check_turn == "player_one") {
		std::cout << "[ System Message ] [ Player One has won! ]" << std::endl;
		if (!two_player) {
			save_game_history("player_one", comp_wins_loses, player_one_history, player_two_history);
		}
	}
	else if (check_turn == "player_two") {
		std::cout << "[ System Message ] [ Player Two has won! ]" << std::endl;
	}
}

void GameClass::initialise_play(string set_turn, string username[2], bool _two_players) {
	this->player_one_user = username[0];

	this->two_players = _two_players;

	if (!_two_players) {
		this->player_two_user = "";
	}
	else {
		this->player_two_user = username[1];
	}

	int counter = 0;
	string computer_name = "player_computer";
	int comp_wins_loses[2], player_one_history[2], player_two_history[2];

	int positions_remaining = 0;

	initialise_new_game();

	while (counter != 2) {
		counter++;
	}

	if (!_two_players) {
		ifstream ifs;
		ifs.open("game_history.txt");

		if (ifs.is_open()) {
			ifs >> comp_wins_loses[0];
			ifs >> comp_wins_loses[1];
		}

		ifs.close();

		ifs.open(this->player_one_user + "_history.txt");

		if (ifs.is_open()) {
			ifs >> player_one_history[0];
			ifs >> player_one_history[1];
		}

		ifs.close();

		player_two_history[0] = NULL;
		player_two_history[1] = NULL;
	}
	
	if (this->two_players) {
		ifstream ifs;

		ifs.open(this->player_one_user + "_history.txt");

		if (ifs.is_open()) {
			ifs >> player_one_history[0];
			ifs >> player_one_history[1];
		}

		ifs.close();

		ifs.open(this->player_two_user + "_history.txt");

		if (ifs.is_open()) {
			ifs >> player_two_history[0];
			ifs >> player_two_history[1];
		}

		ifs.close();
	}

	if (this->two_players) {
		display_board();
	}

	while (!is_game_over() && positions_remaining != 9) {
		if (set_turn == "player_computer" && this->two_players == false) {
			Computer_Ai cp;
			
			cp.best_move(this->board_game, this->letter_array);
			this->board_game[cp.get_comp_row()][cp.get_comp_column()] = this->player_computer;
			display_board();
			cout << endl << "[ System Message ] [ Computer has played, Player_One's turn! ]" << endl << endl;
			positions_remaining++;
			set_turn = "player_one";
		}
		else if (set_turn == "player_one") {
			if (!this->two_players) {
				display_board();
				cout << endl;
			}
			player_input('X');

			if (this->restart) {
				this->restart = false;

				if (this->two_players == false) {
					set_turn = "player_computer";
				}

				initialise_play(set_turn, username, this->two_players);
			}

			if (this->back_menu) {
				this->back_menu = false;
				return;
			}

			display_board();
			positions_remaining++;
			if (this->two_players == false) {
				cout << endl << "[ System Message ] [ Player_One has played, Computer's turn! ]" << endl << endl;
				set_turn = "player_computer";
			}
			else {
				cout << endl << "[ System Message ] [ Player_One has played, Player_two's turn! ]" << endl << endl;
				set_turn = "player_two";
			}
		}
		else if (set_turn == "player_two" && this->two_players == true) {
			player_input('O');

			if (this->restart) {
				this->restart = false;
				initialise_play(set_turn, username, this->two_players);
			}

			if (this->back_menu) {
				this->back_menu = false;
				return;
			}


			display_board();
			cout << "[ System Message ] [ Player_Two has played, Player_One's turn! ]" << endl << endl;
			positions_remaining++;
			set_turn = "player_one";
		}
	}

	if (!is_game_over() && positions_remaining == 9) {
		std::cout << "[ System Message ] [ Game Has Drawn! ]" << std::endl;
	}
	else {
		if (set_turn == "player_computer" && this->two_players == false) {
			set_turn = "player_one";
		}
		else if (set_turn == "player_one") {
			if (this->two_players == false) {
				set_turn = "player_computer";
			}
			else {
				set_turn = "player_two";
			}
		}
		else if (set_turn == "player_two" && this->two_players == true) {
			set_turn = "player_one";
		}

		evaluate_winners(set_turn, _two_players, comp_wins_loses, player_one_history, player_two_history);
	}
}

void GameClass::initialise_ai_play() {
	string set_turn = "player_computer_one";

	int positions_remaining = 0;

	while (!is_game_over() && positions_remaining != 9) {
		if (set_turn == "player_computer_one") {
			Computer_Ai cp;

			cp.best_move(this->board_game, this->letter_array);
			this->board_game[cp.get_comp_row()][cp.get_comp_column()] = this->player_computer;
			display_board();
			cout << endl << "[ System Message ] [ Computer has played, Player_One's turn! ]" << endl << endl;
			positions_remaining++;
			set_turn = "player_computer_two";
		}
		else {
			Computer_Ai cp;

			cp.best_move(this->board_game, this->letter_array);
			this->board_game[cp.get_comp_row()][cp.get_comp_column()] = this->player_computer;
			display_board();
			cout << endl << "[ System Message ] [ Computer has played, Player_One's turn! ]" << endl << endl;
			positions_remaining++;
			set_turn = "player_computer one";
		}

		if (!is_game_over() && positions_remaining == 9) {
			std::cout << "[ System Message ] [ Game Has Drawn! ]" << std::endl;
		}
		else {
			if (set_turn == "player_computer_one") {
				set_turn = "player_computer_two";
			}
			else if (set_turn == "player_one") {
				if (this->two_players == false) {
					set_turn = "player_computer";
				}
				else {
					set_turn = "player_two";
				}
			}
			else if (set_turn == "player_two" && this->two_players == true) {
				set_turn = "player_one";
			}

		}
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

void GameClass::save_game_history(string winner, int comp_wins_loses[2], int player_one_history[2], int player_two_history[2]) {
	ofstream of;

	if (!this->two_players) {
		of.open("game_history.txt", std::ofstream::out | std::ofstream::trunc);

		int wins = comp_wins_loses[0];
		int loses = comp_wins_loses[1];

		if (winner == "player_computer") {
			of << ++wins << endl;
			of << loses;
		}
		else {
			of << wins << endl;
			of << ++loses;
		}

		of.close();

		of.open(this->player_one_user + "_history.txt", std::ofstream::out | std::ofstream::trunc);

		int player_one_wins = player_one_history[0];
		int player_one_loses = player_one_history[1];

		if (winner == "player_one") {
			of << ++player_one_wins << endl;
			of << player_one_loses << endl;
		}
		else {
			of << player_one_wins << endl;
			of << ++player_one_loses << endl;
		}

		of.close();
	}
	else {
		of.open(this->player_one_user + "_history.txt", std::ofstream::out | std::ofstream::trunc);

		int player_one_wins = player_one_history[0];
		int player_one_loses = player_one_history[1];

		if (winner == "player_one") {
			of << player_one_wins++ << endl;
			of << player_one_loses << endl;
		}
		else {
			of << player_one_wins << endl;
			of << ++player_one_loses << endl;
		}

		of.close();

		of.open(this->player_two_user + "_history.txt", std::ofstream::out | std::ofstream::trunc);

		int player_two_wins = player_one_history[0];
		int player_two_loses = player_one_history[1];

		if (winner == "player_one") {
			of << player_two_wins++ << endl;
			of << player_two_loses << endl;
		}
		else {
			of << player_two_wins << endl;
			of << ++player_two_loses << endl;
		}

		of.close();
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
