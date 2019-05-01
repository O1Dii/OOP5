#pragma once
#include <string>
#include <iostream>

struct addr {
	char addr[50];
	int num;
	int korpus;
	int kv;
};

class Person
{
private:
	char Email[50];
	char Password[50];
	char Tel[20];
	char Name[20];
	char SecName[20];
	char Patronymic[20];
	addr Addr;
public:
	Person();
	void setValues(char&Email, char&Password, char&Tel, char&Name, char&SecName, char&Pat, char&Ad, int num, int korp, int kv);
	char* getEmail();
	char* getPassword();
	char* getTel();
	char* getName();
	char* getSecName();
	char* getPatronymic();
	addr getAddr();
	bool operator ==(Person);
	bool operator !=(Person);
	bool operator <(const Person&) const;
	bool operator >(const Person&) const;
};

