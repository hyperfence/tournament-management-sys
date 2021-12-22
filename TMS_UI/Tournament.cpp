#include "Tournament.h"

Tournament::Tournament()
{
	this->match = NULL;
}
TournamentDescription Tournament::getTournament(int id)
{
	DBHandler::getTournamentDB(id, &this->tournament);
	// Get Matches here and store them and matches array
	return this->tournament;
}
bool Tournament::addMatch(int team_1, int team_2, int game_id, int tournament_id, std::string date)
{
	int matchId = 0;
	if (DBHandler::addMatchDB(team_1, team_2, game_id, tournament_id, date, &matchId) == true)
	{
		DBHandler::mapMatchDB(tournament_id, matchId);
		return true;
	}
	return false;
}
bool Tournament::removeTournament(int id)
{
	return DBHandler::removeTournamentDB(id);
}
bool Tournament::addTournament(std::string name, std::string prize, int totalTeams)
{
	int matchId = 0;
	if (DBHandler::addTournamentDB(name, prize, totalTeams, &matchId) == true)
	{
		this->getTournament(matchId);
		return true;
	}
	return false;
}