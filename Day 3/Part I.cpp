#include <iostream>
#include <string>
#include <fstream>
#include <regex>

#define LIMIT 1000

using namespace std;

int fabric[LIMIT][LIMIT];

string inpath = "PATH_TO_INPUT_FILE";

void read() {
	ifstream input(inpath);
	string line;
	while (getline(input, line)) {
		smatch matches;
		regex_search(line, matches, regex("#[0-9]+...([0-9]+),([0-9]+)..([0-9]+)x([0-9]+)"));
		if (matches.size() == 5) {
			int distL = stoi(matches[1]);
			int distT = stoi(matches[2]);
			int sideL = stoi(matches[3]);
			int sideT = stoi(matches[4]);
			for (int k = 0; k < sideT; k++) {
				for (int i = 0; i < sideL; i++) {
					fabric[distT + k][distL + i]++;
				}
			}
		}
	}
	int count = 0;
	for (int i = 0; i < LIMIT; i++) {
		for (int k = 0; k < LIMIT; k++) {
			if (fabric[i][k] > 1) {
				count++;
			}
		}
	}
	cout << "Overlaps: " << count << endl;
}

int main() {
	read();
}