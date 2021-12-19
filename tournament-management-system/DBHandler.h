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

using namespace std;

class DBHandler
{
private:
	string db_host;
	string db_user;
	string db_pass;
	string db_name;
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
	~DBHandler();
};

