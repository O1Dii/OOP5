#pragma once
#include "Person.h"
#include <string>

class Doctor : public Person
{
private:
	char description[200];
public:
	friend std::ostream &operator<<(std::ostream &stream, Doctor obj);
	Doctor() : Person() {
		strcpy_s(this->description, 200, "\0");
	}
	Doctor operator=(Doctor person);
	void setDescription(std::string description);
	char * getDescription();
};

