#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int PART = 1;

int main()
{
    ifstream fin("problem11.txt");

    int ans = 0;

    vector<vector<long long> > monkeys;
    vector<string> operations;
    vector<long long> divs;
    vector<long long> tmonkeys, fmonkeys;
    vector<long long> monkey_business;
    string s;
    int step_in_monkey = 0;
    while (fin >> s) {
        if (step_in_monkey == 0) {
            vector<long long> v;
            monkeys.push_back(v);
            monkey_business.push_back(0);
            fin >> s; // X:
            fin >> s; // Starting
            step_in_monkey = 1;
        }
        else if (step_in_monkey == 1) {
            do {
                fin >> s;
                stringstream ss;
                if (s[s.size() - 1] == ',') ss << s.substr(0, s.size() - 1);
                else ss << s;
                int item;
                ss >> item;
                monkeys[monkeys.size() - 1].push_back(item);
            } while (s[s.size() - 1] == ',');
            step_in_monkey = 2;
        }
        else if (step_in_monkey == 2) {
            string a, b, c, d, e;
            fin >> a >> b >> c >> d >> e;
            operations.push_back(d+e);
            step_in_monkey = 3;
        }
        else if (step_in_monkey == 3) {
            string a, b;
            int div;
            fin >> a >> b >> div;
            divs.push_back(div);

            int tmonkey, fmonkey;
            fin >> s; // If
            fin >> s; // true:
            fin >> s; // throw
            fin >> s; // to
            fin >> s; // monkey
            fin >> tmonkey;

            fin >> s; // If
            fin >> s; // false:
            fin >> s; // throw
            fin >> s; // to
            fin >> s; // monkey
            fin >> fmonkey;

            tmonkeys.push_back(tmonkey);
            fmonkeys.push_back(fmonkey);

            step_in_monkey = 0;
        }
    }

    int lcm = 1;
    for (int i = 0; i < divs.size(); i++) {
        lcm *= divs[i];
    }

    for (int i = 0; i < (PART == 1 ? 20 : 10000); i++) {
        vector<vector<long long> > new_monkeys(monkeys.size());
        for (int j = 0; j < monkeys.size(); j++) {
            for (int k = 0; k < monkeys[j].size(); k++) {
                monkey_business[j] += 1;

                bool square = false;
                int num;
                if (operations[j].substr(1) == "old") square = true;
                else {
                    stringstream ss;
                    ss << operations[j].substr(1);
                    ss >> num;
                }
                if (square) {
                    monkeys[j][k] *= monkeys[j][k];
                } else if (operations[j][0] == '+') {
                    monkeys[j][k] += num;
                } else if (operations[j][0] == '*') {
                    monkeys[j][k] *= num;
                }

                if (PART == 1) monkeys[j][k] /= 3;

                monkeys[j][k] %= lcm;

                if (monkeys[j][k] % divs[j] == 0) {
                    if (tmonkeys[j] > j) {
                        monkeys[tmonkeys[j]].push_back(monkeys[j][k]);
                    } else {
                        new_monkeys[tmonkeys[j]].push_back(monkeys[j][k]);
                    }
                } else {
                    if (fmonkeys[j] > j) {
                        monkeys[fmonkeys[j]].push_back(monkeys[j][k]);
                    } else {
                        new_monkeys[fmonkeys[j]].push_back(monkeys[j][k]);
                    }
                }
            }
        }
        monkeys = new_monkeys;
    }

    sort(monkey_business.begin(), monkey_business.end());
    cout << monkey_business[monkey_business.size() - 1] * monkey_business[monkey_business.size() - 2] << '\n';
}
