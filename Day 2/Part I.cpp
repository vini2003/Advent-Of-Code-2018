#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

string inpath = "PATH_TO_INPUT_FILE";

int count2 = 0, count3 = 0;

set<char> storage;

void read() {
	ifstream input(inpath);
	string line;
	while (getline(input, line)) {
		if (!line.empty()) {
			bool a = false, b = false;
			for (char l : line) {
				storage.insert(l);
			}
			for (char l : storage) {
				int n = count(line.begin(), line.end(), l);
				if (n == 2 && !a) {
					a = true;
					count2++;
				}
				if (n == 3 && !b) {
					b = true;
					count3++;
				}

			}
			storage.clear();
		}
	}
	cout << "Checksum: " << (count2 * count3) << endl;
	system("PAUSE");
}

int main() {
	read();
}