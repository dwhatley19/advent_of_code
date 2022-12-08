#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <queue>
using namespace std;

typedef pair<int, int> pii;
#define A first
#define B second

int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};

bool visited[105][105];

int get_basin_size(vector<string> heatmap, int i, int j) {

	queue<pii> q;
	q.push(pii(i, j));
	visited[i][j] = true;

	int ans = 1;

	while (!q.empty()) {
		pii cur = q.front();
		int next_i = cur.A, next_j = cur.B;
		// cout << next_i << ' ' << next_j << '\n';
		q.pop();
		for (int k = 0; k < 4; k++) {
			if (next_i + dx[k] < 0 || next_i + dx[k] >= heatmap.size()) {
				continue;
			}
			if (next_j + dy[k] < 0 || next_j + dy[k] >= heatmap[next_i].size()) {
				continue;
			}
			if (
				!visited[next_i + dx[k]][next_j + dy[k]] &&
				heatmap[next_i][next_j] < heatmap[next_i + dx[k]][next_j + dy[k]] &&
				heatmap[next_i + dx[k]][next_j + dy[k]] != '9'
			) {
				visited[next_i + dx[k]][next_j + dy[k]] = true;
				q.push(pii(next_i + dx[k], next_j + dy[k]));
				ans++;
			}
		}
	}

	return ans;
}

int main()
{
	ifstream fin("problem9.txt");

	int ans1 = 0;
	vector<int> basin_sizes;

	vector<string> heatmap;
	vector<string> visited;

	string s;
	while (fin >> s) {
		heatmap.push_back(s);
	}

	for (int i = 0; i < heatmap.size(); i++) {
		for (int j = 0; j < heatmap[i].size(); j++) {
			int num_less = 0;
			for (int k = 0; k < 4; k++) {
				if (i + dx[k] < 0 || i + dx[k] >= heatmap.size()) {
					num_less++;
					continue;
				}
				if (j + dy[k] < 0 || j + dy[k] >= heatmap[i].size()) {
					num_less++;
					continue;
				}
				if (heatmap[i][j] < heatmap[i + dx[k]][j + dy[k]]) num_less++;
			}
			if (num_less == 4) {
				ans1 += heatmap[i][j] - '0' + 1;
				basin_sizes.push_back(get_basin_size(heatmap, i, j));
			}
		}
	}

	cout << ans1 << '\n';

	sort(basin_sizes.begin(), basin_sizes.end());

	cout << basin_sizes[basin_sizes.size() - 1] * basin_sizes[basin_sizes.size() - 2] * basin_sizes[basin_sizes.size() - 3] << '\n';
}
