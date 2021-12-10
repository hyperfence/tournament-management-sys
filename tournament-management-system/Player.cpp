#include "Player.h"

Player::Player()
{
}
Player::Player(int id, string name, string email, string pass)
{
	this->player.id = id;
	this->player.name = name;
	this->player.email = email;
	this->player.password = pass;
}
void Player::displayDetails()
{
	cout << "************ Player Details ************" << endl;
	cout << "ID: " << this->player.id << endl;
	cout << "Name: " << this->player.name << endl;
	cout << "Email: " << this->player.email << endl;
	cout << "Password: " << this->player.password << endl;
	cout << "****************************************" << endl;
	;
}