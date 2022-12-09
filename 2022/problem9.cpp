#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef pair<long long, long long> pii;
#define A first
#define B second

long long dx[4] = {0, 0, 1, -1};
long long dy[4] = {1, -1, 0, 0};
float eps = 0.00001;

void solve(int num_knots)
{
	ifstream fin("problem9.txt");

	long long ans = 0;

	vector<pii> cur_pos;
	for (int i = 0; i < num_knots; i++) cur_pos.push_back(pii(0, 0));
	set<string> s;
	s.insert("0,0");

	char c;
	long long i;
	while (fin >> c >> i) {
		long long k = 0;
		if (c == 'U') k = 0;
		if (c == 'D') k = 1;
		if (c == 'R') k = 2;
		if (c == 'L') k = 3;

		int j = 0;
		for (j = 0; j < i; j++) {
			cur_pos[num_knots - 1] = pii(cur_pos[num_knots - 1].A + dx[k], cur_pos[num_knots - 1].B + dy[k]);

			for (int knot = num_knots - 1; knot >= 1; knot--) {
				if (abs(float(cur_pos[knot].A - cur_pos[knot - 1].A)) > 1+eps) {
					cur_pos[knot - 1].A += (cur_pos[knot - 1].A < cur_pos[knot].A) ? 1 : -1;

					if (cur_pos[knot - 1].B != cur_pos[knot].B) {
						cur_pos[knot - 1].B += (cur_pos[knot - 1].B < cur_pos[knot].B) ? 1 : -1;
					}
				}

				if (abs(float(cur_pos[knot].B - cur_pos[knot - 1].B)) > 1+eps) {
					cur_pos[knot - 1].B += (cur_pos[knot - 1].B < cur_pos[knot].B) ? 1 : -1;

					if (cur_pos[knot - 1].A != cur_pos[knot].A) {
						cur_pos[knot - 1].A += (cur_pos[knot - 1].A < cur_pos[knot].A) ? 1 : -1;
					}
				}
			}

			stringstream ss;
			ss << cur_pos[0].A << ',' << cur_pos[0].B;
			s.insert(ss.str());
		}
	}

	cout << s.size() << '\n';
}

int main()
{
	solve(2);
	solve(10);
}
