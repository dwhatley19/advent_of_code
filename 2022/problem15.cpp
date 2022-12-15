#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
using namespace std;

const int ROW = 2000000;
const int MAX_COORD = 4000000;

typedef pair<int, int> pii;
#define A first
#define B second

int iabs(int x) { return (x < 0) ? -x : x; }

vector<pii> get_unacceptable_ranges(vector<pii> sensor_positions, vector<pii> beacon_positions, int row)
{
    vector<pii> result;
    for (int i = 0; i < beacon_positions.size(); i++) {
        int x1 = sensor_positions[i].A, y1 = sensor_positions[i].B, x2 = beacon_positions[i].A, y2 = beacon_positions[i].B;
        int manhattan = iabs(x2 - x1) + iabs(y2 - y1);
        int dist_from_row = iabs(y1 - row);
        if (dist_from_row <= manhattan) {
            int min_x = x1 - (manhattan - dist_from_row), max_x = x1 + (manhattan - dist_from_row);
            result.push_back(pii(min_x, max_x));
        }
    }
    return result;
}

int main()
{
    ifstream fin("problem15.txt");

    string s;
    vector<pii> sensor_positions, beacon_positions;
    while (getline(fin, s)) {
        int x1, y1, x2, y2;
        sscanf(s.c_str(), "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", &x1, &y1, &x2, &y2);
        sensor_positions.push_back(pii(x1, y1));
        beacon_positions.push_back(pii(x2, y2));
    }

    vector<pii> part_1_ranges = get_unacceptable_ranges(sensor_positions, beacon_positions, ROW);
    set<int> unacceptable_positions;
    for (int i = 0; i < part_1_ranges.size(); i++) {
        for (int j = part_1_ranges[i].A; j <= part_1_ranges[i].B; j++) {
            unacceptable_positions.insert(j);
        }
    }

    for (int i = 0; i < beacon_positions.size(); i++) {
        int x2 = beacon_positions[i].A, y2 = beacon_positions[i].B;
        if (y2 == ROW && unacceptable_positions.find(x2) != unacceptable_positions.end()) {
            unacceptable_positions.erase(x2);
        }
    }

    cout << unacceptable_positions.size() << endl;

    for (int i = 0; i <= MAX_COORD; i++) {
        int highest_y_so_far = 0;
        vector<pii> unacceptable_ranges = get_unacceptable_ranges(sensor_positions, beacon_positions, i);
        sort(unacceptable_ranges.begin(), unacceptable_ranges.end());
        for (int j = 0; j < unacceptable_ranges.size() - 1; j++) {
            highest_y_so_far = max(highest_y_so_far, unacceptable_ranges[j].B);
            if (highest_y_so_far < unacceptable_ranges[j + 1].A) {
                cout << (long long)(highest_y_so_far + 1) * (long long)(MAX_COORD) + (long long)(i) << '\n';
                return 0;
            }
        }
    }
}
