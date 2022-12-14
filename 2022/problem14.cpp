#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <sstream>
using namespace std;

const int SAND_X = 500, SAND_Y = 0;
bool blocked[1000][1000];

bool will_next_sand_fall(int max_y)
{
    int cur_sand_x = SAND_X, cur_sand_y = SAND_Y;
    while (cur_sand_y <= max_y) {
        if (!blocked[cur_sand_x][cur_sand_y+1]) cur_sand_y++;
        else if (!blocked[cur_sand_x-1][cur_sand_y+1]) {
            cur_sand_y++;
            cur_sand_x--;
        }
        else if (!blocked[cur_sand_x+1][cur_sand_y+1]) {
            cur_sand_y++;
            cur_sand_x++;
        }
        else break;
    }

    blocked[cur_sand_x][cur_sand_y] = true;

    if (cur_sand_y > max_y) return true;
    return false;
}

int main()
{
    ifstream fin("problem14.txt");

    string s;
    int ans = 0;
    int max_y = 0;
    while (getline(fin, s)) {
        stringstream ss;
        ss << s;
        string instruction;
        int prev_x = -1, prev_y = -1;
        while (ss >> instruction) {
            if (s == "->") continue;

            int x, y;
            sscanf(instruction.c_str(), "%d,%d", &x, &y);
            max_y = max(max_y, y);

            if (prev_x > 0 && prev_y > 0) {
                if (prev_x == x) {
                    for (int i = min(prev_y, y); i <= max(prev_y, y); i++) {
                        blocked[x][i] = true;
                    }
                } else if (prev_y == y) {
                    for (int i = min(prev_x, x); i <= max(prev_x, x); i++) {
                        blocked[i][y] = true;
                    }
                }
            }
            prev_x = x;
            prev_y = y;
        }
    }

    // Part 1
    // while (!will_next_sand_fall(max_y)) ans++;

    for (int i = 0; i < 1000; i++) {
        blocked[i][max_y + 2] = true;
    }

    while (!blocked[SAND_X][SAND_Y]) {
        will_next_sand_fall(max_y);
        ans++;
    }

    cout << ans << endl;
}
