#include <iostream>
#include <string>
#include <fstream>
#include <regex>

#define LIMIT 1000

using namespace std;

int fabric[LIMIT][LIMIT];

vector<int> recIDs, distsL, distsT, sidesL, sidesT;

string inpath = "PATH_TO_INPUT_FILE";

void read() {
	ifstream input(inpath);
	string line;
	while (getline(input, line)) {
		smatch matches;
		regex_search(line, matches, regex("#([0-9]+)...([0-9]+),([0-9]+)..([0-9]+)x([0-9]+)"));
		if (matches.size() == 6) {
			recIDs.push_back(stoi(matches[1]));
			distsL.push_back(stoi(matches[2]));
			distsT.push_back(stoi(matches[3]));
			sidesL.push_back(stoi(matches[4]));
			sidesT.push_back(stoi(matches[5]));
		}
	}
	for (int h = 0; h < recIDs.size(); h++) {
		for (int k = 0; k < sidesT[h]; k++) {
			for (int i = 0; i < sidesL[h]; i++) {
				fabric[distsT[h] + k][distsL[h] + i]++;
			}
		}
	}
	for (int h = 0; h < recIDs.size(); h++) {
		bool overlap = false;
		for (int k = 0; k < sidesT[h]; k++) {
			for (int i = 0; i < sidesL[h]; i++) {
				if (fabric[distsT[h] + k][distsL[h] + i] > 1) {
					overlap = true;
				}
			}
		}
		if (!overlap) {
			cout << "Only clear rectangle: " << recIDs[h] << endl;
		}
	}
}

int main() {
	read();
}