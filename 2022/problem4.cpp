#include <fstream>
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	ifstream fin("problem4.txt");

	int ans = 0;
	int ans2 = 0;

	string s;
	while (fin >> s) {
		int a,b,c,d;
		sscanf(s.c_str(), "%d-%d,%d-%d", &a, &b, &c, &d);

		if (a <= c && b >= d) ans++;
		else if (c <= a && d >= b) ans++;

		if (
			(a <= d && b >= d) ||
			(b >= c && a <= c) ||
			(a <= c && b >= d) ||
			(c <= a && d >= b)
		) {
			ans2++;
		}
	}

	cout << ans << endl;
	cout << ans2 << endl;
}
