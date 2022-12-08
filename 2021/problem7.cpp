#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main()
{
	ifstream fin("problem7.txt");

	vector<int> vals;

	string s;
	fin >> s;

	size_t pos = 0;
	string token, delimiter = ",";
	while ((pos = s.find(",")) != string::npos) {
		token = s.substr(0, pos);
		vals.push_back(stoi(token));
		s.erase(0, pos + delimiter.length());
	}

	int total = std::accumulate(vals.begin(), vals.end(), 0);

	int median = 462;//int(double(total) / vals.size() + 0.5);

	cout << median << '\n';

	int ans = 0;

	for (int i = 0; i < vals.size(); i++) {
		if (vals[i] < median) ans += (median - vals[i]) * ((median - vals[i]) + 1) / 2;
		else ans += (vals[i] - median) * (vals[i] - median + 1) / 2;
	}

	cout << ans << '\n';

}
