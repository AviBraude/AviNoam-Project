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