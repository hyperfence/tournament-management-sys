#pragma once
#include <iostream>
#include "TeamDescription.h"

using namespace std;

class Team
{
private:
	TeamDescription team;
public:
	Team();
	Team(int id, string name, int totalPlayers);
	TeamDescription getTeam(int id);
	int getTotalPlayers();
	void createTeam(int playerID, string name, int totalPlayers);
	void addPlayer(int playerID);
	void removePlayer(int playerID);
	void displayPlayers();
};

