#pragma once
#include <iostream>
#include "PlayerDescription.h"
#include "DBHandler.h"

class Player
{
private:
	PlayerDescription player;

public:
	Player();
	Player(int id, std::string name, std::string email, std::string password);
	bool login(std::string email, std::string pass);
	bool signup(std::string name, std::string email, std::string pass);
	PlayerDescription getPlayer(int id);
	void displayDetails();
};

