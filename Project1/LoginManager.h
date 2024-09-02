#pragma once
#include "IDatabase.h"
#include<vector>



class LoginManager {

public:
	LoginManager();
	~LoginManager();

	void signup(std::string, std::string, std::string);
	void login(std::string, std::string);
	void logout(std::string);




private:
	//fields
	IDatabase* _database;
	std::vector<LoggedUser> _loggedUsers;

};


class LoggedUser
{
public:
	inline std::string getUserName() { return _userName; };
	//fields
	std::string _userName;
};