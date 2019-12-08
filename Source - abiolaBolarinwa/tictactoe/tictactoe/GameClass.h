#pragma once
#include <string>

class GameClass {
	private:
		char player_one;
		char player_two;
		char player_computer;

		char board_game[3][3];
		char letter_array[9] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };
		
	public:
		GameClass();
		
		void display_board();
		void player_input(char player_symbol);
		void evaluate_winners(std::string check_turn);
		void initialise_play(std::string set_turn, bool two_players);
		void initialise_new_game();

		bool is_game_over();
		bool row_traversed(char board_game[][3]);
		bool column_traversed(char board_game[][3]);
		bool diagonal_traversed(char board_game[][3]);		

		~GameClass();
		
};

