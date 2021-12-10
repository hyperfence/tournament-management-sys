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
	sql::Statement* stmt;
	sql::ResultSet* res;

public:
	DBHandler()
	{
		try
		{
			/* Create a connection */
			driver = get_driver_instance();
			con = driver->connect("sql157.main-hosting.eu", "u295091441_admin", "tlXp8Io6O");
			/* Connect to the MySQL test database */
			con->setSchema("u295091441_tournament_db");
			stmt = con->createStatement();
			res = stmt->executeQuery("SELECT * FROM player");
			while (res->next()) {
				cout << "\t... MySQL replies: ";
				/* Access column data by alias or column name */
				cout << res->getString("name") << endl;
				cout << "\t... MySQL says it again: ";
				/* Access column data by numeric offset, 1 is the first column */
				cout << res->getString(3) << endl;
			}
			delete res;
			delete stmt;
			delete con;
		}
		catch (sql::SQLException& e)
		{
			cout << "# ERR: SQLException in " << __FILE__;
			cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
			cout << "# ERR: " << e.what();
			cout << " (MySQL error code: " << e.getErrorCode();
			cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		}
	}
	void syncTeam(TeamDescription team);
	TeamDescription getTeam(int id);
	PlayerDescription getPlayer(int id);
};

