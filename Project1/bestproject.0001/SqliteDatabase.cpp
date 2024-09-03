#include "SqliteDatabase.h"
#include"sqlite3.h"
#include <iostream>
#include <fstream>
#include<vector>

int mycallback(void* data, int argc, char** argv, char** azColName);




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
		return false;
	}
	else
	{	//only initializes if didnt already exist.
		if (!existsFlag)
		{
			std::cout << "Opened database successfully" << std::endl;
		
			const char* sql = "CREATE TABLE Users("  \
			"NAME TEXT PRIMARY KEY  NOT NULL," \
			"MAIL TEXT NOT NULL," \
			"PASSWORD TEXT NOT NULL."")";

		check = sqlite3_exec(this->_DB, sql, nullptr, nullptr, &zErrMsg);
		}
	}
	return true;
}

bool SQliteDatabase::close()
{
	//delete _DB;
	sqlite3_close(_DB);
	std::cout << "closed DB";
	return true;
}

int SQliteDatabase::doesUserExist(std::string currentName)
{
	int check;
	char* zErrMsg;
	std::string querry = "SELECT count(Name) from Users Where Name ='" + currentName + "';";
	//std::vector<std::string>* names = new std::vector<std::string> ;
	int countName;
	check = sqlite3_exec(this->_DB, querry.c_str(), mycallback, &countName, &zErrMsg);//callback func
	if (countName > 0)
	{
		return -1;//name is already taken
	}
	return 0;//good name doesnt exist yet and is valid
	
}

int SQliteDatabase::doesPasswordMatch(std::string currentName, std::string password)
{

	int check;
	char* zErrMsg;
	std::string querry = "SELECT count(Name) from Users Where Name ='" + currentName + "'\
			AND PASSWORD = '" + password+"'; ";
	//std::vector<std::string>* names = new std::vector<std::string> ;
	int countName;
	check = sqlite3_exec(this->_DB, querry.c_str(), mycallback, &countName, &zErrMsg);//callback func
	if (countName == 0)
	{
		return -1;//no match between name and password
	}
	return 0;//name and password match

}

int SQliteDatabase::addNewUser(std::string name, std::string password, std::string mail)
{
	int check;
	char* zErrMsg;
	std::string querry = "INSERT INTO Users (Name, Password, Email)\
		VALUES('"+name +"', '"+ password+"', '"+mail+"'); ";

	check = sqlite3_exec(this->_DB, querry.c_str(), nullptr, nullptr, &zErrMsg);//callback func
	if (check)
	{
		return -1;
	}
	return 0;
	
}

SQliteDatabase::SQliteDatabase()
{
	_DB = nullptr;
}

bool SQliteDatabase::isfile(std::string fileName)
{
	std::ifstream f;
	f.open(fileName);
	if (f)
	{
		f.close();
		return true;
	}
	return false;
}

int mycallback(void* data, int argc, char** argv, char** azColName)
{
	int* count = (int*)data;
	*count = atoi(argv[0]);
	
	return 0;
	
}

