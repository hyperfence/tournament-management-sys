#include "DBHandler.h"

sql::Statement* DBHandler::stmt = NULL;
sql::ResultSet* DBHandler::res = NULL;

sql::Connection* DBHandler::getCon()
{
	return this->con;
}
void DBHandler::syncTeam(TeamDescription team)
{

}
TeamDescription DBHandler::getTeam(int id, sql::Connection* con)
{
	TeamDescription team;
	try
	{
		string sql = "SELECT * FROM team WHERE id = " + to_string(id);
		DBHandler::stmt = con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		DBHandler::res->next();
		team.id = id;
		team.name = DBHandler::res->getString("name");
		team.leadID = DBHandler::res->getInt("leadID");

		sql = "SELECT * FROM team_player WHERE team_id = " + to_string(id);
		DBHandler::stmt = con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		while (DBHandler::res->next()) {
			team.playerIDs.emplace_back(DBHandler::res->getInt("player_id"));
		}
	}
	catch (sql::SQLException& e)
	{
		cout << "ERROR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "ERROR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}

	return team;
}
PlayerDescription DBHandler::getPlayer(int id, sql::Connection* con)
{
	PlayerDescription player;
	try
	{
		string sql = "SELECT * FROM player WHERE id = "+to_string(id);
		stmt = con->createStatement();
		res = stmt->executeQuery(sql);
		res->next();
		player.id = id;
		player.name = res->getString("name");
		player.email = res->getString("email");
		player.password = res->getString("password");
	}
	catch (sql::SQLException& e)
	{
		cout << "ERROR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "ERROR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	return player;
}
bool DBHandler::addPlayer(int playerID, int teamID, sql::Connection* con)
{
	bool result = true;
	try
	{
		string sql = "INSERT INTO team_player (team_id, player_id) VALUES (" + to_string(teamID) + "," + to_string(playerID) + ")";
		stmt = con->createStatement();
		stmt->execute(sql);
	}
	catch (sql::SQLException& e)
	{
		result = false;
		cout << "ERROR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "ERROR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	return result;
}
bool DBHandler::removePlayer(int playerID, int teamID, sql::Connection* con)
{
	bool result = true;
	try
	{
		string sql = "DELETE FROM team_player WHERE team_id = " + to_string(teamID) + " AND player_id = " + to_string(playerID);
		stmt = con->createStatement();
		stmt->execute(sql);
	}
	catch (sql::SQLException& e)
	{
		result = false;
		cout << "ERROR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "ERROR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
	return result;
}
void DBHandler::establishConnection()
{
	try
	{
		this->driver = get_driver_instance();
		this->con = this->driver->connect("sql157.main-hosting.eu", "u295091441_admin", "tlXp8Io6O");
		this->con->setSchema("u295091441_tournament_db");
		// To Loop Multiple Entries:
		// while(res->next())
	}
	catch (sql::SQLException& e)
	{
		cout << "ERROR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "ERROR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}
void DBHandler::closeConnection()
{
	delete res;
	delete stmt;
	delete con;
}