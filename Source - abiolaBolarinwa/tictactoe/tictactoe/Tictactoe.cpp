// tictactoe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "GameClass.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

void display_menu();
void display_menu_one();
void display_game_menu_one(int number);
void display_game_history();

bool exit_game = true;
bool both_comp = false;
bool determine_players = false;

int players_length;

string player_user[2];


int main() {
	while (::exit_game) {
		GameClass new_game;
		display_menu();

		if (::exit_game == false) {
			break;
		}

		if (!::determine_players) {
			if (::both_comp) {
				new_game.initialise_ai_play();
				
			}
			else {
				new_game.initialise_play("player_computer", ::player_user, ::determine_players);
			}
		}
		else {
			new_game.initialise_play("player_one", ::player_user, ::determine_players);
		}

	} 
}

// Prints Main menu, that asks for player input.
void display_menu() {
	int menu_selector;

	std::cout << "TIC TAC TOE - Game Main Menu" << std::endl << std::endl;
	std::cout << "1. New Game" << std::endl;
	std::cout << "2. Game History" << std::endl;
	std::cout << "3. Quit Game" << std::endl << std::endl;
	std::cout << "Please select one of the options above (1 -3): ";

	std::cin >> menu_selector;

	while (!std::cin) {
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "[ System Message ] [ Please enter a letter from 1 - 3 ]" << std::endl << std::endl;
		std::cout << "Please select one of the following conditions from 1 - 3 that have not been selected: ";
		std::cin >> menu_selector;
	}

	if (menu_selector == 1) {
		system("CLS");
		display_menu_one();
		system("CLS");
	}
	else if (menu_selector == 2) {
		system("CLS");
		display_game_history();
		system("CLS");
		display_menu();
	}
	else if (menu_selector == 3) {
		::exit_game = false;
	}
	else {
		system("CLS");
		std::cout << "[ System Message ] [ Wrong Input ] [ Please enter a numeriacal value between 1 - 3 ]" << std::endl << std::endl << std::endl;
		display_menu();
	}
}

// Prints menu and asks player for input, returns
// new function depending on players input.
void display_menu_one() {
	char menu_selector;

	std::cout << std::endl << "TIC TAC TOE - New Game Menu" << std::endl << std::endl;
	std::cout << "1. Player_one vs Computer_ai" << std::endl;
	std::cout << "2. Player_one vs Player_two" << std::endl;
	std::cout << "3. Computer_ai_one vs Computer_ai_two" << std::endl;
	std::cout << "4. Back to main menu" << std::endl << std::endl;
	std::cout << "Please select one of the options above (1 -3): ";

	std::cin >> menu_selector;
		
	while (!std::cin) {
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "[ System Message ] [ Please enter a letter from 1 - 3 ]" << std::endl << std::endl;
		std::cout << "Please select one of the following conditions from 1 - 3 that have not been selected: ";
		std::cin >> menu_selector;
	}	

	if (menu_selector == '1') {
		::determine_players = false;

		std::cin.clear();
		std::cin.ignore(100, '\n');
		display_game_menu_one(1);
		return;
	}
	else if (menu_selector == '2') {
		::determine_players = true;
		system("CLS");
		display_game_menu_one(1);
		system("CLS");
		display_game_menu_one(2);
		std::cout << std::endl;
		return;
	}
	else if (menu_selector == '3') {
		::both_comp = true;
		return;
	}
	else if (menu_selector == '4') {
		display_menu();
	}
	else {
		std::cout << "[ System Message ] [ Wrong Input ] [ Please enter a numeriacal value between 1 - 3 ]" << std::endl << std::endl << std::endl;
		display_menu_one();
	}
}

// Gets Users Username and creates a new file.
void display_game_menu_one(int number) {
	ofstream ofs;
	ifstream ifs;
	std::string username;

	if (number == 1) {
		std::cout << "Please enter the Player_One's Initials of length 3: ";		
	}
	else if (number == 2) {
		std::cout << "Please enter the Player_Two's Initials of length 3: ";
	}
	
	std::getline(std::cin, username);

	std::for_each(username.begin(), username.end(), [](char& c) {
		c = ::toupper(c);
	});

	::player_user[number - 1] = username;

	string row[2];
	row[0] = "0";
	row[1] = "0";

	ifs.open("player_history.txt", std::ifstream::binary);

	int length_get;
	string* users;

	if (ifs.is_open()) {
		ifs.seekg(0, ifs.end);
		std::streamoff length = ifs.tellg();
		length_get = (int)length;
		ifs.seekg(0, ifs.beg);
	}
	else {
		length_get = 0;
		return;
	}

	users = new string[length_get];

	for (int i = 0; i < length_get; i++) {
		ifs >> users[i];

		if (users[i] == "") {
			::players_length = i;
			break;
		}
	}

	ifs.close();
	bool cont = true;

	for (int i = 0; i < 2; i++) {
		if (users[i] == username) {
			cont = false;
			break;
		}
	}

	if (cont) {
		if (username.length() == 3) {
			ifs.open(username + "_history.txt");

			if (!ifs.is_open()) {
				ofs.open(username + "_history.txt");

				if (ofs.is_open()) {
					ofs << row[0] << endl;
					ofs << row[1] << endl;
				}

				ofs.close();
			}

			ifs.close();

			ofs.open("player_history.txt", ios::out | ios::app);
			ofs << username << endl;
			::players_length++;
			ofs.close();


		}
		else {
			display_game_menu_one(number);
		}
	}
	std::cout << std::endl;
}

// Prints Player Game History.
void display_game_history() {
	ifstream ifs;

	ifs.open("player_history.txt", std::ifstream::binary);

	int length = 0;
	string* users;

	if (ifs.is_open()) {
		ifs.seekg(0, ifs.end);
		length = (int) ifs.tellg();
		ifs.seekg(0, ifs.beg);
	}
	else {
		length = 0;
		return;
	}

	users = new string[length];

	for (int i = 0; i < length; i++) {
		ifs >> users[i];

		if (users[i] == "") {
			::players_length = i;
			break;
		}
	}

	ifs.close();

	int length1 = ::players_length;

	std::cout << " ________________________________________________________" << std::endl;
	std::cout << "|           Players           |    Wins    |    Loses    |" << std::endl;
	std::cout << "|_____________________________|____________|_____________|" << std::endl;
	
	
	
	int comp_wins_lose[2];

	ifs.open("game_history.txt");

	ifs >> comp_wins_lose[0];
	ifs >> comp_wins_lose[1];

	ifs.close();
	std::cout << "|                             |            |             |" << std::endl;
	std::cout << "|         " << "[ COMP_AI ]" << "         |      " << comp_wins_lose[0] << "     |      " << comp_wins_lose[1] << "      |" << std::endl;

	int wins_lose[100][2];
	
	for (int i = 0; i < length1; i++) {
		ifs.open(users[i] + "_history.txt");

		ifs >> wins_lose[i][0];
		ifs >> wins_lose[i][1];

		ifs.close();
	}

	for (int i = 0; i < length1; i++) {
		std::cout << "|----------------------------- ------------ -------------|" << std::endl;
		std::cout << "|             " << users[i] << "             | "<< "     " << wins_lose[i][0] << "     |      " << wins_lose[i][1] << "      |" << std::endl;
	}
	std::cout << "|----------------------------- ------------ -------------|" << std::endl;
	std::cout << "|_____________________________|____________|_____________|" << std::endl << std::endl;

	std::cout << "       Please Press [ R ]  to return to Main Menu !       " << std::endl;

	int get_return;

	do {
		get_return = _getch();
		get_return = toupper(get_return);

	} while (get_return != 'R');


	return;
}