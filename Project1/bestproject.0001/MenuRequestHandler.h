#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	inline MenuRequestHandler(RequestHandlerFactory& factory) : _factory(factory) {};
	virtual bool isRequestRelevent(RequestInfo& a);
	virtual RequestResult handleRequest(RequestInfo& a);

private:
	RequestResult signout(RequestInfo& a);
	RequestResult getRooms(RequestInfo& a);
	RequestResult getPlayerInRoom(RequestInfo& a);
	RequestResult getPersonalStats(RequestInfo& a);
	RequestResult getHighScore(RequestInfo& a);
	RequestResult joinRoom(RequestInfo& a);
	RequestResult createRoom(RequestInfo& a);



	RequestHandlerFactory& _factory;
	LoggedUser _user;
};