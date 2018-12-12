#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <regex>
#include <chrono>

using namespace std;

auto regexID = regex("#([0-9]+)");
auto regexFW = regex(":([0-9]+)");
smatch matches;

string input_path = "PATH_TO_INPUT_FILE";

class Guard {
public:
	void setEmpty() {
		ID = NULL;
		sleep.clear();
		awake.clear();
	}
	void setID(int tmpID) {
		ID = tmpID;
	}
	void setTime(vector<int> tmpsleep, vector<int> tmpAwake) {
		sleep = tmpsleep;
		awake = tmpAwake;
	}
	int MaxSleep() {
		int tmpsleep = 0;
		for (int i = 0; i < sleep.size(); i++) {
			tmpsleep += (awake[i] - sleep[i]);
		}
		return tmpsleep;
	}
	int MaxMinute() {
		int buffer[60] = { 0 };
		for (int i = 0; i < sleep.size(); i++) {
			for (int k = sleep[i]; k <= awake[i]; k++) {
				buffer[k]++;
			}
		}
		auto MaxMinute = max_element(begin(buffer), end(buffer));;
		return MaxMinute - begin(buffer);
	}

private:
	int ID;
	vector<int> sleep;
	vector<int> awake;
};

void read() {
	Guard guard;
	set<int>IDList;
	map<int, pair<vector<int>, vector<int>>> guardData;
	vector<string> storage;
	string line;
	ifstream input(input_path);
	while (getline(input, line)) {
		storage.push_back(line);
	}
	sort(storage.begin(), storage.end());
	int ID = 0;
	for (string str : storage) {
		if (str.find("#") != string::npos) {
			regex_search(str, matches, regexID);
			IDList.insert(stoi(matches[1]));
			ID = stoi(matches[1]);
		}
		else {
			regex_search(str, matches, regexFW);
			if (str.find("l") != string::npos) {
				guardData[ID].first.push_back(stoi(matches[1]));
			}
			if (str.find("w") != string::npos) {
				guardData[ID].second.push_back(stoi(matches[1]));
			}
		}
	}
	int minute = 0, sleep = 0, tmpID = 0;
	for (int myID : IDList) {
		guard.setID(myID);
		guard.setTime(guardData[myID].first, guardData[myID].second);
		if (guard.MaxSleep() > sleep) {
			sleep = guard.MaxSleep();
			minute = guard.MaxMinute();
			tmpID = myID;
		}
		guard.setEmpty();
	}
	cout << minute * tmpID << endl;
}

int main() {
	read();
}