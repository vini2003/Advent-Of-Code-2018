#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	int iFrequencyTotal = 0;
	ifstream input("C:\\Users\\vini2003\\Documents\\Advent of Code\\Day 1\\input");
	string line;
	while (input.is_open() && !input.eof()) {
		getline(input, line);
		if (!line.empty()) {
			iFrequencyTotal += stoi(line);
			cout << iFrequencyTotal << endl;
		}
	}
	cout << "END RESULT:\t" << iFrequencyTotal << endl;
	for (;;);
}