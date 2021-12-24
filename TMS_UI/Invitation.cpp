#include "Invitation.h"

InviteList* Invitation::getInvites(int playerID, int* count)
{
	if (DBHandler::getInvitesDB(playerID, this->invites, count) == true)
	{
		return this->invites;
	}
	return nullptr;
}
bool Invitation::sendInvite(int senderID, std::string receiverEmail, int teamID)
{
	if (DBHandler::sendInvite(senderID, receiverEmail, teamID) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Invitation::acceptInvite(int inviteID)
{
	DBHandler::updateInvite(inviteID, 1);
}
void Invitation::rejectInvite(int inviteID)
{
	DBHandler::updateInvite(inviteID, 0);
}