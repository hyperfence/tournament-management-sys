#include "Game.h"

Game::Game()
{
	this->game.id = 0;
	this->game.name = "";
}
Game::Game(int id, std::string name)
{
	this->game.id = id;
	this->game.name = name;
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