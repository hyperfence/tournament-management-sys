#pragma once
#include <iostream>
#include "Team.h"
#include "Player.h"
#include "jdbc/mysql_connection.h"

using namespace std;

class DBHandler
{
private:

public:
	DBHandler();
	void syncTeam(TeamDescription team);
	TeamDescription getTeam(int id);
	PlayerDescription getPlayer(int id);
};

