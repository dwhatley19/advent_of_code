#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 1005, LINES = 500;

int overlap[MAX_SIZE][MAX_SIZE];

int main()
{
	ifstream fin("problem6.txt");

	vector<int> vals;

	string s;
	fin >> s;

	size_t pos = 0;
	string token, delimiter = ",";
	while ((pos = s.find(",")) != string::npos) {
		token = s.substr(0, pos);
		vals.push_back(stoi(token));
		s.erase(0, pos + delimiter.length());
	}

	long long ans = 0;

	vector<long long> new_fish_vec;

	for (int i = 0; i < 14; i++) {
		vector<int> old_vals = vals;
		int new_fish = 0;
		for (int j = 0; j < old_vals.size(); j++) {
			if (vals[j] == 0) {
				vals[j] = 6;
				vals.push_back(8);
				new_fish++;
			} else {
				vals[j]--;
			}
		}
		cout << vals.size() << ' ' << new_fish << '\n';
		new_fish_vec.push_back(new_fish);
	}

	ans = vals.size();
	for (int i = 14; i < 256; i++) {
		long long next_val = new_fish_vec[i - 9] + new_fish_vec[i - 7];
		new_fish_vec.push_back(next_val);
		ans += next_val;
	}

	cout << ans << '\n';
}
