#pragma once
#include <iostream>
#include "TournamentDescription.h"
#include "DBHandler.h"

class Match;

class Tournament {
private:
	TournamentDescription tournament;

public:
	Tournament();
	TournamentDescription getTournament(int id);
	TournamentDescription* getAllTournaments(int player_id, int* size);
	TeamDescription selectTeam(int id);
	bool addMatch(int team_1, int team_2, int tournament_id, std::string date);
	bool addTournament(std::string name, int game_id, std::string prize, int totalTeams, int organizer_id);
	bool removeTournament(int id);
};