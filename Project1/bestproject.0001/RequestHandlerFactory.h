#pragma once
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "LoginManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	inline RequestHandlerFactory(IDatabase* DB) : _myDB(DB), _loginManager(_myDB) {};
	LoginRequestHandler* creatLoginRequestHandler();
	MenuRequestHandler* creatMenuRequestHandler();
	LoginManager getLoginManager();

private:
	LoginManager _loginManager;
	IDatabase* _myDB;

};
