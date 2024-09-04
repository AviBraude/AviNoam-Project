#include "Question.h"

Question::Question(std::string question, std::vector<std::string> answers, int correctnum/*starts at 0*/)
{
	_question = question;
	_possibleAnswers = answers;
	_correctAnswer = correctnum;
}

Question::~Question()
{
}
