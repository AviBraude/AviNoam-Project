#include "LoginManager.h"
#include "SqliteDatabase.h"
#include"request.h"



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
		return 0;//error
	}
	else
	{
		check = _database->addNewUser(name, password, mail);
		if (check)
		{
			return 0;//error with DB
		}
		else
		{
			//all good!!!
			LoggedUser newUser(name);
			_loggedUsers.push_back(newUser);
			_database->close();
		}

	}

}

int LoginManager::login(LoginRequest rqst)
{
	int check;
	std::string name = rqst._userName;
	std::string password = rqst._password;
	//std::string mail = rqst.email;
	_database->open();
	check = _database->doesUserExist(name);
	if (check)//name aleady exists
	{
		//error
	}
	else
	{
		check = _database->doesPasswordMatch(name,password);
		if (check)//no match with password
		{
			return 0;//bad
		}
		else
		{
			LoggedUser newUser(name);
			_loggedUsers.push_back(newUser);
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
