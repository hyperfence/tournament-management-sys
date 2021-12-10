#pragma once
#include <iostream>
#include "PlayerDescription.h"

using namespace std;

class Player
{
private:
	PlayerDescription player;
public:
	Player();
	Player(int id, string name, string email, string password);
	PlayerDescription getPlayer(int id);
	PlayerDescription getCurrentPlayer();
	void displayDetails();
};
