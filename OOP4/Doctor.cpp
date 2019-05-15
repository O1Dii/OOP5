#include "Good.h"
#include <iostream>
#include <string>
#include <iomanip>


Good::Good() {
	strcpy_s(this->Name, 50, "\0");
	strcpy_s(this->ManufCountry, 50, "\0");
	strcpy_s(this->ManufName, 50, "\0");
	this->Amount = 0;
	this->Price = 0;
	strcpy_s(this->Shape, 20, "\0");
}

void Good::setValues(char&Name, char&ManufCountry, char&ManufName, int Amount, float Price, char&Shape)
{
	strcpy_s(this->Name, 50, &Name);
	strcpy_s(this->ManufCountry, 50, &ManufCountry);
	strcpy_s(this->ManufName, 50, &ManufName);
	this->Amount = Amount;
	this->Price = Price;
	strcpy_s(this->Shape, 20, &Shape);
}

char * Good::getName()
{
	return Name;
}

char * Good::getManufCountry()
{
	return ManufCountry;
}

char * Good::getManufName()
{
	return ManufName;
}

int Good::getAmount()
{
	return Amount;
}

float Good::getPrice()
{
	return Price;
}

char * Good::getShape()
{
	return Shape;
}

bool Good::operator==(Good a)
{
	if (strcmp(this->Name, a.Name))
		return false;
	if (strcmp(this->ManufCountry, a.ManufCountry))
		return false;
	if (strcmp(this->ManufName, a.ManufName))
		return false;
	if (this->Amount != a.Amount)
		return false;
	if (this->Price != a.Price)
		return false;
	if (strcmp(this->Shape, a.Shape))
		return false;
	return true;
}

bool Good::operator!=(Good a)
{
	return !(*this == a);
}

bool Good::operator<(const Good &man) const
{
	std::string N1(this->Name), N2(man.Name);
	float Price1 = this->Price, Price2 = man.Price;
	int Amount1 = this->Amount, Amount2 = man.Amount;
	if (N1 == N2) {
		if (Price1 == Price2) {
			return Amount1 < Amount2;
		}
		return N1 < N2;
	}
	return N1 < N2;
}

Good Good::operator=(Good Good)
{
	char Name[50], ManufCountry[50], ManufName[50], Shape[20];
	int Amount;
	float Price;
	strcpy_s(Name, 50, Good.getName());
	strcpy_s(ManufCountry, 50, Good.getManufCountry());
	strcpy_s(ManufName, 50, Good.getManufName());
	Amount = Good.getAmount();
	Price = Good.getPrice();
	strcpy_s(Shape, 20, Good.getShape());
	this->setValues(*Name, *ManufCountry, *ManufName, Amount, Price, *Shape);
	return *this;
}

std::ostream & operator<<(std::ostream & stream, Good obj)
{
	stream << "Название: " << obj.getName() << "\n";
	stream << "Страна производитель: " << obj.getManufCountry() << "\n";
	stream << "Компания производитель: " << obj.getManufName() << "\n";
	stream << "Количество на складе: " << obj.getAmount() << "\n";
	stream << "Цена: " << std::fixed << std::setprecision(2) << obj.getPrice() << '\n';
	stream << "Форма: " << obj.getShape();
	return stream;
}