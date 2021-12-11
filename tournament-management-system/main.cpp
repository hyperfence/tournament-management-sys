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

	player.getPlayer(1, db.getCon());
	player.displayDetails();

	team.getTeam(1, db.getCon());

	team.addPlayer(1, db.getCon());
	team.addPlayer(2, db.getCon());
	team.addPlayer(3, db.getCon());
	team.addPlayer(4, db.getCon());

	team.displayDetails();
	return 0;
}