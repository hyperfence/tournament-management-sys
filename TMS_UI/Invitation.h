#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "InviteList.h"
#include "DBHandler.h"

class Invitation
{
private:
	InviteList* invites;

public:
	Invitation()
	{
		invites = NULL;
	}
	InviteList* getInvites(int playerID, int* count);
	bool sendInvite(int senderID, std::string receiverEmail, int teamID);
	void acceptInvite(int inviteID);
	void rejectInvite(int inviteID);
};

