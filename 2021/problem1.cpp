#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	ifstream fin("problem1.txt");

	int answer1 = 0;
	int answer2 = 0;

	int prev1 = 0, prev2 = 0, prev3 = 0;
	for (int i = 0; i < 2000; i++) {
		int x;
		fin >> x;
		if (i > 0 && x > prev1) {
			answer1++;
		}
		if (i > 2 && x+prev2+prev1 > prev1+prev2+prev3) {
			answer2++;
		}
		prev3 = prev2;
		prev2 = prev1;
		prev1 = x;
	}

	cout << answer1 << '\n';
	cout << answer2 << "\n";
}
