#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

string inpath = "PATH_TO_INPUT_FILE";

vector<string> storage;

void read() {
	ifstream input(inpath);
	string line;
	while (getline(input, line)) {
		if (!line.empty()) {
			char l[26];
			int k = 0;
			for (char chr : line) {
				l[k] = chr;
				k++;
			}
			for (string str : storage) {
				char s[26];
				int i = 0, o = 0;
				for (char chr : str) {
					s[i] = chr;
					i++;
				}
				for (int h = 0; h < 26; h++) {
					if (l[h] != s[h]) {
						o++;
					}
				}
				if (o == 1) {
				}
				cout << str << endl << line << endl << endl << endl;
			}
			storage.push_back(line);
		}
	}
}

int main() {
	read();
}