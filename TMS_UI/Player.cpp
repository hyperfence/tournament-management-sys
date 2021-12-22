#include "Player.h"

Player::Player() 
{
	this->player.id = 0;
}
Player::Player(int id, std::string name, std::string email, std::string pass)
{
	this->player.id = id;
	this->player.name = name;
	this->player.email = email;
	this->player.password = pass;
}
bool Player::login(std::string email, std::string pass)
{
	return DBHandler::loginPlayer(email, pass, &this->player);
}
bool Player::signup(std::string name, std::string email, std::string pass)
{
	return DBHandler::signupPlayer(name, email, pass);
}
PlayerDescription Player::getPlayer(int id)
{
	if (this->player.id == id)
	{
		return this->player;
	}
	else
	{
		 return DBHandler::getPlayer(id);
	}
}
void Player::displayDetails()
{
	std::cout << "************ Player Details ************" << std::endl;
	std::cout << "ID: " << this->player.id << std::endl;
	std::cout << "Name: " << this->player.name << std::endl;
	std::cout << "Email: " << this->player.email << std::endl;
	std::cout << "Password: " << this->player.password << std::endl;
	std::cout << "****************************************" << std::endl;
}