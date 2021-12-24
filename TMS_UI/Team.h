#pragma once
#include <iostream>
#include "TeamDescription.h"
#include "DBHandler.h"

class Team
{
private:
	TeamDescription team;

public:
	Team();
	Team(int id, std::string name, int leadId, int totalPlayers);
	TeamDescription getTeam(int id);
	int getTotalPlayers();
	void displayDetails();
	bool createTeam(int playerId, std::string name, int totalPlayers);
	void addPlayer(int playerId);
	void removePlayer(int playerId);
	void displayPlayers();
};

