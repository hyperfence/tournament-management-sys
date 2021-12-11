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
	TeamDescription getTeam(int id, sql::Connection* con);
	int getTotalPlayers();
	void displayDetails();
	void createTeam(int playerID, string name, int totalPlayers);
	void addPlayer(int playerID, sql::Connection * con);
	void removePlayer(int playerID);
	void displayPlayers();
};

