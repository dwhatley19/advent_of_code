#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;
using FunctionPtr = bool (int, int);

string subtract(string str1, string str2)
{
	int nums1[26], nums2[26];
	string diff = "";
	for (int i = 0; i < 26; i++) {
		nums1[i] = 0;
		nums2[i] = 0;
	}
	for (int i = 0; i < str1.size(); i++) {
		nums1[str1[i] - 'a'] += 1;
	}
	for (int i = 0; i < str2.size(); i++) {
		nums2[str2[i] - 'a'] += 1;
	}
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < abs(nums1[i] - nums2[i]); j++) {
			diff += ('a' + i);
		}
	}
	return diff;
}

bool test_strings(string str1, string str2, FunctionPtr pred)
{
	int nums1[26], nums2[26];
	bool yes = true;
	for (int i = 0; i < 26; i++) {
		nums1[i] = 0;
		nums2[i] = 0;
	}
	for (int i = 0; i < str1.size(); i++) {
		nums1[str1[i] - 'a'] += 1;
	}
	for (int i = 0; i < str2.size(); i++) {
		nums2[str2[i] - 'a'] += 1;
	}
	for (int i = 0; i < 26; i++) {
		if (pred(nums1[i], nums2[i])) yes = false;
	}
	return yes;
}

bool is_anagram(string str1, string str2)
{
	return test_strings(str1, str2, [](int a, int b){ return a != b; });
}

bool is_subset(string str1, string str2)
{
	return test_strings(str1, str2, [](int a, int b){ return a > b; });
}


vector<string> decode(vector<string> input)
{
	vector<string> out(10);

	for (int i = 0; i < input.size(); i++) {
		if (input[i].size() == 2) {
			out[1] = input[i];
		} else if (input[i].size() == 4) {
			out[4] = input[i];
		} else if (input[i].size() == 3) {
			out[7] = input[i];
		} else if (input[i].size() == 7) {
			out[8] = input[i];
		}
	}

	string top = subtract(out[7], out[1]);
	string leftmid = subtract(out[4], out[1]);

	for (int i = 0; i < input.size(); i++) {
		if (input[i].size() == 6) {
			if (is_subset(out[1], input[i]) && is_subset(leftmid, input[i])) {
				out[9] = input[i];
			} else if (is_subset(out[1], input[i])) {
				out[0] = input[i];
			} else {
				out[6] = input[i];
			}
		} else if (input[i].size() == 5) {
			if (is_subset(top, input[i]) && is_subset(leftmid, input[i])) {
				out[5] = input[i];
			} else if (is_subset(out[1], input[i])) {
				out[3] = input[i];
			} else {
				out[2] = input[i];
			}
		}
	}

	return out;
}

int decode(vector<string> encoded, vector<string> digits)
{
	int ans = 0;

	vector<string> decoded = decode(encoded);

	for (int i = 0; i < digits.size(); i++) {
		for (int j = 0; j < decoded.size(); j++) {
			if (is_anagram(digits[i], decoded[j])) {
				ans *= 10;
				ans += j;
			}
		}
	}

	return ans;
}

int main()
{
	ifstream fin("problem8.txt");

	int ans = 0;

	for (int i = 0; i < 200; i++) {
		int decoded = 0;
		vector<string> input;
		vector<string> digits;
		for (int j = 0; j < 15; j++) {
			string s;
			fin >> s;
			if (j < 10) {
				input.push_back(s);
			}
			if (j > 10) {
				digits.push_back(s);
			}
		}
		ans += decode(input, digits);
	}

	cout << ans << '\n';

}
