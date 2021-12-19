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

void Team::createTeam(int playerId, string name, int totalPlayers)
{
	this->team.leadID = playerId;
	this->team.name = name;
	this->team.totalPlayers = totalPlayers;
}

void Team::addPlayer(int playerId)
{
	if (this->team.playerIDs.size() < this->team.totalPlayers)
	{
		if (!(std::find(this->team.playerIDs.begin(), this->team.playerIDs.end(), playerId) != this->team.playerIDs.end()))
		{	
			if (DBHandler::addPlayer(playerId, this->team.id))
			{
				this->team.playerIDs.emplace_back(playerId);
			}	
		}
	}
	else
	{
		cout << "Team players limit exceeding!" << endl;
	}

}
TeamDescription Team::getTeam(int id)
{
	if (this->team.id == id)
	{
		return this->team;
	}
	else
	{
		this->team = DBHandler::getTeam(id);
		return team;
	}
}
void Team::removePlayer(int playerId)
{
	if ((std::find(this->team.playerIDs.begin(), this->team.playerIDs.end(), playerId) != this->team.playerIDs.end()))
	{
		if (DBHandler::removePlayer(playerId, this->team.id))
		{
			this->team.playerIDs.erase(std::remove(this->team.playerIDs.begin(), this->team.playerIDs.end(), playerId), this->team.playerIDs.end());
		}
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
