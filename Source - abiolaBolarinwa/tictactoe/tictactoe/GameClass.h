#pragma once
#include <string>

class GameClass {
	private:
		char player_one;
		char player_two;

		std::string player_one_user;
		std::string player_two_user;

		bool restart = false;
		bool back_menu = false;

		bool two_players = false;

		char player_computer;

		char board_game[3][3];
		char letter_array[9] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };
		
	public:
		GameClass();
		
		void display_board();
		void player_input(char player_symbol);
		void evaluate_winners(std::string check_turn, bool two_player, int comp_wins_loses[2], int player_one_history[2], int player_two_history[2]);
		void initialise_play(std::string set_turn, std::string username[2], bool _two_players);
		void initialise_ai_play();
		void initialise_new_game();
		void save_game_history(std::string winner, int comp_wins_loses[2], int player_one_history[2], int player_two_history[2]);

		bool is_game_over();
		bool row_traversed(char board_game[][3]);
		bool column_traversed(char board_game[][3]);
		bool diagonal_traversed(char board_game[][3]);

		~GameClass();
		
};

