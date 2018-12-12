#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <regex>

using namespace std;

auto regexID = regex("#([0-9]+)");
auto regexFW = regex(":([0-9]+)");
smatch matches;

string input_path = "PATH_TO_INPUT_FILE";

class Guard {
public:
	void SetEmpty() {
		ID = NULL;
		sleep.clear();
		awake.clear();
	}
	void SetID(int tmpID) {
		ID = tmpID;
	}
	void SetTime(vector<int> tmpsleep, vector<int> tmpAwake) {
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
		amount = *max_element(begin(buffer), end(buffer));
		return MaxMinute - begin(buffer);
	}
	int MaxAmount() {
		MaxMinute();
		return amount;
	}

private:
	int ID;
	int amount;
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
	map<int, int> GuardSleep;
	for (int myID : IDList) {
		guard.SetID(myID);
		guard.SetTime(guardData[myID].first, guardData[myID].second);
		GuardSleep[myID] = guard.MaxMinute();
		if (guard.MaxSleep() > sleep) {
			sleep = guard.MaxSleep();
			minute = guard.MaxMinute();
			tmpID = myID;
		}
		guard.SetEmpty();
	}
	cout << "Part I: " << minute * tmpID << endl;
	minute = 0, sleep = 0, tmpID = 0;
	map<int, pair<int, int>> myMap;
	for (int myID : IDList) {
		guard.SetID(myID);
		guard.SetTime(guardData[myID].first, guardData[myID].second);
		myMap[myID] = { guard.MaxMinute(), guard.MaxAmount() };
		if (myMap[myID].second > minute) {
			minute = myMap[myID].second;
			sleep = myMap[myID].first;
			tmpID = myID;
		}
		guard.SetEmpty();
	}
	cout << "Part II: " << sleep * tmpID << endl;
}

int main() {
	read();
}