#include "Match.h"

Match::Match()
{
	this->match.id = 0;
	this->match.team_1 = 0;
	this->match.team_2 = 0;
	this->match.game_id = 0;
	this->match.status = "";
	this->match.date = "";
}
Match::Match(int team_1, int team_2, int game_id, string status, string date)
{
	this->match.id = 0;
	this->match.team_1 = team_1;
	this->match.team_2 = team_2;
	this->match.game_id = game_id;
	this->match.status = status;
	this->match.date = date;
}
void Match::addMatch(int team_1, int team_2, int game_id, string status, string date, sql::Connection* con)
{
	this->match.team_1 = team_1;
	this->match.team_2 = team_2;
	this->match.game_id = game_id;
	this->match.status = status;
	this->match.date = date;

	// Call DBHandler Ftn
}
// void getMatch(int id, sql::Connection* con);
// void removeMatch(int id, sql::Connection* con);
// Creating a Tournament Entry
// Updating Match Information
// Announcing an Update on Match
// Removing a team from tournament.
