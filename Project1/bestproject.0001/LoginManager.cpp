#include "LoginManager.h"
#include "SqliteDatabase.h"
#include"request.h"
#include <string>
#include <iostream>



LoginManager::LoginManager(IDatabase* db)
{
	_database = db;
}

LoginManager::~LoginManager()
{
}

int LoginManager::signup(SigninRequest rqst)
{
	int check;
	std::string name = rqst._userName;
	std::string password = rqst._password;
	std::string mail = rqst._email;
	_database->open();
	check = _database->doesUserExist(name);
	if (check)//name aleady exists
	{
		std::cout << "name already exist." << std::endl;
		_database->close();
		return 0;//error
	}
	else
	{
		check = _database->addNewUser(name, password, mail);
		if (check)
		{
			_database->close();
			return 0;//error with DB
		}
		else
		{
			//all good!!!
			std::cout << "sign in successfully." << std::endl;

			LoggedUser newUser(name);
			_loggedUsers.push_back(newUser);
			_database->close();
			return 1;
		}

	}

}

int LoginManager::login(LoginRequest rqst)
{
	int check;
	std::string name = rqst._userName;
	std::string password = rqst._password;
	//std::string mail = rqst.email;
	std::cout << "open database for validation" << std::endl;
	_database->open();
	check = _database->doesUserExist(name);
	if (!check)//name aleady exists
	{
		std::cout << "faild at name check - closing database" << std::endl;
		_database->close();
		return 0;//error
	}
	else
	{
		check = _database->doesPasswordMatch(name,password); // 0 - means good
		if (check != 0)//no match with password
		{

			std::cout << "faild at password check - closing database" << std::endl;
			_database->close();
			return 0;//bad
		}
		else
		{
			LoggedUser newUser(name);
			_loggedUsers.push_back(newUser);
			std::cout << "login succeessded - closing database" << std::endl;
			_database->close();
			return 1;//good
		}
	}

}

void LoginManager::logout(std::string name)
{
	LoggedUser newUser(name);
	auto it = std::find(_loggedUsers.begin(), _loggedUsers.end(),
		newUser);

	// If element is found found, erase it 
	if (it != _loggedUsers.end()) {
		_loggedUsers.erase(it);
	}
}

LoggedUser::LoggedUser(std::string name)
{
	_userName = name;
}

bool LoggedUser::operator==(const LoggedUser other)//dont know why it works
{
	if (this->getUserName() == other.getUserName())
	{
		return true;
	}
	return false;
}
