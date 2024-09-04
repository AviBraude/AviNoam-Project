#pragma once
#include <string>
#include<list>
#include "Question.h"


class IDatabase
{
public:
	//methods
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(std::string) = 0;
	virtual int doesPasswordMatch(std::string, std::string) = 0;
	virtual int addNewUser(std::string, std::string, std::string)= 0;
	virtual std::list<Question>* getQuestions(int) = 0;
	virtual float getPlayerAverageAnswerTime(std::string) = 0;
	virtual int getNumOfCorrectAnswers(std::string) = 0;
	virtual int getNumOfTotalAnswers(std::string) = 0;
	virtual int getNumOfPlayerGames(std::string) = 0;
	virtual int getPlayerScore(std::string) = 0;
	virtual std::vector<std::string> getHighScores() = 0;






};
