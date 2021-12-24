#include "Tournament.h"
#include "Team.h"
#include "Match.h"

Tournament::Tournament()
{
	
}
TournamentDescription Tournament::getTournament(int id)
{
	DBHandler::getTournamentDB(id, &this->tournament);
	// Get Matches here and store them and matches array
	return this->tournament;
}
bool Tournament::addMatch(int team_1, int team_2, int tournament_id, std::string date)
{
	Team team;
	Match match;
	match.addTeams(team.getTeam(team_1), team.getTeam(team_2));
	match.setSchedule(tournament_id, date);
	if (match.getMatchId() > 0)
	{
		return true;
	}
	return false;
}
bool Tournament::removeTournament(int id)
{
	return DBHandler::removeTournamentDB(id);
}
bool Tournament::addTournament(std::string name, int game_id, std::string prize, int totalTeams, int organizerId)
{
	int tId = 0;
	if (DBHandler::addTournamentDB(name, prize, game_id, totalTeams,organizerId, &tId) == true)
	{
		this->getTournament(tId);
		return true;
	}
	return false;
}