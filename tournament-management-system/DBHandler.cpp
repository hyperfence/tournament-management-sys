#include "DBHandler.h"

sql::Driver* DBHandler::driver = NULL;
sql::Connection* DBHandler::con = NULL;
sql::Statement* DBHandler::stmt = NULL;
sql::ResultSet* DBHandler::res = NULL;

DBHandler::DBHandler()
{
	this->db_host = "sql157.main-hosting.eu";
	this->db_user = "u295091441_admin";
	this->db_pass = "tlXp8Io6O";
	this->db_name = "u295091441_tournament_db";
}
void DBHandler::establishConnection()
{
	try
	{
		DBHandler::driver = get_driver_instance();
		DBHandler::con = DBHandler::driver->connect(this->db_host, this->db_user, this->db_pass);
		DBHandler::con->setSchema(this->db_name);
	}
	catch (sql::SQLException& e)
	{
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
		error.displayError();
	}
}
TeamDescription DBHandler::getTeam(int id)
{
	TeamDescription team;
	try
	{
		string sql = "SELECT * FROM team WHERE id = " + to_string(id);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		DBHandler::res->next();
		team.id = id;
		team.name = DBHandler::res->getString("name");
		team.leadID = DBHandler::res->getInt("leadID");

		sql = "SELECT * FROM team_player WHERE team_id = " + to_string(id);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		while (DBHandler::res->next()) {
			team.playerIDs.emplace_back(DBHandler::res->getInt("player_id"));
		}
	}
	catch (sql::SQLException& e)
	{
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
		error.displayError();
	}
	return team;
}
PlayerDescription DBHandler::getPlayer(int id)
{
	PlayerDescription player;
	try
	{
		string sql = "SELECT * FROM player WHERE id = "+to_string(id);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		DBHandler::res->next();
		player.id = id;
		player.name = DBHandler::res->getString("name");
		player.email = DBHandler::res->getString("email");
		player.password = DBHandler::res->getString("password");
	}
	catch (sql::SQLException& e)
	{
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
		error.displayError();
	}
	return player;
}
bool DBHandler::addPlayer(int playerID, int teamID)
{
	bool result = true;
	try
	{
		string sql = "INSERT INTO team_player (team_id, player_id) VALUES (" + to_string(teamID) + "," + to_string(playerID) + ")";
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::stmt->execute(sql);
	}
	catch (sql::SQLException& e)
	{
		// Error Handling Here
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
		error.displayError();
	}
	return result;
}
bool DBHandler::removePlayer(int playerID, int teamID)
{
	bool result = true;
	try
	{
		string sql = "DELETE FROM team_player WHERE team_id = " + to_string(teamID) + " AND player_id = " + to_string(playerID);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::stmt->execute(sql);
	}
	catch (sql::SQLException& e)
	{
		// Error Handling Here
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
		error.displayError();
	}
	return result;
}
bool DBHandler::sendInvite(int senderID, int receiverID, int teamID)
{
	bool result = true;
	try
	{
		string sql = "INSERT INTO invite (team_id, sender_id, receiver_id) VALUES (" + to_string(teamID) + ", " + to_string(senderID) + ", " + to_string(receiverID) + ")";
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::stmt->execute(sql);
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
		error.displayError();
	}
	return result;
}
bool DBHandler::updateInvite(int inviteID, int action)
{
	bool result = true;
	string sql = "";
	if (action == 0)
	{
		sql = "DELETE FROM invites WHERE id = "+to_string(inviteID);
	}
	else if (action == 1)
	{
		sql = "SELECT * FROM invites WHERE id = " + to_string(inviteID);

		sql = "INSERT INTO team_player (team_id, player_id) VALUES ()";
	}
	else
	{
		return false;
	}
	return result;
}
DBHandler::~DBHandler()
{
	delete res;
	delete stmt;
	delete con;
}