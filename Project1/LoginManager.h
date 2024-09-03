#pragma once
#include "IDatabase.h"
#include<vector>
#include"LoginRequest.h"



class LoginManager {

public:
	LoginManager(IDatabase* db);
	~LoginManager();

	int signup(SignupRequest rqst);
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
	inline std::string getUserName() { return _userName; };
	//fields
	std::string _userName;
};