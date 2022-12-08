#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	ifstream fin("problem3.txt");

	vector<int> zeros;

	int one = 0, two = 0;

	vector<string> strings;

	string s;
	while (fin >> s) {
		strings.push_back(s);
		for (int i = 0; i < s.size(); i++) {
			if (i >= zeros.size()) zeros.push_back(0);
			if (s[i] == '0') zeros[i] += 1;
		}
	}

	string most_common = "", least_common = "";

	vector<string> old_strings = strings;

	for (int x = 0; x < 2; x++) {
		int index = 0;
		while (true) {
			vector<string> new_strings;
			int half = strings.size() / 2;
			int zeros = 0;
			for (int i = 0; i < strings.size(); i++) {
				if (strings[i][index] == '0') {
					zeros++;
				}
			}
			for (int i = 0; i < strings.size(); i++) {
				if (strings[i][index] == '0' && ((x == 0 && zeros > half) || (x == 1 && zeros <= half))) {
					new_strings.push_back(strings[i]);
				}
				if (strings[i][index] == '1' && ((x == 0 && zeros <= half) || (x == 1 && zeros > half))) {
					new_strings.push_back(strings[i]);
				}
			}
			strings = new_strings;
			if (strings.size() == 1) {
				cout << strings[0] << '\n';
				break;
			}
			index++;
		}
		strings = old_strings;
	}
}
