#pragma once
#include "IDatabase.h"
#include<vector>
#include"request.h"


class LoggedUser;
class LoginManager 
{
public:
	LoginManager(IDatabase* db);
	~LoginManager();

	int signup(SigninRequest rqst);
	int login(LoginRequest rqst);
	void logout(std::string name);




private:
	//fields
	IDatabase* _database;
	std::vector<LoggedUser> _loggedUsers;

};


class LoggedUser
{

public:

	LoggedUser(std::string name);

	bool operator == (const LoggedUser);
	inline std::string getUserName()const { return _userName; };
	//fields
	std::string _userName;
};