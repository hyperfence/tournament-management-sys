#include "Game.h"

Game::Game()
{
	this->game.id = 0;
	this->game.name = "";
	this->game.category = "";
}
Game::Game(int id, std::string name, std::string category)
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
		DBHandler::getGameDB(id, &this->game);
		return game;
	}
}