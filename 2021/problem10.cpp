#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
	ifstream fin("problem10.txt");
	string s;
	stack<char> stk;
	long long score = 0;

	map<char, long long> scores;
	map<char, long long> scores2;

	scores[')'] = 3;
	scores[']'] = 57;
	scores['}'] = 1197;
	scores['>'] = 25137;

	scores2['('] = 1;
	scores2['['] = 2;
	scores2['{'] = 3;
	scores2['<'] = 4;

	vector<long long> final_scores;

	while (fin >> s) {
		long long final_score = 0;
		bool corrupt = false;
		for (int i = 0; i < s.size(); i++) {
			char c = s[i];
			// If the character is an opening chunk, push it to the stack.
			if (c == '(' || c == '[' || c == '{' || c == '<') {
				stk.push(c);
			}
			// If the character is a closing chunk, check if it matches the
			// last opening chunk in the stack. If it doesn't match, then
			// the line is corrupted and we can stop processing it.
			else if (c == ')' || c == ']' || c == '}' || c == '>') {
				char open = stk.top();
				if ((c == ')' && open != '(') || (c == ']' && open != '[') || (c == '}' && open != '{') || (c == '>' && open != '<')) {
					// Add the score for the illegal character to the total score.
					score += scores[c];
					corrupt = true;
					break;
				}
				stk.pop();
			}
		}
		// After processing the line, clear the stack for the next line.
		while (!stk.empty()) {
			final_score *= 5;
			final_score += scores2[stk.top()];
			stk.pop();
		}
		// cout << final_score << ' ';
		if (!corrupt && final_score > 0) {
			final_scores.push_back(final_score);
		}
	}

	cout << score << endl;

	sort(final_scores.begin(), final_scores.end());
	cout << final_scores[final_scores.size() / 2] << '\n';

	return 0;
}