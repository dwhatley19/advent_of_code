#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int main()
{
	ifstream fin("problem13.txt");
	int t;
	fin >> t;

	string s;
	fin >> s;

	vector<int> buses;
	size_t pos = 0;
	int num_items = 0;
	while ((pos = s.find(',')) != string::npos) {
	    string token = s.substr(0, pos);
	    if (token != "x") {
	    	stringstream ss;
	    	int bus_id;
	    	ss << token;
	    	ss >> bus_id;
	    	buses.push_back(bus_id);
	    }
	    s.erase(0, pos + 1);
	    num_items--;
	}
	// cout << num_items << '\n';
	buses.push_back(17);

	int lowest_mins = 1e6;
	int product = 0;
	for (int i = 0; i < buses.size(); i++) {
		int mins = buses[i] - t % buses[i];
		if (mins < lowest_mins) {
			lowest_mins = mins;
			product = mins * buses[i];
		}
	}

	cout << product << '\n';
}
