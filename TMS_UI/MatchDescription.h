#pragma once
#include <iostream>

struct MatchDescription
{
	int id;
	int team_1;
	int team_2;
	std::string status;
	std::string date;
};

struct MatchStats
{
	int id;
	int winner;
	int loser;
	int score;
};

