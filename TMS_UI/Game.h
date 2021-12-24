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
	Game(int id, std::string name);
	GameDescription getGame(int id);
};

