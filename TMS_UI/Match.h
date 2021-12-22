#pragma once
#include <iostream>
#include "MatchDescription.h"
#include "DBHandler.h"

class Match
{
private:
	MatchDescription match;
	MatchStats stats;

public:
	Match();
	MatchDescription getMatch(int id);
	bool removeMatch(int id);
	MatchStats getStats(int id);
};

