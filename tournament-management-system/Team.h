#pragma once
#include <iostream>
#include "TeamDescription.h"
#include "DBHandler.h"

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
	void displayDetails();
	void createTeam(int playerId, string name, int totalPlayers);
	void addPlayer(int playerId);
	void removePlayer(int playerId);
	void displayPlayers();
};

