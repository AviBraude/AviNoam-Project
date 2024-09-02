#pragma once
#include "IDatabase.h"
#include"sqlite3.h"


class SQliteDatabase : IDatabase
{
	bool open();
	bool close();
	
	int doesUserExist(std::string);
	int doesPasswordMatch(std::string, std::string);
	int addNewUser(std::string, std::string, std::string);

private:
	//helpers
	bool isfile(std::string);
	
	//fields
	sqlite3* _DB;
};