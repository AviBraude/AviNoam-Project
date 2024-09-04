#pragma once
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "LoginManager.h"
#include "RoomManager.h"
#include"rooms.h"


class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase& DB) : _myDB(&DB), _loginManager(&DB) {};
	LoginRequestHandler* creatLoginRequestHandler();
	LoginManager getLoginManager();
	
	MenuRequestHandler* creatMenuRequestHandler();
	RoomManager& getRoomManager();
	//statistics manger &

private:
	LoginManager _loginManager;
	IDatabase* _myDB;

	RoomManager _roomManager;
	// _statistics manager
};
