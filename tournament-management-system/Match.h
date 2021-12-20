#pragma once
#include <iostream>
#include "MatchDescription.h"
#include "DBHandler.h"
using namespace std;

class Match
{
private:
	MatchDescription match;
public:
	Match();
	Match(int team_1, int team_2, int game_id, string status, string date);
	void addMatch(int team_1, int team_2, int game_id, string status, string date, sql::Connection* con);
	void getMatch(int id, sql::Connection* con);
	void removeMatch(int id, sql::Connection* con);
};

