#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ifstream fin("problem1.txt");

	int cur_sum = 0;
	int max_sum = 0;

	vector<int> v;

	string line;

	while (getline(fin, line)) {
		stringstream ss;
		if (line == "") {
			if (cur_sum > max_sum) {
				max_sum = cur_sum;
			}
			v.push_back(cur_sum);
			cur_sum = 0;
		} else {
			ss << line;
			int num;
			ss >> num;
			cur_sum += num;
		}
	}

	sort(v.begin(), v.end());

	cout << max_sum << endl;

	cout << v[v.size()-1] + v[v.size()-2] + v[v.size()-3] << '\n';
}
