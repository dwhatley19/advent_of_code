#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ifstream fin("problem2.txt");

	int ans1 = 0;
	int ans2 = 0;

	char a, b;
	while (fin >> a >> b) {
		int a1 = a - 'A';
		int a2 = b - 'X';

		int diff = a1 - a2;
		if (diff < 0) diff += 3;
		if (diff == 2) {
			ans1 += a2 + 1 + 6;
		} else if (diff == 1) {
			ans1 += a2 + 1;
		} else {
			ans1 += a2 + 1 + 3;
		}

		int choose = a1 - (a2 == 0 ? 1 : a2 == 1 ? 0 : 2);
		if (choose < 0) choose += 3;
		ans2 += choose + 1 + (a2 == 0 ? 0 : a2 == 1 ? 3 : 6);
	}

	cout << ans1 << endl;
	cout << ans2 << endl;
}
