#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int main()
{
	ifstream fin("problem8.txt");

	int ans = 0;

	vector<string> trees;

	string s;
	while (getline(fin, s)) {
		trees.push_back(s);
	}

	int max_scenic_score = 0;
	for (int i = 0; i < trees.size(); i++) {
		for (int j = 0; j < trees[i].size(); j++) {
			int scenic_score = 1;
			bool visible = false;
			for (int k = 0; k < 4; k++) {
				bool this_k_visible = true;
				int this_k_scenic_score = 0;
				int cur_i = i, cur_j = j;
				while (
					cur_i + dx[k] >= 0 && cur_i + dx[k] < trees.size() &&
					cur_j + dy[k] >= 0 && cur_j + dy[k] < trees[i].size()
				) {
					cur_i += dx[k];
					cur_j += dy[k];
					this_k_scenic_score += 1;
					if (trees[cur_i][cur_j] >= trees[i][j]) {
						this_k_visible = false;
						break;
					}
				}

				if (this_k_visible) {
					visible = true;
				}
				scenic_score *= this_k_scenic_score;
			}
			if (visible)
				ans++;
			if (scenic_score > max_scenic_score)
				max_scenic_score = scenic_score;
		}
	}

	cout << ans << '\n';
	cout << max_scenic_score << '\n';
}
