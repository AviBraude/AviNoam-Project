#include "SqliteDatabase.h"
#include"sqlite3.h"
#include <iostream>
#include <fstream>



bool SQliteDatabase::open()
{
	//will print the table content if i will want
	//i put it here so the sqlite3_exe() would work

	char* zErrMsg;
	 _DB = nullptr;
	int check;

	std::string dbName;
	bool existsFlag = false;
	if (isfile(dbName))
	{
		existsFlag = true;
	}
	check = sqlite3_open("mydb.db", &_DB);//will it stay open outside of scope??
	if (check)
	{
		std::cout << "Can't open database" << std::endl;
	}
	else
	{	//only initializes if didnt already exist.
		if (!existsFlag)
		{
			std::cout << "Opened database successfully" << std::endl;
		
			const char* sql = "CREATE TABLE Users("  \
			"NAME PRIMARY KEY TEXT NOT NULL," \
			"MAIL TEXT NOT NULL," \
			"PASSWORD TEXT NOT NULL."")";

		check = sqlite3_exec(this->_DB, sql, nullptr, nullptr, &zErrMsg);
		}
	}
}

bool SQliteDatabase::close()
{
	delete _DB;
	std::cout << "closed DB";
}

int SQliteDatabase::doesUserExist(std::string)
{
	
}

bool SQliteDatabase::isfile(std::string fileName)
{
	std::ifstream f;
	f.open(fileName);
	if (f)
	{
		return true;
	}
	return false;
}


