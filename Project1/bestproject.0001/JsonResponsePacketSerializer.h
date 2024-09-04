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
	
	static std::vector<unsigned char> serializeResponse(LogoutRespons logoutResponse);
	static std::vector<unsigned char> serializeResponse(GetRoomsRespons getRoomResponse);
	static std::vector<unsigned char> serializeResponse(GetPlayersInRoomResponse playersInRoomResponse);
	static std::vector<unsigned char> serializeResponse(JoinRoomRespons joinRoomResponse);
	static std::vector<unsigned char> serializeResponse(CreateRoomRespons createRoomResponse);
	static std::vector<unsigned char> serializeResponse(GetHigehScoreResponse highScoreResponse);
	static std::vector<unsigned char> serializeResponse(GetPersonalStatsResponse personalStateResponse);
	
	
	static std::vector<unsigned char> helpSerial(json jsonObject);
};


