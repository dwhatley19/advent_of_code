#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, int> piii;
#define A first
#define B second

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int get_fewest_steps(vector<string> v, int s_x, int s_y, int e_x, int e_y)
{
    vector<vector<bool> > visited;
    for (int i = 0; i < v.size(); i++) {
        vector<bool> vis_row(v[i].size());
        visited.push_back(vis_row);
    }

    queue<piii> q;
    q.push(piii(pii(s_x, s_y), 0));
    visited[s_x][s_y] = true;
    
    while (!q.empty()) {
        piii cur = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            if (
                cur.A.A + dx[i] >= 0 && cur.A.A + dx[i] < v.size() &&
                cur.A.B + dy[i] >= 0 && cur.A.B + dy[i] < v[0].size() &&
                v[cur.A.A + dx[i]][cur.A.B + dy[i]] - v[cur.A.A][cur.A.B] <= 1 &&
                !visited[cur.A.A + dx[i]][cur.A.B + dy[i]]
            ) {
                visited[cur.A.A + dx[i]][cur.A.B + dy[i]] = true;
                if (cur.A.A + dx[i] == e_x && cur.A.B + dy[i] == e_y) {
                    return cur.B + 1;
                }
                q.push(piii(pii(cur.A.A + dx[i], cur.A.B + dy[i]), cur.B + 1));
            }
        }
    }

    return -1;
}

int main()
{
    ifstream fin("problem12.txt");
    string s;
    vector<string> v;
    int s_x, s_y, e_x, e_y;
    int row = 0;
    while (fin >> s) {
        v.push_back(s);
        string::iterator index_of_s = find(s.begin(), s.end(), 'S');
        string::iterator index_of_e = find(s.begin(), s.end(), 'E');
        if (index_of_s != s.end()) {
            s_x = row;
            s_y = index_of_s - s.begin();
        }
        if (index_of_e != s.end()) {
            e_x = row;
            e_y = index_of_e - s.begin();
        }
        row++;
    }
    v[s_x][s_y] = 'a';
    v[e_x][e_y] = 'z';
    int sxy = get_fewest_steps(v, s_x, s_y, e_x, e_y);
    cout << sxy << '\n';
    int fewest_fewest_steps = sxy;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            if (v[i][j] == 'a') {
                int this_sxy = get_fewest_steps(v, i, j, e_x, e_y);
                if (this_sxy != -1 && this_sxy < fewest_fewest_steps) {
                    fewest_fewest_steps = this_sxy;
                }
            }

        }
    }
    cout << fewest_fewest_steps << endl;
}
