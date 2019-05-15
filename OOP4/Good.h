#pragma once
#include <string>

class Good
{
private:
	char Name[50];
	char ManufCountry[50];
	char ManufName[50];
	int Amount;
	float Price;
	char Shape[20];
public:
	/*
	Название товара
	Страна производства
	Фирма производитель
	Количество на складе
	Цена
	Форма
	*/
	Good();
	void setValues(char&Name, char&ManufCountry, char&ManufName, int Amount, float Price, char&Shape);
	char* getName();
	char* getManufCountry();
	char* getManufName();
	int getAmount();
	float getPrice();
	char* getShape();
	friend std::ostream &operator<<(std::ostream &stream, Good obj);
	Good operator=(Good Good);
	bool operator ==(Good);
	bool operator !=(Good);
	bool operator <(const Good&) const;
};

