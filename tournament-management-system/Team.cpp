#include "Team.h"
#include <algorithm>

Team::Team()
{
	this->team.id = 0;
	this->team.name = "";
	this->team.totalPlayers = 0;
}
Team::Team(int id, string name, int totalPlayers)
{
	this->team.id = id;
	this->team.name = name;
	this->team.totalPlayers = totalPlayers;
}

int Team::getTotalPlayers()
{
	return this->team.totalPlayers;
}

void Team::createTeam(int playerID, string name, int totalPlayers)
{
	this->team.leadID = playerID;
	this->team.name = name;
	this->team.totalPlayers = totalPlayers;
}

void Team::addPlayer(int playerID, sql::Connection * con)
{
	if (this->team.playerIDs.size() < this->team.totalPlayers)
	{
		if (!(std::find(this->team.playerIDs.begin(), this->team.playerIDs.end(), playerID) != this->team.playerIDs.end()))
		{	
			if (DBHandler::addPlayer(playerID, this->team.id, con))
			{
				cout << "Inside the function!" << endl;
				this->team.playerIDs.emplace_back(playerID);
			}	
		}
	}
	else
	{
		cout << "Team players limit exceeding!" << endl;
	}

}
TeamDescription Team::getTeam(int id, sql::Connection* con = NULL)
{
	if (this->team.id == id)
	{
		return this->team;
	}
	else
	{
		this->team = DBHandler::getTeam(id, con);
		return team;
	}
}
void Team::removePlayer(int playerID)
{
	if ((std::find(this->team.playerIDs.begin(), this->team.playerIDs.end(), playerID) != this->team.playerIDs.end()))
	{
		this->team.playerIDs.erase(std::remove(this->team.playerIDs.begin(), this->team.playerIDs.end(), playerID), this->team.playerIDs.end());
	}
}

void Team::displayPlayers()
{
	for (int i = 0; i < this->team.playerIDs.size(); i++)
	{
		cout << this->team.playerIDs[i] << endl;
	}
}
void Team::displayDetails()
{
	cout << "************** Team Details **************" << endl;
	cout << "Team ID: " << team.id << endl;
	cout << "Lead ID: " << team.leadID << endl;
	cout << "Team Name: " << team.name << endl;
	cout << "Team Players: " << endl;
	displayPlayers();
	cout << "******************************************" << endl;
}
