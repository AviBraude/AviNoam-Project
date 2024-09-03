#pragma once
#include "Communicator.h"
#include "request.h"
#include <fstream>
#include "json.hpp"
#include <vector>

using json = nlohmann::json;

class JsonResponsePacketDeserializer
{
public:
	//static std::vector<unsigned char> deserializeResponse(ErrorResponse errorResponse);
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> loginMsg);
	static SigninRequest deserializeSignUpRequest(std::vector<unsigned char> signupMsg);
	void setMsgInfo(std::string &msg);
	// RequestInfo _myStruct;
};


