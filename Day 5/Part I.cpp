#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>

using namespace std;

string input_path = "PATH_TO_INPUT_FILE";

void read() {
	bool boolybool = false;
	string storage;
	ifstream input(input_path);
	while (!boolybool) {
		getline(input, storage);
		boolybool = true;
	}
	bool something = false;
	int reactions = 0;
	while (!something) {
		for (int i = 0; i < storage.length(); i++) {
			if (isupper(storage[i]) && islower(storage[i + 1]) && tolower(storage[i]) == storage[i + 1]) {
				storage.erase(storage.begin() + i, storage.begin() + i + 2);
				i--;
				reactions++;
			}
			if (islower(storage[i]) && isupper(storage[i + 1]) && toupper(storage[i]) == storage[i + 1]) {
				storage.erase(storage.begin() + i, storage.begin() + i + 2);
				i--;
				reactions++;
			}
		}
		if (reactions > 0) {
			reactions = 0;
		}
		else {
			something = true;
			cout << "Elements: " << storage.length() << endl;
		}
	}
}

int main() {
	read();
}