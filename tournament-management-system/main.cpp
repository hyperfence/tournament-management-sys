#include <iostream>
#include "Player.h"
#include "Team.h"
#include "DBHandler.h"

using namespace std;

int main()
{
	Player player(1, "Hammad", "hammad@nu.edu.pk", "123");
	Team team(1, "Hammad's Team", 3);
	team.addPlayer(1);
	team.addPlayer(2);
	team.addPlayer(3);
	team.addPlayer(4);

	team.displayPlayers();
	
	team.removePlayer(3);
	team.displayPlayers();
	player.displayDetails();

	DBHandler test;

	return 0;
}