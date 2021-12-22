#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

struct TeamDescription
{
	int id;
	int leadID;
	std::string name;
	int totalPlayers;
	std::vector <int> playerIDs;
};

