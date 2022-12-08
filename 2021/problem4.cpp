#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int BOARD_SIZE = 5;
int MAX_STEPS = 10000;

int board_winning_steps(vector<vector<int> > board, vector<int> winning)
{
	int min_overall = MAX_STEPS;
	for (int i = 0; i < BOARD_SIZE; i++) {
		int max_in_row = 0;
		for (int j = 0; j < BOARD_SIZE; j++) {
			auto it = find(winning.begin(), winning.end(), board[i][j]);
			if (it != winning.end()) {
				max_in_row = max(max_in_row, int(it - winning.begin()));
			}
		}
		min_overall = min(min_overall, max_in_row);
	}

	for (int j = 0; j < BOARD_SIZE; j++) {
		int max_in_col = 0;
		for (int i = 0; i < BOARD_SIZE; i++) {
			auto it = find(winning.begin(), winning.end(), board[i][j]);
			if (it != winning.end()) {
				max_in_col = max(max_in_col, int(it - winning.begin()));
			}
		}
		min_overall = min(min_overall, max_in_col);
	}

	return min_overall;
}

int main()
{
	ifstream fin("problem4.txt");

	vector<int> winning;
	vector<vector<vector<int> > > boards;

	string s;
	fin >> s;

	size_t pos = 0;
	string token, delimiter = ",";
	while ((pos = s.find(",")) != string::npos) {
		token = s.substr(0, pos);
		winning.push_back(stoi(token));
		s.erase(0, pos + delimiter.length());
	}

	vector<int> board_winning_steps_vec;

	while (true) {
		bool bad = false;
		vector<vector<int> > board;
		for (int i = 0; i < BOARD_SIZE; i++) {
			vector<int> board_row;
			for (int j = 0; j < BOARD_SIZE; j++) {
				int x;
				if (!(fin >> x)) bad = true;
				board_row.push_back(x);
			}
			board.push_back(board_row);
		}

		if (bad) break;

		boards.push_back(board);

		// figure out # steps it takes for board to win
		board_winning_steps_vec.push_back(board_winning_steps(board, winning));
	}

	int argmin = std::distance(board_winning_steps_vec.begin(), std::max_element(board_winning_steps_vec.begin(), board_winning_steps_vec.end()));
	int min_steps = board_winning_steps_vec[argmin];

	int unmarked_sum = 0;

	for (int i = 0; i < BOARD_SIZE; i++) {
		int max_in_row = 0;
		for (int j = 0; j < BOARD_SIZE; j++) {
			auto it = find(winning.begin(), winning.end(), boards[argmin][i][j]);
			if (it != winning.end() && it - winning.begin() > min_steps) {
				unmarked_sum += boards[argmin][i][j];
			}
		}
	}

	cout << unmarked_sum * winning[min_steps] << '\n';
}
