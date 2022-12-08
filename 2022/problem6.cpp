#include <fstream>
#include <iostream>
#include <set>

using namespace std;

int NUM_CHARS = 14;//4;

int main()
{
	ifstream fin("problem6.txt");

	int ans = 0;
	int ans2 = 0;

	string s;
	while (getline(fin, s)) {
		for (int i = 0; i < s.size() - NUM_CHARS; i++) {
			set<char> st;
			for (int j = 0; j < NUM_CHARS; j++) {
				st.insert(s[i+j]);
			}
			if (st.size() == NUM_CHARS) {
				cout << i + NUM_CHARS << '\n';
				break;
			}
		}
	}
}
