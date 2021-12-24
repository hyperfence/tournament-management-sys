#include "DBHandler.h"

//std::string DBHandler::db_host = NULL;
//std::string DBHandler::db_user = NULL;
//std::string DBHandler::db_pass = NULL;
//std::string DBHandler::db_name = NULL;
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
	/*
	DBHandler::db_host = "sql157.main-hosting.eu";
	DBHandler::db_user = "u295091441_admin";
	DBHandler::db_pass = "tlXp8Io6O";
	DBHandler::db_name = "u295091441_tournament_db";
	*/
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
	}
}
TeamDescription DBHandler::getTeam(int id)
{
	TeamDescription team;
	try
	{
		std::string sql = "SELECT * FROM team WHERE id = " + std::to_string(id);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		DBHandler::res->next();
		team.id = id;
		team.name = DBHandler::res->getString("name");
		team.leadId = DBHandler::res->getInt("lead_id");
		team.totalPlayers = DBHandler::res->getInt("total_players");
		sql = "SELECT * FROM team_player WHERE team_id = " + std::to_string(id);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		while (DBHandler::res->next()) {
			team.playerIds.emplace_back(DBHandler::res->getInt("player_id"));
		}
	}
	catch (sql::SQLException& e)
	{
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return team;
}
bool DBHandler::createTeamDB(int playerId, std::string name, int totalPlayers)
{
	bool result = true;
	try
	{
		std::string sql = "INSERT INTO team (name, lead_id, total_players) VALUES ('" + name + "', " + std::to_string(playerId) + ", " + std::to_string(totalPlayers) + ")";
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
	}
	return result;
}
PlayerDescription DBHandler::getPlayer(int id)
{
	PlayerDescription player;
	try
	{
		std::string sql = "SELECT * FROM player WHERE id = "+std::to_string(id);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		DBHandler::res->next();
		player.id = id;
		player.name = DBHandler::res->getString("name");
		player.email = DBHandler::res->getString("email");
		player.password = "";
	}
	catch (sql::SQLException& e)
	{
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return player;
}
bool DBHandler::addPlayer(int playerID, int teamID)
{
	bool result = true;
	try
	{
		std::string sql = "INSERT INTO team_player (team_id, player_id) VALUES (" + std::to_string(teamID) + "," + std::to_string(playerID) + ")";
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
	}
	return result;
}
bool DBHandler::removePlayer(int playerID, int teamID)
{
	bool result = true;
	try
	{
		std::string sql = "DELETE FROM team_player WHERE team_id = " + std::to_string(teamID) + " AND player_id = " + std::to_string(playerID);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::stmt->execute(sql);
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
bool DBHandler::getInvitesDB(int playerId, InviteList*& list, int* count)
{
	bool result = true;
	try 
	{
		std::string sql = "SELECT COUNT(*) AS total FROM invitation WHERE receiver_id = " + std::to_string(playerId);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		DBHandler::res->next();
		int inviteCount = DBHandler::res->getInt("total");
		*count = inviteCount;
		list = new InviteList[inviteCount];
		sql = "SELECT * FROM invitation WHERE receiver_id = " + std::to_string(playerId);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		int index = 0;
		while (DBHandler::res->next())
		{
			list[index].inviteID = DBHandler::res->getInt("id");
			list[index].teamId = DBHandler::res->getInt("team_id");;
			index++;
		}
		for (int i=0; i<inviteCount; i++)
		{
			sql = "SELECT * FROM team WHERE id = " + std::to_string(list[i].teamId);
			DBHandler::stmt = DBHandler::con->createStatement();
			DBHandler::res = DBHandler::stmt->executeQuery(sql);
			DBHandler::res->next();
			list[i].teamName = DBHandler::res->getString("name");
		}
	}
	catch (sql::SQLException& e) 
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
bool DBHandler::sendInvite(int senderId, std::string receiverEmail, int teamId)
{
	bool result = true;
	try
	{
		std::string sql = "SELECT * FROM player WHERE email = '" + receiverEmail + "'";
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		DBHandler::res->next();
		int receiverId = DBHandler::res->getInt("id");
		sql = "INSERT INTO invitation (team_id, sender_id, receiver_id) VALUES (" + std::to_string(teamId) + ", " + std::to_string(senderId) + ", " + std::to_string(receiverId) + ")";
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::stmt->execute(sql);
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
bool DBHandler::updateInvite(int inviteID, int action)
{
	bool result = true;
	int playerId = 0;
	int teamId = 0;
	if (action == 0)
	{
		try
		{
			std::string sql = "DELETE FROM invitation WHERE id = " + std::to_string(inviteID);
			DBHandler::stmt = DBHandler::con->createStatement();
			DBHandler::stmt->execute(sql);
		}
		catch (sql::SQLException& e)
		{
			result = false;
			ErrorHandler error;
			error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
			error.logError();
		}
	}
	else if (action == 1)
	{
		try
		{
			std::string sql = "SELECT * FROM invitation WHERE id = " + std::to_string(inviteID);
			DBHandler::stmt = DBHandler::con->createStatement();
			DBHandler::res = DBHandler::stmt->executeQuery(sql);
			DBHandler::res->next();
			playerId = res->getInt("receiver_id");
			teamId = res->getInt("team_id");
			sql = "INSERT INTO team_player (team_id, player_id) VALUES (" + std::to_string(teamId) + ", " + std::to_string(playerId) + ")";
			DBHandler::stmt = DBHandler::con->createStatement();
			DBHandler::stmt->execute(sql);
			sql = "DELETE FROM invitation WHERE id = " + std::to_string(inviteID);
			DBHandler::stmt = DBHandler::con->createStatement();
			DBHandler::stmt->execute(sql);
		}
		catch (sql::SQLException& e)
		{
			ErrorHandler error;
			error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
			error.logError();
			return false;
		}
	}
	else
	{
		result = false;
	}
	return result;
}
bool DBHandler::loginPlayer(std::string email, std::string pass, PlayerDescription* player)
{
	bool result = true;
	try
	{
		std::string sql = "SELECT * FROM player WHERE email = '" + email + "' AND password = '" + pass + "'";
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		if (DBHandler::res->next() == false)
		{
			result = false;
		}
		else
		{
			player->id = DBHandler::res->getInt("id");
			player->name = DBHandler::res->getString("name");
			player->email = email;
			player->password = pass;
			sql = "SELECT * FROM tournament WHERE organizer_id = " + std::to_string(player->id);
			DBHandler::stmt = DBHandler::con->createStatement();
			DBHandler::res = DBHandler::stmt->executeQuery(sql);
			if (DBHandler::res->next() == false)
			{
				player->status = "Player";
			}
			else
			{
				player->status = "Organizer";
			}
		}
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
bool DBHandler::signupPlayer(std::string name, std::string email, std::string pass)
{
	bool result = true;
	try
	{
		std::string sql = "INSERT INTO player (name, email, password) VALUES ('" + name + "', '" + email + "', '" + pass + "')";
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::stmt->execute(sql);
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
bool DBHandler::getGameDB(int id, GameDescription* game)
{
	bool result = true;
	try
	{
		std::string sql = "SELECT * FROM game WHERE id = " + std::to_string(id);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		if (DBHandler::res->next() == false)
		{
			result = false;
		}
		else
		{
			game->id = id;
			game->name = DBHandler::res->getString("name");
		}
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
bool DBHandler::getMatchDB(int id, MatchDescription* match)
{
	bool result = true;
	try
	{
		std::string sql = "SELECT * FROM matches WHERE id = " + std::to_string(id);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		if (DBHandler::res->next() == false)
		{
			result = false;
		}
		else
		{
			match->id = id;
			match->team_1 = DBHandler::res->getInt("team_1");
			match->team_2 = DBHandler::res->getInt("team_2");
			match->date = DBHandler::res->getString("date");
		}
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
bool DBHandler::addMatchDB(int team_1, int team_2, int tournament_id, std::string date, int* matchId)
{
	bool result = true;
	try
	{
		std::string sql = "INSERT INTO matches (team_1, team_2, date) VALUES (" + std::to_string(team_1) + ", " + std::to_string(team_2) + ", '" + date + "')";
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::stmt->execute(sql);
		sql = "SELECT id FROM matches ORDER BY id DESC LIMIT 1";
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		DBHandler::res->next();
		*matchId = DBHandler::res->getInt("id");
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
bool DBHandler::updateMatchInfo(int id, int score, int winnerId, int loserId, std::string status)
{
	bool result = true;
	try
	{
		std::string sql = "UPDATE match_stats SET score = " + std::to_string(score) + ", winner = " + std::to_string(winnerId) + ", loser = " + std::to_string(loserId) + " WHERE match_id = " + std::to_string(id);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::stmt->execute(sql);
		sql = "UPDATE matches SET status = '" + status + "' WHERE id = " + std::to_string(id);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::stmt->execute(sql);
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
bool DBHandler::mapMatchDB(int tournament_id, int match_id)
{
	bool result = true;
	try
	{
		std::string sql = "INSERT INTO tournament_match (tournament_id, match_id) VALUES (" + std::to_string(tournament_id) + ", " + std::to_string(match_id) + ")";
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::stmt->execute(sql);
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
bool DBHandler::removeMatchDB(int id)
{
	bool result = true;
	try
	{
		std::string sql = "DELETE FROM matches WHERE id = " + std::to_string(id);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::stmt->execute(sql);
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
bool DBHandler::getTournamentDB(int id, TournamentDescription* tournament)
{
	bool result = true;
	try
	{
		std::string sql = "SELECT * FROM tournament WHERE id = " + std::to_string(id);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		if (DBHandler::res->next() == false)
		{
			result = false;
		}
		else
		{
			tournament->id = id;
			tournament->name = DBHandler::res->getString("name");
			tournament->prize = DBHandler::res->getString("prize");
			tournament->totalTeams = DBHandler::res->getInt("total_teams");
		}
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
bool DBHandler::addTournamentDB(std::string name, std::string prize, int game_id, int totalTeams, int organizerId, int* tournamentId)
{
	bool result = true;
	try
	{
		std::string sql = "INSERT INTO tournament (name, prize, game_id, total_teams, organizer_id) VALUES ('" + name + "', '" + prize + "', " + std::to_string(game_id) + ", " + std::to_string(totalTeams) + ", " + std::to_string(organizerId) + ")";
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::stmt->execute(sql);
		sql = "SELECT id FROM tournament ORDER BY id DESC LIMIT 1";
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::res = DBHandler::stmt->executeQuery(sql);
		DBHandler::res->next();
		*tournamentId = DBHandler::res->getInt("id");
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
bool DBHandler::getLastInsertID(int* id) 
{
	bool result = true;
	try {
		std::string sql = "SELECT LAST_INSERT_ID() AS id";
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::stmt->execute(sql);
		DBHandler::res->next();
		*id = DBHandler::res->getInt("id");
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
bool DBHandler::removeTournamentDB(int id)
{
	bool result = true;
	try
	{
		std::string sql = "DELETE FROM tournament WHERE id = " + std::to_string(id);
		DBHandler::stmt = DBHandler::con->createStatement();
		DBHandler::stmt->execute(sql);
	}
	catch (sql::SQLException& e)
	{
		result = false;
		ErrorHandler error;
		error.setError(__LINE__, e.getErrorCode(), "MySQL", __FILE__, e.what(), e.getSQLState());
		error.logError();
	}
	return result;
}
DBHandler::~DBHandler()
{
	delete res;
	delete stmt;
	delete con;
}