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
	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(std::vector<unsigned char> getPlayersMsg);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char> JoinRoomMsg);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char> CreateRoomMsg);
	void setMsgInfo(std::string &msg);
	// RequestInfo _myStruct;
};


