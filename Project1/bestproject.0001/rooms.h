#pragma once

#include <string>
#include <vector>
#include "LoginManager.h"
class LoggedUser;

struct RoomData
{
public:
	std::string name;
	unsigned int id;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;

private:
};

struct Room
{
public:
	Room(LoggedUser u, RoomData r);
	void addUser(LoggedUser u);
	void renoveUser(LoggedUser u);
	std::vector<std::string> getAllUsers();
	unsigned int getIsActive();
	RoomData GetAllData();

private:
	RoomData _metadata;
	std::vector<LoggedUser> _users;
};