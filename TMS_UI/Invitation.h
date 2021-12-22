#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "DBHandler.h"

struct InviteList
{
	int inviteID;
	int teamID;
	InviteList* next;
};

class Invitation
{
private:
	InviteList* invites;

public:
	Invitation()
	{
		invites = NULL;
	}
	InviteList* getInvites(int playerID);
	void sendInvite(int senderID, int receiverID, int teamID);
	void acceptInvite(int inviteID);
	void rejectInvite(int inviteID);
};

