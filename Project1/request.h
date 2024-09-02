#pragma once
#include <string>

#define  STATUS1 200;

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