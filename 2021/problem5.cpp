#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 1005, LINES = 500;

int overlap[MAX_SIZE][MAX_SIZE];

int main()
{
	ifstream fin("problem5.txt");

	for (int i = 0; i < LINES; i++) {
		string a, b, c;
		fin >> a >> b >> c;

		int apos = a.find(","), cpos = c.find(",");
		int x1 = stoi(a.substr(0, apos)), y1 = stoi(a.substr(apos + 1)), x2 = stoi(c.substr(0, cpos)), y2 = stoi(c.substr(cpos + 1));

		double slope = double(y2 - y1) / double(x2 - x1);
		int minx = min(x1, x2), maxx = max(x1, x2);
		int miny = min(y1, y2), maxy = max(y1, y2);

		if (x1 == x2) {
			for (int i = miny; i <= maxy; i++) {
				overlap[i][x1] += 1;
			}
		}
		else if (y1 == y2) {
			for (int i = minx; i <= maxx; i++) {
				overlap[y1][i] += 1;
			}
		}
		else if ((slope + 1) < 1e-8) {
			for (int i = 0; i <= maxx-minx; i++) {
				overlap[maxy-i][minx+i] += 1;
			}
		}
		else if ((slope - 1) < 1e-8) {
			for (int i = 0; i <= maxx-minx; i++) {
				overlap[miny+i][minx+i] += 1;
			}
		}
	}

	int pts = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			if (overlap[i][j] > 1) pts++;
		}
	}

	cout << pts << '\n';
}
