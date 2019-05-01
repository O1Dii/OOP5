#include "Person.h"
#include <string>


Person::Person()
{
	strcpy_s(this->Email, 50, "\0");
	strcpy_s(this->Password, 50, "\0");
	strcpy_s(this->Tel, 20, "\0");
	strcpy_s(this->Name, 20, "\0");
	strcpy_s(this->SecName, 20, "\0");
	strcpy_s(this->Patronymic, 20, "\0");
	strcpy_s(this->Addr.addr, 50, "\0");
	this->Addr.num = 0;
	this->Addr.korpus = 0;
	this->Addr.kv = 0;
}

void Person::setValues(char &E, char &P, char &T, char &N, char &SN, char &Pat, char &Ad, int num, int korp, int kv)
{
	strcpy_s(this->Email, 50, &E);
	strcpy_s(this->Password, 50, &P);
	strcpy_s(this->Tel, 20, &T);
	strcpy_s(this->Name, 20, &N);
	strcpy_s(this->SecName, 20, &SN);
	strcpy_s(this->Patronymic, 20, &Pat);
	strcpy_s(this->Addr.addr, 50, &Ad);
	this->Addr.num = num;
	this->Addr.korpus = korp;
	this->Addr.kv = kv;
}

char * Person::getEmail()
{
	return Email;
}

char * Person::getPassword()
{
	return Password;
}

char * Person::getTel()
{
	return Tel;
}

char * Person::getName()
{
	return Name;
}

char * Person::getSecName()
{
	return SecName;
}

char * Person::getPatronymic()
{
	return Patronymic;
}

addr Person::getAddr()
{
	return Addr;
}

bool Person::operator==(Person a)
{
	if (strcmp(this->Addr.addr, a.Addr.addr))
		return false;
	if (strcmp(this->Email, a.Email))
		return false;
	if (strcmp(this->Password, a.Password))
		return false;
	if (strcmp(this->Name, a.Name))
		return false;
	if (strcmp(this->SecName, a.SecName))
		return false;
	if (strcmp(this->Patronymic, a.Patronymic))
		return false;
	if (strcmp(this->Tel, a.Tel))
		return false;
	if (this->Addr.korpus != a.Addr.korpus)
		return false;
	if (this->Addr.num != a.Addr.num)
		return false;
	return true;
}

bool Person::operator!=(Person a)
{
	return !(*this == a);
}

bool Person::operator<(const Person &man) const
{
	std::string SN1(this->SecName), SN2(man.SecName), N1(this->Name), N2(man.Name), Pat1(this->Patronymic), Pat2(this->Patronymic);
	if (SN1 == SN2) {
		if (N1 == N2) {
			return Pat1 < Pat2;
		}
		return N1 < N2;
	}
	return SN1 < SN2;
}

bool Person::operator>(const Person &man) const
{
	std::string Add1(this->Addr.addr), Add2(man.Addr.addr);
	if (Add1 == Add2) {
		if (this->Addr.num == this->Addr.num) {
			return this->Addr.korpus < man.Addr.korpus;
		}
		return this->Addr.num < man.Addr.num;
	}
	return Add1 < Add2;
}