#pragma once
#include<string>
#include<vector>

class Question {
public:
	Question(std::string question, std::vector<std::string> answers, int correctnum/*starts at 0*/);
	~Question();

	//getters
	inline std::string getQuestion() { return _question; };
	inline std::vector<std::string>* getPossibleAnswers() { return &_possibleAnswers ; };
	inline int getCorrectAnswer() { return _correctAnswer; };



private:
	//fields
	std::string _question;
	std::vector< std::string> _possibleAnswers;
	int _correctAnswer;

};