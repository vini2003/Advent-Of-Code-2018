#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <map>
#include <set>

using namespace std;

string inpath = "PATH_TO_INPUT_FILE";

map<int, tuple<vector<int>, vector<int>, int>> list;

vector<string> storage;

set<int> IDs;

int ID = 0, minute = 0, tmpOcc = 0;

void read() {
	ifstream input(inpath);
	string line;
	while (getline(input, line)) {
		storage.push_back(line);
	}
	sort(storage.begin(), storage.end());
	for (string str : storage) {
		if (regex_match(str, regex(".+#.+"))) {
			smatch matches;
			regex_search(str, matches, regex(".+#([0-9]+).+"));
			IDs.insert(stoi(matches[1]));
			ID = stoi(matches[1]);
		}
		if (regex_match(str, regex(".+00:[0-9]+.+fall.+"))) {
			smatch matches;
			regex_search(str, matches, regex("00:([0-9]+)"));
			get<0>(list[ID]).push_back(stoi(matches[1]));
		}
		if (regex_match(str, regex(".+00:[0-9]+.+wake.+"))) {
			smatch matches;
			regex_search(str, matches, regex("00:([0-9]+)"));
			get<1>(list[ID]).push_back(stoi(matches[1]));
		}
	}
	tuple<int, int> slept = { 0, 0 };
	for (int tmpID : IDs) {
		for (int awake : get<1>(list[tmpID])) {
			get<2>(list[tmpID]) += awake;
		}
		for (int sleep : get<0>(list[tmpID])) {
			get<2>(list[tmpID]) -= sleep;
		}
		if (get<2>(list[tmpID]) > get<1>(slept)) {
			slept = { tmpID, get<2>(list[tmpID]) };
		}
	}
	map<int, int> occur;
	for (int i = 0; i < get<0>(list[get<0>(slept)]).size(); i++) {
		for (int k = get<0>(list[get<0>(slept)])[i]; k < get<1>(list[get<0>(slept)])[i]; k++) {
			occur[k]++;
		}
	}
	for (int i = 0; i < 60; i++) {
		cout << i << "\t" << occur[i] << endl;
		if (occur[i] > tmpOcc) {
			tmpOcc = occur[i];
			minute = i;
		}
	}
	cout << "Slept the most: " << get<0>(slept) << " at " << get<1>(slept) << ", with the most slept-during minute being: " << minute << ", thus the code is: " << get<0>(slept) * minute;
}

int main() {
	read();
}