#pragma once
#include <string>
#include <vector>
#include "request.h"

#define  STATUS1 200;
struct RoomData;

////////////////
/// RESPONSES //
////////////////

struct SignupResponse
{
	unsigned int _status;
};

struct LoginResponse
{
	unsigned int _status;
};

struct ErrorResponse
{
	std::string _message;
};

struct LogoutRespons
{
	unsigned int _status;
};

struct JoinRoomRespons
{
	unsigned int _status;
};

struct CreateRoomRespons
{
	unsigned int _status;
};

struct GetRoomsRespons
{
	unsigned int _status;
	std::vector<RoomData> _rooms;
};

struct GetHigehScoreResponse
{
	unsigned int _status;
	std::vector<std::string> _statistics;
};

struct GetPersonalStatsResponse
{
	unsigned int _status;
	std::vector<std::string> _statistics;
};

struct GetPlayersInRoomResponse
{
	std::vector<std::string> _players;
};

///////////////
/// REQUEST ///
///////////////

struct LoginRequest
{
	std::string _userName;
	std::string _password;
};

struct SigninRequest
{
	std::string _userName;
	std::string _password;
	std::string _email;
};

struct GetPlayersInRoomRequest
{
	unsigned int roomID;
};

struct JoinRoomRequest
{
	unsigned int roomID;
};

struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};