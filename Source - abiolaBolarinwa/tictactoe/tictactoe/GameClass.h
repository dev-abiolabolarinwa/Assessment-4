#pragma once
class GameClass {
	private:
		char player_one = 'X';
		char player_two = 'O';
		char player_computer = '0';

		char board_game[3][3];
		char letter_array[9] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };
		
	public:
		GameClass();

		void display_board();
		void evaluate_winner(string check_turn);
		void initialise_game(char board_game[][3], int total_moves[]);
		
};

