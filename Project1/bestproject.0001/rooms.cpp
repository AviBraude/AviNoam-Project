#include "rooms.h"
#include <algorithm>

Room::Room(LoggedUser u, RoomData r)
{
	_users.push_back(u);
	_metadata.id = r.id;
	_metadata.name = r.name;
	_metadata.isActive = r.isActive;
	_metadata.maxPlayers = r.maxPlayers;
	_metadata.timePerQuestion = r.timePerQuestion;
	_metadata.numOfQuestionsInGame = r.numOfQuestionsInGame;
}

void Room::addUser(LoggedUser u)
{
	_users.push_back(u);
}

void Room::renoveUser(LoggedUser u)
{
	auto it = std::find(_users.begin(), _users.end(), u);
	if (it != _users.end())
		_users.erase(it);
}

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> names;
	for_each(_users.begin(), _users.end(), [this, &names](LoggedUser it) {names.push_back(it.getUserName()); });
	return names;
}

unsigned int Room::getIsActive()
{
	return _metadata.isActive;
}

RoomData Room::GetAllData()
{
	return _metadata;
}
