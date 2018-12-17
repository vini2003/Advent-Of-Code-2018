#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

void read() {
	ifstream input("PATH_TO_INPUT_FILE");
	string phrase;
	getline(input, phrase);
	string alphabet = "abcdefghijklmnopqrstuvwxyz";
	int sizes[26] = { 0 };
	int s = 0;
	for (char c : alphabet) {
		string tmpPhrase = phrase;
		tmpPhrase.erase(remove(tmpPhrase.begin(), tmpPhrase.end(), tolower(c)), tmpPhrase.end());
		tmpPhrase.erase(remove(tmpPhrase.begin(), tmpPhrase.end(), toupper(c)), tmpPhrase.end());
		for (int p = 0; p < tmpPhrase.size();) {
			if (p >= 0 && tolower(tmpPhrase[p]) == tolower(tmpPhrase[p + 1]) && ((islower(tmpPhrase[p]) && isupper(tmpPhrase[p + 1])) | (isupper(tmpPhrase[p]) && islower(tmpPhrase[p + 1])))) {
				tmpPhrase.erase(p, 2);
				p = 0;
			}
			else {
				p++;
			}
		}
		sizes[s] = tmpPhrase.size();
		s++;
	}
	cout << "Result: " << *min_element(begin(sizes), end(sizes)) << endl;
}

int main() {
	read();
}