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
MatchDescription Match::getMatch(int id)
{
	DBHandler::getMatchDB(id, &this->match);
	return this->match;
}
bool Match::removeMatch(int id)
{
	return DBHandler::removeMatchDB(id);
}
MatchStats Match::getStats(int id)
{
	return stats;
}