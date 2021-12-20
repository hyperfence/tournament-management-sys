#pragma once
#include <iostream>
#include "DBHandler.h"
#include "GameDescription.h"
using namespace std;

class Game
{
private:
	GameDescription game;
public:
	Game();
	Game(int id, string name, string category);
	GameDescription getGame(int id);
	void displayDetails();
};

