#pragma once
#include <stdlib.h>
#include <iostream>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include "ErrorHandler.h"
#include "Team.h"
#include "Player.h"
#include "Invitation.h"
#include "Game.h"
#include "Match.h"
#include "Tournament.h"

class DBHandler
{
private:
	/*static std::string db_host;
	static std::string db_user;
	static std::string db_pass;
	static std::string db_name;*/
	std::string db_host;
	std::string db_user;
	std::string db_pass;
	std::string db_name;
	static sql::Driver* driver;
	static sql::Connection* con;
	static sql::Statement* stmt;
	static sql::ResultSet* res; 
	static bool isLoading;

public:
	DBHandler();
	/*
		The following method is used to create
		connection to the MySQL DataBase
	*/
	void establishConnection();
	/*
		The following methods handle the Team's DB
		related functionality
	*/
	static TeamDescription getTeam(int teamId);
	static bool createTeamDB(int playerId, std::string name, int totalPlayers);
	/*
		The following methods handle the Players's DB
		related functionality
	*/
	static bool loginPlayer(std::string email, std::string pass, PlayerDescription* player);
	static bool signupPlayer(std::string name, std::string email, std::string pass);
	static PlayerDescription getPlayer(int playerId);
	static bool addPlayer(int playerId, int teamId);
	static bool removePlayer(int playerId, int teamId);
	/*
		The following methods handle the Invites's DB
		related functionality
	*/
	//InviteList* getInvites(int playerId);
	static bool getInvitesDB(int playerId, InviteList*& list, int* count);
	static bool sendInvite(int senderId, std::string receiverEmail, int teamId);
	static bool updateInvite(int inviteId, int action); // Action 0 = Rejected && Action 1 = Accepted
	/*
		The following methods handle Game's DB
		related functionality
	*/
	static bool getGameDB(int id, GameDescription* game);
	/*
		The following methods handle Match DB
		related functionality
	*/
	static bool getMatchDB(int id, MatchDescription* match);
	static bool addMatchDB(int team_1, int team_2, int tournament_id, std::string date, int* matchId);
	static bool updateMatchInfo(int id, int score, int winnerId, int loserId, std::string status);
	static bool mapMatchDB(int tournament_id, int match_id);
	static bool removeMatchDB(int id);
	/*
		The following methods handle Tournament DB
		related functionality
	*/
	static bool getTournamentDB(int id, TournamentDescription* tournament);
	static bool removeTournamentDB(int id);
	static bool addTournamentDB(std::string name, std::string prize, int game_id, int totalTeams, int organizerId, int* tournamentId);

	static bool getLastInsertID(int* id);
	~DBHandler();
};