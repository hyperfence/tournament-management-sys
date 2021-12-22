#pragma once
#include <iostream>

struct MatchDescription
{
	int id;
	int team_1;
	int team_2;
	int game_id;
	std::string status;
	std::string date;
};

struct MatchStats
{
	int matchID;
	int winner;
	int loser;
	int score;
};

