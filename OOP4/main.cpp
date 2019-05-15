#include <iostream>
#include <list>
#include <map>
#include <fstream>
#include <queue>
#include "Good.h"
#include "Helper.h"

using namespace std;

/*
	priority_queue
	Учёт товаров в аптеке

	Название товара
	Страна производства
	Фирма производитель
	Количество на складе
	Цена
	Форма

*/


void menu(int & choice) {
	cout << "1. Добавить товар" << endl;
	cout << "2. Изменить товар" << endl;
	cout << "3. Просмотр всех товаров" << endl;
	cout << "4. Удаление товара" << endl;
	cout << "5. Поиск товара" << endl;
	cout << "6. Выход" << endl;
	do {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> choice;
	} while (!cin.good() && (choice < 1 || choice > 6));
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int choice, choice2, patIndex = 0;
	my_priority_queue<Good> goods;
	fstream f;
	Good item;

	f.open("Goods.txt", fstream::app || fstream::in);
	//f.open("Doctors.txt", fstream::out);
	while (f.peek() != EOF) {
		f.read((char*)&item, sizeof(Good));
		goods.push(item);
	}
	f.close();
	do {
		system("pause");
		system("cls");
		menu(choice);
		switch (choice) {
		case 1: 
		{
			item = Good();
			item = Helper::input(item);
			if (item.getName()[0] != '\0') {
				Helper::writeFile(item);
				goods.push(item);
			}
			break;
		}
		case 2: 
			item = Helper::outputDoctors(goods);
			if (item.getName()[0] != '\0') {
				Helper::menu_edit<Good>(choice2);
				Good doc2 = item;
				item = Helper::input(item, choice2);
				if (item.getName()[0] != '\0') {
					Helper::del(doc2);
					goods.remove(doc2);
					Helper::writeFile(item);
					goods.push(item);
				}
			}
			break;
		case 3:
			item = Helper::outputDoctors(goods);
			if (item.getName()[0] != '\0') {
				cout << item << endl;
			}
			break;
		case 4: {
			item = Helper::outputDoctors(goods);
			if (item.getName()[0] != '\0') {
				Helper::del(item);
				goods.remove(item);
			}
			break;
		}
		case 5:
			Helper::search(goods);
			break;
		default:
			break;
		}
	} while (choice != 6);
}