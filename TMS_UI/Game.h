#pragma once
#include <iostream>
#include "GameDescription.h"
#include "DBHandler.h"

class Game
{
private:
	GameDescription game;

public:
	Game();
	Game(int id, std::string name, std::string category);
	GameDescription getGame(int id);
};

