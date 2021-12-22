#include "Team.h"
#include <algorithm>

Team::Team()
{
	this->team.id = 0;
	this->team.name = "";
	this->team.totalPlayers = 0;
}
Team::Team(int id, std::string name, int totalPlayers)
{
	this->team.id = id;
	this->team.name = name;
	this->team.totalPlayers = totalPlayers;
}
int Team::getTotalPlayers()
{
	return this->team.totalPlayers;
}

void Team::createTeam(int playerId, std::string name, int totalPlayers)
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
		std::cout << "Team players limit exceeding!" << std::endl;
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
		std::cout << this->team.playerIDs[i] << std::endl;
	}
}
void Team::displayDetails()
{
	std::cout << "************** Team Details **************" << std::endl;
	std::cout << "Team ID: " << team.id << std::endl;
	std::cout << "Lead ID: " << team.leadID << std::endl;
	std::cout << "Team Name: " << team.name << std::endl;
	std::cout << "Team Players: " << std::endl;
	displayPlayers();
	std::cout << "******************************************" << std::endl;
}
