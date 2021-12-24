#pragma once
#include <iostream>
#include "MatchDescription.h"
#include "DBHandler.h"
#include "Team.h"

class Match
{
private:
	MatchDescription match;
	MatchStats stats;

public:
	Match();
	int getMatchId();
	bool addTeams(TeamDescription T1, TeamDescription T2);
	MatchDescription setSchedule(int tId, std::string date);
	MatchDescription getMatch(int id);
	bool removeMatch(int id);
	MatchStats getStats(int id);
};

