#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	inline MenuRequestHandler(RequestHandlerFactory& factory) : _factory(factory) {};
	virtual bool isRequestRelevent(RequestInfo& a);
	virtual RequestResult handleRequest(RequestInfo& a);
private:
	RequestHandlerFactory& _factory;
};