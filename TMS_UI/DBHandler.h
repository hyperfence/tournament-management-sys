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
#include "Tournament.h"
#include "Match.h"

class DBHandler
{
private:
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
	static bool sendInvite(int senderId, int receiverId, int teamId);
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
	static bool addMatchDB(int team_1, int team_2, int game_id, int tournament_id, std::string date, int* matchId);
	static bool mapMatchDB(int tournament_id, int match_id);
	static bool removeMatchDB(int id);
	/*
		The following methods handle Tournament DB
		related functionality
	*/
	static bool getTournamentDB(int id, TournamentDescription* tournament);
	static bool removeTournamentDB(int id);
	static bool addTournamentDB(std::string name, std::string prize, int totalTeams, int* tournamentId);
	~DBHandler();
};