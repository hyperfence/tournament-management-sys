#pragma once
#include <stdlib.h>
#include <iostream>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include "Team.h"
#include "Player.h"


using namespace std;

class DBHandler
{
private:
	sql::Driver* driver;
	sql::Connection* con;
	static sql::Statement* stmt;
	static sql::ResultSet* res; 

public:
	DBHandler()
	{
		driver = NULL;
		con = NULL;
	}
	void establishConnection();
	sql::Connection* getCon();
	void syncTeam(TeamDescription team);
	static TeamDescription getTeam(int id, sql::Connection* con);
	static PlayerDescription getPlayer(int id, sql::Connection* con);
	static bool addPlayer(int playerID, int teamID, sql::Connection * con);
	void closeConnection();
	~DBHandler()
	{
		delete res;
		delete stmt;
		delete con;
	}
};

