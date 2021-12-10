#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TeamDescription
{
	int id;
	int leadID;
	string name;
	int totalPlayers;
	vector <int> playerIDs;
};

