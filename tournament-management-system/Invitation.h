#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Invitation
{
public:
	vector <int> getInvitations(int playerID);
	void sendInvitation(int senderID, int receiverID, int teamID);
	void acceptInvitation(int invitationID);
	void rejectInvitation(int invitationID);
};

