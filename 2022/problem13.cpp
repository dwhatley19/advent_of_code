#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

const string SIGNAL_ONE = "[[2]]", SIGNAL_TWO = "[[6]]";

string get_nth_element(string list, int n)
{
    int num_commas_passed = 0;
    int cur_index = 1;
    int bracket_balance = 0;
    string cur_element = "";
    bool reset = false;
    while (cur_index < list.size() && num_commas_passed < n) {
        if (reset) {
            cur_element = "";
            reset = false;
        }

        cur_element += list[cur_index];

        if (list[cur_index] == ',' && bracket_balance == 0) {
            num_commas_passed++;
            reset = true;
        }
        else if (list[cur_index] == '[') bracket_balance++;
        else if (list[cur_index] == ']') bracket_balance--;

        cur_index++;
    }
    if (num_commas_passed >= n - 1) return cur_element.substr(0, cur_element.size() - 1);
    return "";
}

int compare_left_and_right(string left, string right)
{
    if (left == "" && right != "") return -1;
    if (right == "" && left != "") return 1;

    if (left[0] != '[' && right[0] != '[') {
        int left_num = atoi(left.c_str()), right_num = atoi(right.c_str());
        return left_num == right_num ? 0 : left_num < right_num ? -1 : 1;
    }

    int n = 0;
    while (true) {
        n++;

        string left_nth = get_nth_element(left, n);
        string right_nth = get_nth_element(right, n);

        if (left_nth == "" && right_nth == "") return 0;

        if (left_nth[0] == '[' && right_nth.size() && right_nth[0] != '[') {
            right_nth = "[" + right_nth + "]";
        } else if (left_nth.size() && left_nth[0] != '[' && right_nth[0] == '[') {
            left_nth = "[" + left_nth + "]";
        }

        int left_nth_smaller = compare_left_and_right(left_nth, right_nth);
        if (left_nth_smaller != 0) {
            return left_nth_smaller;
        }
    }
}

bool is_left_smaller(string left, string right)
{
    return compare_left_and_right(left, right) == -1;
}

int main()
{
    ifstream fin("problem13.txt");

    vector<string> signals;

    string left, right;
    int i = 0, ans = 0;
    while (fin >> left >> right) {
        i++;
        if (is_left_smaller(left, right)) ans += i;

        signals.push_back(left);
        signals.push_back(right);
    }

    signals.push_back(SIGNAL_ONE);
    signals.push_back(SIGNAL_TWO);

    sort(signals.begin(), signals.end(), is_left_smaller);

    cout << ans << endl;

    int signal_one_idx = find(signals.begin(), signals.end(), SIGNAL_ONE) - signals.begin();
    int signal_two_idx = find(signals.begin(), signals.end(), SIGNAL_TWO) - signals.begin();

    cout << (signal_one_idx + 1) * (signal_two_idx + 1) << '\n';
}
