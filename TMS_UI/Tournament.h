#pragma once
#include <iostream>
#include "TournamentDescription.h"
#include "DBHandler.h"
#include "Match.h"

class Match;

class Tournament {
private:
	Match* match;
	TournamentDescription tournament;

public:
	Tournament();
	TournamentDescription getTournament(int id);
	bool addMatch(int team_1, int team_2, int game_id, int tournament_id, std::string date);
	bool addTournament(std::string name, std::string prize, int totalTeams);
	bool removeTournament(int id);
};