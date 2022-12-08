#include <fstream>
#include <iostream>

using namespace std;

string seats[103];
int num_rows;

int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[8] = {-1, 1, 0, 0, 1, -1, 1, -1};

int step()
{
	string new_seats[103];
	int changed = 0;
	for (int i = 0; i < num_rows; i++) {
		string new_row = seats[i];
		for (int j = 0; j < seats[i].size(); j++) {
			int num_occupied = 0;
			for (int k = 0; k < 8; k++) {
				int si = i + dx[k], sj = j + dy[k];
				while (si >= 0 && si < num_rows && sj >= 0 && sj < seats[i].size()) {
					if (seats[si][sj] == '#') {
						num_occupied++;
						break;
					}
					if (seats[si][sj] == 'L') {
						break;
					}
					si += dx[k];
					sj += dy[k];
				}
			}
			if (num_occupied == 0 && seats[i][j] == 'L') {
				new_row[j] = '#';
				changed++;
			}
			if (num_occupied >= 5 && seats[i][j] == '#') {
				new_row[j] = 'L';
				changed++;
			}
		}
		new_seats[i] = new_row;
	}
	for (int i = 0; i < num_rows; i++) {
		seats[i] = new_seats[i];
	}
	return changed;
}

int main()
{
	ifstream fin("problem11.txt");
	string s;
	int i = 0;
	while (fin >> s) {
		seats[i] = s;
		i++;
	}
	num_rows = i;

	int changed = step();
	while (changed > 0) {
		changed = step();
	}

	int occupied = 0;
	for (int i = 0; i < num_rows; i++) {
		for (int j = 0; j < seats[i].size(); j++) {
			if (seats[i][j] == '#') occupied++;
		}
	}

	cout << occupied << '\n';
}
