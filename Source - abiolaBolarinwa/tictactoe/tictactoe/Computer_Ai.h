#pragma once
class Computer_Ai {
	private:
		int comp_column = -1;
		int comp_row = -1;
		char move_array[9] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };
	public:
		bool check_moves(char board_game[3][3], char board_index[9]);

		int minimax(char board_game[3][3], int tree_depth, bool min_or_max, char board_index[9]);
		int evaluate_winner(char board_game[3][3]);
		int get_comp_row();
		int get_comp_column();

		void best_move(char board_game[3][3], char board_index[9], bool min_or_max);
};