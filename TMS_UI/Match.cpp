#include "Match.h"

Match::Match()
{
	this->match.id = 0;
	this->match.team_1 = 0;
	this->match.team_2 = 0;
	this->match.status = "";
	this->match.date = "";
}
MatchDescription Match::getMatch(int id)
{
	DBHandler::getMatchDB(id, &this->match);
	return this->match;
}
int Match::getMatchId()
{
	return this->match.id;
}
MatchDescription Match::setSchedule(int tId, std::string date)
{
	int matchId = 0;
	if (DBHandler::addMatchDB(this->match.team_1, this->match.team_2, tId, date, &matchId) == true)
	{
		if (DBHandler::mapMatchDB(tId, matchId) == true)
		{
			this->match.date = date;
			this->match.id = matchId;
			return this->match;
		}
	}
	this->match.team_1 = 0;
	this->match.team_2 = 0;
	return this->match;
}
bool Match::addTeams(TeamDescription T1, TeamDescription T2)
{
	this->match.team_1 = T1.id;
	this->match.team_2 = T2.id;
	return true;
}
bool Match::removeMatch(int id)
{
	return DBHandler::removeMatchDB(id);
}
MatchStats Match::getStats(int id)
{
	return stats;
}