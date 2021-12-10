#include <iostream>
#include "Player.h"
#include "Team.h"
#include "DBHandler.h"

using namespace std;

int main()
{

	DBHandler db;
	db.establishConnection();

	Player player(3, "Hammad", "hammad@nu.edu.pk", "123");
	Team team(3, "Hammad's Team", 3);
	team.addPlayer(1);
	team.addPlayer(2);
	team.addPlayer(3);
	team.addPlayer(4);

	team.displayPlayers();
	
	team.removePlayer(3);
	team.displayPlayers();
	player.displayDetails();
	player.getPlayer(1, db.getCon());
	player.displayDetails();
	return 0;
}