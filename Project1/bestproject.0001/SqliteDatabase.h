#pragma once
#include "IDatabase.h"
#include"sqlite3.h"


class SQliteDatabase : public IDatabase
{
	
public:
	bool open();
	bool close();
	
	int doesUserExist(std::string);
	int doesPasswordMatch(std::string, std::string);
	int addNewUser(std::string, std::string, std::string);

	SQliteDatabase();
private:
	//helpers

	bool isfile(std::string);
	
	//fields
	sqlite3* _DB;
};