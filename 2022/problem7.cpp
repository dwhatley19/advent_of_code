#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

long long MAX_SZ = 100000;
long long MAX_SPACE = 70000000;
long long UNUSED_SPACE = 30000000;

int main()
{
	ifstream fin("problem7.txt");

	long long ans = 0;

	string s;
	vector<string> cur_dir;
	set<string> visited_dirs;
	map<string, long long> sizes;
	while (getline(fin, s)) {
		stringstream ss;
		string start, cmd, dir;
		long long sz;
		string file_name;
		if (s[0] == '$') {
			if (s[2] == 'l') continue;
			ss << s;
			ss >> start >> cmd >> dir;

			if (dir == "..") {
				cur_dir.pop_back();
			} else {
				// REEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
				while (visited_dirs.find(dir) != visited_dirs.end()) {
					dir += "a";
				}
				visited_dirs.insert(dir);
				cur_dir.push_back(dir);
			}
		} else {
			if (s[0] >= '0' && s[0] <= '9') {
				ss << s;
				ss >> sz >> file_name;

				for (long long j = 0; j < cur_dir.size(); j++) {
					if (sizes.find(cur_dir[j]) != sizes.end()) {
						sizes[cur_dir[j]] += sz;
					} else {
						sizes[cur_dir[j]] = sz;
					}
				}
			}
		}
	}

	long long avail_space = 30000000 - (MAX_SPACE - sizes["/"]);
	long long smallest = MAX_SPACE;

	for (map<string, long long>::iterator it = sizes.begin(); it != sizes.end(); it++) {
		if (it->second <= MAX_SZ) {
			ans += it->second;
		}
		if (it->second >= avail_space && it->second < smallest) {
			smallest = it->second;
		}
	}

	cout << ans << endl;
	cout << smallest << endl;
}
