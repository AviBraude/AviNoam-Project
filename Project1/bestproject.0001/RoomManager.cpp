#include "RoomManager.h"
#include <algorithm>
#include <string>

int RoomManager::createRoom(LoggedUser u, RoomData r)
{
	//Room* roomy = new 
	_rooms[r.id] = Room(u, r);
	return 1;
}

void RoomManager::deleteRoom(int id)
{
	_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(int id)
{
	return _rooms[id].getIsActive();
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> ourData;
	for_each(_rooms.begin(), _rooms.end(), [this, &ourData](std::pair<unsigned int, Room> it) {ourData.push_back(it.second.GetAllData()); });

	return ;
}

Room& RoomManager::getRoom(int id)
{
	return _rooms[id];
}
