// tictactoe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "GameClass.h"

#include <iostream>
#include <string>

void display_menu();
void display_menu_one();
void display_menu_two();
void display_menu_three();

bool determine_players = false;

int main() {
	GameClass new_game;

	if (!::determine_players) {
		new_game.initialise_play("player_comp", ::determine_players);
	}
	else {
		new_game.initialise_play("player_one", ::determine_players);
	}
}

void display_menu() {
	int menu_selector;

	std::cout << "TIC TAC TOE - Game Main Menu" << std::endl;
	std::cout << "1. New Game" << std::endl;
	std::cout << "2. Game History" << std::endl;
	std::cout << "3. Quit Game" << std::endl;
	std::cout << "Please select one of the options above (1 -3): ";

	std::cin >> menu_selector;

	while (!std::cin) {
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "[ System Message ] [ Please enter a letter from 1 - 3 ]" << std::endl << std::endl;
		std::cout << "Please select one of the following conditions from 1 - 3 that have not been selected: ";
		std::cin >> menu_selector;
	}

	if (menu_selector != 1 || menu_selector != 2 || menu_selector != 3) {
		std::cout << "[ System Message ] [ Wrong Input ] [ Please enter a numeriacal value between 1 - 3 ]" << std::endl << std::endl << std::endl;

		display_menu();
	}

	if (menu_selector == 1) {
		display_menu_one();

	}
	else if (menu_selector == 2) {
		display_menu_two();

	}
	else if (menu_selector == 3) {
		display_menu_three();

	}
}

void display_menu_one() {
	int menu_selector;

	std::cout << "TIC TAC TOE - New Game Menu" << std::endl;
	std::cout << "1. Player_one vs Computer_ai" << std::endl;
	std::cout << "2. Player_one vs Player_two" << std::endl;
	std::cout << "3. Back to main menu" << std::endl;
	std::cout << "Please select one of the options above (1 -3): ";

	std::cin >> menu_selector;

	while (!std::cin) {
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cout << "[ System Message ] [ Please enter a letter from 1 - 3 ]" << std::endl << std::endl;
		std::cout << "Please select one of the following conditions from 1 - 3 that have not been selected: ";
		std::cin >> menu_selector;
	}

	if (menu_selector != 1 || menu_selector != 2 || menu_selector != 3) {
		std::cout << "[ System Message ] [ Wrong Input ] [ Please enter a numeriacal value between 1 - 3 ]" << std::endl << std::endl << std::endl;

		display_menu_one();
	}

	if (menu_selector == 1) {
		::determine_players = false;
	}
	else if (menu_selector == 2) {
		::determine_players = true;
	}
	else if (menu_selector == 3) {
		display_menu();
	}
}

void display_menu_two() {

}

void display_menu_three() {

}
