#include "Game.h"

Game::Game()
{
	this->game.id = 0;
	this->game.name = "";
	this->game.category = "";
}
Game::Game(int id, string name, string category)
{
	this->game.id = id;
	this->game.name = name;
	this->game.category = category;
}
GameDescription Game::getGame(int id)
{
	if (this->game.id == id)
	{
		return this->game;
	}
	else
	{
		this->game = DBHandler::getGameDB(id);
		return game;
	}
}
void Game::displayDetails()
{
	cout << "************ Game Details ************" << endl;
	cout << "ID: " << this->game.id << endl;
	cout << "Name: " << this->game.name << endl;
	cout << "Category: " << this->game.category << endl;
	cout << "****************************************" << endl;
	;
}