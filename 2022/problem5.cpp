#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

int COLUMNS = 9;
vector<stack<char> > input_stacks(1000);
vector<stack<char> > stacks(1000);

bool PART_2 = true;

int main()
{
	ifstream fin("problem5.txt");

	string ans = "";
	int ans2 = 0;

	string s;
	bool flag = false;
	while (getline(fin, s)) {
		if (s.size() < 2) continue;
		if (s[1] == '1') {
			flag = true;
			for (int i = 0; i < COLUMNS; i++) {
				while (!input_stacks[i].empty()) {
					stacks[i].push(input_stacks[i].top());
					input_stacks[i].pop();
				}
			}
			continue;
		}

		if (!flag) {
			COLUMNS = (s.size() + 1) / 4;
			for (int i = 0; i < 4 * COLUMNS; i += 4) {
				char c = s[i + 1];
				if (c != ' ') input_stacks[i / 4].push(c);
			}
		}
		else {
			int a, b, c;
			sscanf(s.c_str(), "move %d from %d to %d", &a, &b, &c);
			for (int i = 0; i < a; i++) {
				stacks[c - 1].push(stacks[b - 1].top());
				stacks[b - 1].pop();
			}
			if (PART_2) {
				queue<char> temp_q;
				for (int i = 0; i < a; i++) {
					temp_q.push(stacks[c - 1].top());
					stacks[c - 1].pop();
				}
				for (int i = 0; i < a; i++) {
					stacks[c - 1].push(temp_q.front());
					temp_q.pop();
				}
			}
		}
	}

	ans = "";
	for (int i = 0; i < COLUMNS; i++) {
		ans += stacks[i].top();
	}

	cout << ans << '\n';
}
