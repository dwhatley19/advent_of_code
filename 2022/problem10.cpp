#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<string> crt;

int check(int cycle, int X)
{
	if (cycle % 40 == 20) {
		return X * cycle;
	}
	return 0;
}

void fill_crt(int cycle, int X)
{
	int row = (cycle - 1) / 40;
	int column = (cycle - 1) % 40;

	bool light = abs(column - X) <= 1;
	crt[row][column] = light ? '#' : '.';
}

int main()
{
	ifstream fin("problem10.txt");

	int ans = 0;
	int X = 1, cycle = 1;
	for (int i = 0; i < 6; i++) {
		string s = "";
		for (int j = 0; j < 40; j++) {
			s += ".";
		}
		crt.push_back(s);
	}
	string instruction;
	int num;
	fill_crt(cycle, X);
	while (fin >> instruction) {
		if (instruction == "noop") {
			cycle++;
			ans += check(cycle, X);
			fill_crt(cycle, X);
		}
		if (instruction == "addx") {
			fin >> num;
			cycle++;
			ans += check(cycle, X);
			fill_crt(cycle, X);
			X += num;
			cycle++;
			ans += check(cycle, X);
			fill_crt(cycle, X);
		}
	}
	cout << ans << '\n';
	for (int i = 0; i < 6; i++) {
		cout << crt[i] << '\n';
	}
}
