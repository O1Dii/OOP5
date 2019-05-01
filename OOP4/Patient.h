#pragma once
#include "Person.h"
#include <string>


class Patient : public Person
{
private:
	char issue[50];
	char currentState[200];
public:
	friend std::ostream &operator<<(std::ostream &stream, Patient obj);
	Patient() : Person() {
		strcpy_s(this->issue, 50, "\0");
		strcpy_s(this->currentState, 200, "\0");
	}
	Patient operator=(Patient person);
	void setIssue(std::string issue);
	char * getIssue();
	void setCurrentState(std::string currentState);
	char * getCurrentState();
};

