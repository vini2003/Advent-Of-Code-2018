#include <iostream>
#include <string>
#include <fstream>
#include <set>

using namespace std;

string inpath = "PATH_TO_INPUT_FILE";

int result;

set<int> storage;

void read() {
	ifstream input(inpath);
	string line;
	while (getline(input, line)) {
		if (!line.empty()) {
			result += stoi(line);
			if (!storageB.insert(result).second) {
				cout << "Duplicate: " << result;
				system("PAUSE");
			}
		}
	}
	read();
}

int main() {
	read();
}