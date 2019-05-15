#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include "Good.h"
#include "my_priority_queue.h"

using namespace std;


class Helper
{
public:
	template <class T>
	static bool del(T);
	template <class T>
	static void menu_edit(int & choice);
	static Good input(Good & good, int field = 0);
	template <class T>
	static void writeFile(T & Good);
	static Good outputDoctors(my_priority_queue<Good> goods);
	//static void sort(my_priority_queue<Good> & goods);
	static void search(my_priority_queue<Good> & goods);
};


inline void Helper::search(my_priority_queue<Good> & goods) {
	cout << "Введите нужное лекарство" << endl;
	string str;
	cin >> str;
	bool flag = false;
	for (auto & item : goods) {
		if (!strcmp(item.getName(), str.c_str())) {
			if (flag) {
				cout << "--------------------------" << endl;
			}
			cout << item << endl;
			flag = true;
		}
	}
	if (!flag) {
		cout << "Нет таких лекарств" << endl;
	}
}


template<class T>
inline void Helper::writeFile(T & item)
{
	ofstream f;
	if (is_same<T, Good>::value) {
		f.open("Goods.txt", ofstream::app);
	}
	if (f.is_open()) {
		f.write((char*)&item, sizeof(T));
		f.close();
	}
}


inline Good Helper::input(Good & good, int field)
{
	char ch = 0, N[50], MC[50], MN[50], S[20];
	int A;
	float P;
	string output, name, manufCountry, manufName, shape, amount, price;
	strcpy_s(N, 50, good.getName());
	strcpy_s(MC, 50, good.getManufCountry());
	strcpy_s(MN, 50, good.getManufName());
	A = good.getAmount();
	P = good.getPrice();
	strcpy_s(S, 20, good.getShape());
	ifstream f1;
	int format = 0, i = 0, format_pos = 50;
	switch (field) {
	case 0:
	case 1:
	{
		output += "Введите название лекарства(на русском)";
		system("cls");
		cout << output << endl;
		output += '\n';
		ch = 0;
		while (ch != 13) {
			ch = _getch();
			if (ch == '\b' && !name.empty()) {
				name.pop_back();
				system("cls");
				output.pop_back();
				cout << output;
			}
			if (ch >= 'А' && ch <= 'Я') {
				ch += 32;
				name += ch;
				output += ch;
				cout << ch;
			}
			else if (ch >= 'а' && ch <= 'я') {
				name += ch;
				output += ch;
				cout << ch;
			}
		}
		system("cls");		
		cout << output << endl;
	}
	strcpy_s(N, 50, name.c_str());
	if (field != 0) {
		bool flag = true;
		Good item;
		f1.open("Goods.txt");
		while (f1.peek() != EOF) {
			f1.read((char*)&item, sizeof(Good));
			if (!strcmp(item.getName(), name.c_str()) && !strcmp(item.getManufName(), MN)) {
				flag = false;
			}
		}
		f1.close();
		if (flag == false) {
			cout << "Такой товар уже существует" << endl;
			return Good();
		}
		break;
	}	
	output += '\n';
	case 2:
	{
		output += "Введите страну производителя";
		system("cls");
		cout << output << endl;
		output += '\n';
		ch = 0;
		while (ch != 13) {
			ch = _getch();
			if (ch == '\b' && !manufCountry.empty()) {
				manufCountry.pop_back();
				system("cls");
				output.pop_back();
				cout << output;
			}
			if (ch >= 'А' && ch <= 'Я') {
				ch += 32;
				manufCountry += ch;
				output += ch;
				cout << ch;
			}
			else if (ch >= 'а' && ch <= 'я') {
				manufCountry += ch;
				output += ch;
				cout << ch;
			}
		}
		system("cls");	
		cout << output << endl;
		strcpy_s(MC, 50, manufCountry.c_str());
		if (field != 0) {
			break;
		}	
		output += '\n';
	}
	case 3:
	{
		output += "Введите название компании производителя";
		system("cls");
		cout << output << endl;
		output += '\n';
		ch = 0;
		while (ch != 13) {
			ch = _getch();
			if (ch == '\b' && !manufName.empty()) {
				manufName.pop_back();
				system("cls");
				output.pop_back();
				cout << output;
			}
			if (ch >= 'А' && ch <= 'Я') {
				ch += 32;
				manufName += ch;
				output += ch;
				cout << ch;
			}
			else if (ch >= 'а' && ch <= 'я') {
				manufName += ch;
				output += ch;
				cout << ch;
			}
		}
		system("cls");		
		cout << output << endl;

		bool flag = true;
		Good item;
		f1.open("Goods.txt");
		while (f1.peek() != EOF) {
			f1.read((char*)&item, sizeof(Good));
			if (!strcmp(item.getName(), N) && !strcmp(item.getManufName(), manufName.c_str())) {
				flag = false;
			}
		}
		f1.close();
		if (flag == false) {
			cout << "Такой товар уже существует" << endl;
			return Good();
		}

		strcpy_s(MN, 50, manufName.c_str());
		if (field != 0) {
			break;
		}		
		output += '\n';
	}
	case 4:
	{
		output += "Введите количество продуктов на складе";
		system("cls");
		cout << output << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		amount.clear();
		while (amount.length() == 0) {
			ch = 0;
			while (ch != 13) {
				ch = _getch();
				if (ch == '\b' && amount.length() != 0) {
					amount.pop_back();
					system("cls");
					cout << output << endl;
					cout << amount;
				}
				if (ch >= '0' && ch <= '9' && amount.length() <= 2) {
					amount += ch;
					cout << ch;
				}
			}
		}
		output += '\n';
		output += amount;
		output += '\n';
		cout << endl;
		A = atoi(amount.c_str());
		if (field != 0) {
			break;
		}
	}
	case 5:
	{
		output += "Введите цену товара";
		system("cls");
		cout << output << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		price.clear();
		bool flag = true;
		int sep = 0;
		while (price.length() == 0) {
			ch = 0;
			while (ch != 13) {
				ch = _getch();
				if (ch == '\b' && price.length() != 0) {
					if (price.length() == sep) {
						flag = true;
					}
					price.pop_back();
					system("cls");
					cout << output << endl;
					cout << price;
				}
				if (ch >= '0' && ch <= '9' && price.length() <= 5 && price.length() - sep <= 2) {
					price += ch;
					cout << ch;
				}
				if (ch == '.' && flag) {
					price += ch;
					cout << ch;
					flag = false;
					sep = price.length();
				}
			}
		}
		output += '\n';
		output += price;
		output += '\n';
		cout << endl;
		P = round((float)atof(price.c_str()) * 100) / 100;
		if (field != 0) {
			break;
		}
	}
	case 6:
	{
		short int pos = 0;
		vector<string> vect = { "таблетки", "спреи", "свечи", "конфеты", "пластерь" };
		shape = vect[0];
		output += "Выберите форму\n";
		system("cls");
		cout << output;
		cout << shape;
		ch = 0;
		while (ch != 13) {
			ch = _getch();
			if (ch == -32) {
				ch = _getch();
				if (ch == 75) {
					pos--;
					if (pos < 0)
						pos = (short)vect.size() - 1;
					shape = vect[pos];
					system("cls");
					cout << output;
					cout << shape;
				}
				else if (ch == 77) {
					pos++;
					if (pos > (short)vect.size() - 1)
						pos = 0;
					shape = vect[pos];
					system("cls");
					cout << output;
					cout << shape;
				}
				else if (ch == '\0')
					ch = 'а';
			}
		}
		output += '\n';
		output += shape;
		output += '\n';
		cout << endl;
		strcpy_s(S, 20, shape.c_str());
		if (field != 0) {
			break;
		}
	}
	default:
		break;
	}

	good.setValues(*N, *MC, *MN, A, P, *S);
	return good;
}

template <class T>
inline bool Helper::del(T ob)
{
	string file = "Goods.txt";
	fstream f;
	f.open(file, fstream::in || fstream::app);
	T man;
	deque<T> d;
	while (!f.eof()) {
		f.read((char*)&man, sizeof(T));
		if (d.size() != 0) {
			if (man != d[d.size() - 1])
				d.push_back(man);
		}
		else
			d.push_back(man);
	}
	f.close();
	f.open(file, fstream::out);
	while (!d.empty()) {
		man = d.at(0);
		d.pop_front();
		if (man != ob)
			f.write((char*)&man, sizeof(T));
	}
	f.close();
	return true;
}

template<class T>
inline void Helper::menu_edit(int & choice)
{
	cout << "1. Название" << endl;
	cout << "2. Страну производителя" << endl;
	cout << "3. Название компании производителя" << endl;
	cout << "4. Количество на складе" << endl;
	cout << "5. Цена за единицу продукци" << endl;
	cout << "6. Форма" << endl;
	do {
		cin >> choice;
	} while (!cin.good() && (choice < 1 || choice > 6));
}