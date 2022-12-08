#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	ifstream fin("problem2.txt");

	int answer = 0;

	string a;
	long long b;

	long long x=0, y1=0, y=0, aim=0;

	while (fin >> a >> b) {
		if (a == "forward"){
			x += b;
			y += aim * b;
		}
		if (a == "down") {
			y1 += b;
			aim += b;
		}
		if (a == "up") {
			y1 -= b;
			aim -= b;
		}
	}

	cout << x*y1 << '\n';
	cout << x*y << "\n";
}
