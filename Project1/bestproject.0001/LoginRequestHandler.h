#pragma once
#include "IRequestHandler.h"
#include "request.h"
#include <string>
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	inline LoginRequestHandler(RequestHandlerFactory& factory) : _factory(factory) {};
	bool isRequestRelevent(RequestInfo& a);
	RequestResult handleRequest(RequestInfo& a);

private:
	RequestResult login(RequestInfo &a);
	RequestResult signup(RequestInfo &a);
	RequestHandlerFactory& _factory;

};