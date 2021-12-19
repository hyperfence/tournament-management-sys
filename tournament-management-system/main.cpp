#include <iostream>
#include "Player.h"
#include "Team.h"
#include "DBHandler.h"

using namespace std;

int main()
{
	DBHandler db;
	db.establishConnection();

	Player player;
	Team team;

	player.getPlayer(3);
	player.displayDetails();

	team.getTeam(1);
	team.addPlayer(1);
	team.addPlayer(2);
	team.removePlayer(2);
	team.displayDetails();

	return 0;
}