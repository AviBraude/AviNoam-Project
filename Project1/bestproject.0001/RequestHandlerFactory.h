#pragma once
#include "LoginRequestHandler.h"
#include "IDatabase.h"
#include "LoginManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase& DB) : _myDB(&DB), _loginManager(&DB) {};
	LoginRequestHandler* creatLoginRequestHandler();
	MenuRequestHandler* creatMenuRequestHandler();
	LoginManager getLoginManager();
	
private:
	LoginManager _loginManager;
	IDatabase* _myDB;

};
