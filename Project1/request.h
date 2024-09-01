#pragma once
#include <string>



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