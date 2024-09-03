#pragma once
#include "IRequestHandler.h"
#include "request.h"
#include <string>

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevent(RequestInfo& a);
	RequestResult handleRequest(RequestInfo& a);

private:
	RequestResult login(RequestInfo &a);
	RequestResult signup(RequestInfo &a);

};