#pragma once
#include <chrono>
#include <vector>

class RequestResult;
class IRequestHandler
{
public:
	virtual bool isRequestRelevent(RequestInfo& a) = 0;
	virtual RequestResult handleRequest(RequestInfo& a) = 0;
};

struct RequestInfo
{
	unsigned int _msgCode;
	std::chrono::system_clock::time_point _msgTime;
	std::vector<unsigned char> _msgInfo;
};

struct RequestResult
{
	IRequestHandler* newHandler;
	std::vector<unsigned char> _msgBuffer;
};