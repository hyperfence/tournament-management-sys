#include "Team.h"
#include <algorithm>

Team::Team()
{
	this->team.id = 0;
	this->team.name = "";
	this->team.leadId = 0;
	this->team.totalPlayers = 0;
}
Team::Team(int id, std::string name, int leadId, int totalPlayers)
{
	this->team.id = id;
	this->team.name = name;
	this->team.leadId = leadId;
	this->team.totalPlayers = totalPlayers;
}
int Team::getTotalPlayers()
{
	return this->team.totalPlayers;
}

bool Team::createTeam(int playerId, std::string name, int totalPlayers)
{
	if (DBHandler::createTeamDB(playerId, name, totalPlayers) == true)
	{
		this->team.leadId = playerId;
		this->team.name = name;
		this->team.totalPlayers = totalPlayers;
		return true;
	}
	else
	{
		return false;
	}
}

void Team::addPlayer(int playerId)
{
	if (this->team.playerIds.size() < this->team.totalPlayers)
	{
		if (!(std::find(this->team.playerIds.begin(), this->team.playerIds.end(), playerId) != this->team.playerIds.end()))
		{	
			if (DBHandler::addPlayer(playerId, this->team.id))
			{
				this->team.playerIds.emplace_back(playerId);
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
	if ((std::find(this->team.playerIds.begin(), this->team.playerIds.end(), playerId) != this->team.playerIds.end()))
	{
		if (DBHandler::removePlayer(playerId, this->team.id))
		{
			this->team.playerIds.erase(std::remove(this->team.playerIds.begin(), this->team.playerIds.end(), playerId), this->team.playerIds.end());
		}
	}
}

void Team::displayPlayers()
{
	for (int i = 0; i < this->team.playerIds.size(); i++)
	{
		std::cout << this->team.playerIds[i] << std::endl;
	}
}
void Team::displayDetails()
{
	std::cout << "************** Team Details **************" << std::endl;
	std::cout << "Team ID: " << team.id << std::endl;
	std::cout << "Lead ID: " << team.leadId << std::endl;
	std::cout << "Team Name: " << team.name << std::endl;
	std::cout << "Team Players: " << std::endl;
	displayPlayers();
	std::cout << "******************************************" << std::endl;
}
