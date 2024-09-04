#pragma once
#include <map>
#include "rooms.h"
#include "request.h"
#include <vector>
#include <string>
#include "LoginManager.h"

class RoomManager
{
public:
	void createRoom(LoggedUser u, RoomData r);
	void deleteRoom(int id);
	unsigned int getRoomState(int id);
	std::vector<RoomData> getRooms();
	Room& getRoom(int id);

private:
	std::map<unsigned int, Room> _rooms;
};