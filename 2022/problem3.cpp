#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

#define NUM_CHARS 52

vector<int> get_freq_array(string s)
{
	vector<int> freq_array(NUM_CHARS);
	for (int i = 0; i < s.size(); i++) {
		if ('a' <= s[i]) freq_array[s[i] - 'a'] += 1;
		else if (s[i] <= 'Z') freq_array[s[i] - 'A' + NUM_CHARS/2] += 1;
	}
	return freq_array;
}

int main()
{
	ifstream fin("problem3.txt");

	int ans = 0;
	int ans2 = 0;

	vector<string> v;

	string s;
	while (fin >> s) {
		v.push_back(s);
		string s1 = s.substr(0, s.size()/2);
		string s2 = s.substr(s.size()/2);
		vector<int> freq1 = get_freq_array(s1);
		vector<int> freq2 = get_freq_array(s2);
		for (int i = 0; i < NUM_CHARS; i++) {
			if (freq1[i] * freq2[i] > 0) {
				ans += i + 1;
			}
		}
	}

	for (int a = 0; a < v.size(); a += 3) {
		string s1 = v[a], s2 = v[a + 1], s3 = v[a + 2];
		vector<int> freq1 = get_freq_array(s1);
		vector<int> freq2 = get_freq_array(s2);
		vector<int> freq3 = get_freq_array(s3);
		for (int i = 0; i < NUM_CHARS; i++) {
			if (freq1[i] * freq2[i] * freq3[i] > 0) ans2 += i + 1;
		}
	}

	cout << ans << endl;
	cout << ans2 << endl;
}
