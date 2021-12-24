#include "Player.h"

Player::Player() 
{
	this->player.id = 0;
	this->player.status = "Player";
}
Player::Player(int id, std::string name, std::string email, std::string pass)
{
	this->player.id = id;
	this->player.name = name;
	this->player.email = email;
	this->player.password = pass;
	this->player.status = "Player";
}
int Player::getId()
{
	return this->player.id;
}
std::string Player::getName()
{
	return this->player.name;
}
std::string Player::getEmail()
{
	return this->player.email;
}
std::string Player::getStatus()
{
	return this->player.status;
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
void Player::logout()
{
	this->player.id = 0;
	this->player.email = "";
	this->player.name = "";
	this->player.password = "";
	this->player.status = "";
}