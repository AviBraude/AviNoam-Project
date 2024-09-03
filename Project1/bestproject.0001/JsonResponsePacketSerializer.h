#pragma once
#include "Communicator.h"
#include "request.h"
#include <fstream>
#include "json.hpp"
#include <vector>

using json = nlohmann::json;

class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse errorResponse);
	static std::vector<unsigned char> serializeResponse(LoginResponse loginResponse);
	static std::vector<unsigned char> serializeResponse(SignupResponse signupResponse);
	static std::vector<unsigned char> helpSerial(json jsonObject);
};


