#include "SqliteDatabase.h"
#include"sqlite3.h"
#include <iostream>
#include <fstream>
#include<vector>
#include"Question.h"

int intcallback(void* data, int argc, char** argv, char** azColName);
int callbackQuestions(void* data, int argc, char** argv, char** azColName);




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
			"PASSWORD TEXT NOT NULL"")";



		check = sqlite3_exec(this->_DB, sql, nullptr, nullptr, &zErrMsg);
		sql = "CREATE TABLE QUESTIONS("  \
			"QUESTION TEXT PRIMARY KEY  NOT NULL," \
			"ANSWER1 TEXT NOT NULL," \
			"ANSWER2 TEXT NOT NULL," \
			"ANSWER3 TEXT NOT NULL," \
			"ANSWER4 TEXT NOT NULL," \
			"CORRECT_ANSWER TEXT NOT NULL"")";
		check = sqlite3_exec(this->_DB, sql, nullptr, nullptr, &zErrMsg);

		sql = "INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, CORRECT_ANSWER)" \
			"VALUES(\"What does SQL stand for?\", \"Standard Query Language\", \"Structured Query Language\", \"Secure Query Language\", \"Sequential Query Language\", \"2\"); ";

		check = sqlite3_exec(this->_DB, sql, nullptr, nullptr, &zErrMsg);

		sql = "INSERT INTO QUESTIONS (QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, CORRECT_ANSWER) "
			"VALUES (\"What is a common term for unauthorized access to a system?\", \"Phishing\", \"Malware\", \"Hacking\", \"Spoofing\", \"3\");";
		check = sqlite3_exec(this->_DB, sql, nullptr, nullptr, &zErrMsg);

		sql =
			"INSERT INTO QUESTIONS (QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, CORRECT_ANSWER) "
			"VALUES (\"What is the purpose of a firewall?\", \"To monitor network traffic\", \"To prevent unauthorized access\", \"To store data securely\", \"To encrypt communications\", \"2\");";

		check = sqlite3_exec(this->_DB, sql, nullptr, nullptr, &zErrMsg);
		
		sql = "INSERT INTO QUESTIONS (QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, CORRECT_ANSWER)  "
			"VALUES (\"Which protocol is commonly used for secure web transactions?\", \"HTTP\", \"FTP\", \"HTTPS\", \"SMTP\", \"1\");\n";
			
		check = sqlite3_exec(this->_DB, sql, nullptr, nullptr, &zErrMsg);
		sql = "INSERT INTO QUESTIONS (QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, CORRECT_ANSWER) "
			"VALUES (\"What is the main goal of a DDoS attack?\", \"To steal sensitive data\", \"To damage hardware\", \"To overwhelm a system\", \"To alter system configurations\", \"3\");";
		check = sqlite3_exec(this->_DB, sql, nullptr, nullptr, &zErrMsg);


		sql = "INSERT INTO QUESTIONS (QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, CORRECT_ANSWER) "
			"VALUES (\"What does VPN stand for?\", \"Virtual Private Network\", \"Verified Public Network\", \"Virtual Public Node\", \"Verified Private Node\", \"1\");";
		check = sqlite3_exec(this->_DB, sql, nullptr, nullptr, &zErrMsg);

		sql = "INSERT INTO QUESTIONS (QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, CORRECT_ANSWER) "
			"VALUES (\"Which of the following is a type of malware?\", \"Firewall\", \"Antivirus\", \"Worm\", \"VPN\", \"3\");";
		check = sqlite3_exec(this->_DB, sql, nullptr, nullptr, &zErrMsg);
		
		sql = "INSERT INTO QUESTIONS (QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, CORRECT_ANSWER) "
			"VALUES (\"What is phishing?\", \"A type of virus\", \"A technique to steal sensitive information\", \"A network attack\", \"A form of data encryption\", \"2\");";
		check = sqlite3_exec(this->_DB, sql, nullptr, nullptr, &zErrMsg);

		sql = "INSERT INTO QUESTIONS (QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, CORRECT_ANSWER) "
			"VALUES (\"What is the purpose of two-factor authentication (2FA)?\", \"To encrypt data\", \"To provide an additional layer of security\", \"To monitor network activity\", \"To create backups\", \"2\");";
		check = sqlite3_exec(this->_DB, sql, nullptr, nullptr, &zErrMsg);

		sql = "INSERT INTO QUESTIONS (QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4, CORRECT_ANSWER) "
			"VALUES (\"What is a zero-day exploit?\", \"An exploit for a known vulnerability\", \"An exploit that occurs after a patch is released\", \"An exploit for a previously unknown vulnerability\", \"An exploit that requires user intervention\", \"3\");";
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
	check = sqlite3_exec(this->_DB, querry.c_str(), intcallback, &countName, &zErrMsg);//callback func
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
	check = sqlite3_exec(this->_DB, querry.c_str(), intcallback, &countName, &zErrMsg);//callback func
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
	std::string querry = "INSERT INTO Users (NAME, PASSWORD, MAIL)\
		VALUES('"+name +"', '"+ password+"', '"+mail+"'); ";

	check = sqlite3_exec(this->_DB, querry.c_str(), nullptr, nullptr, &zErrMsg);//callback func
	if (check)
	{
		return -1;
	}
	return 0;
	
}

std::list<Question>* SQliteDatabase::getQuestions(int amount)
{
	int check;
	char* zErrMsg;
	std::string querry;
	querry = "SELECT * from QUESTIONS LIMIT '" + std::to_string(amount) + "';";
	std::list<Question>* questionsAndAnswers = new std::list<Question>;
	check = sqlite3_exec(this->_DB, querry.c_str(), callbackQuestions, &questionsAndAnswers, &zErrMsg);//callback func
	return questionsAndAnswers;
}

float SQliteDatabase::getPlayerAverageAnswerTime(std::string)
{
	return 0.0f;
}

int SQliteDatabase::getNumOfCorrectAnswers(std::string)
{
	return 0;
}

int SQliteDatabase::getNumOfTotalAnswers(std::string)
{
	return 0;
}

int SQliteDatabase::getNumOfPlayerGames(std::string)
{
	return 0;
}

int SQliteDatabase::getPlayerScore(std::string)
{
	return 0;
}

std::vector<std::string> SQliteDatabase::getHighScores()
{
	return std::vector<std::string>();
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

int intcallback(void* data, int argc, char** argv, char** azColName)
{
	int* count = (int*)data;
	*count = atoi(argv[0]);
	
	return 0;
	
}

int callbackQuestions(void* data, int argc, char** argv, char** azColName)
{
	int i;
	std::string temp;
	std::list<Question>* res= (std::list<Question>*)data;
	std::string question = argv[0];

	std::vector<std::string> answers;
	answers.push_back(argv[1]);//answer1
	answers.push_back(argv[2]);//answer2
	answers.push_back(argv[3]);//answer3
	answers.push_back(argv[4]);//answer4
	
	int correctNum = (int)argv[5];
		
	Question currentRow = Question(question,answers, correctNum);
	res->push_back(currentRow);




	//for (i = 0; i < argc; i++) 
	//{
	//	temp += azColName[i];
	//	temp += ", ";
	//	temp+= argv[i];
	//	temp += ".";
	//}
	//res->pop_back();//pop the "."at the end
	//res->push_back(temp);

	return 0;
	
}

