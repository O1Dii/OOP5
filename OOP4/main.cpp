#include <iostream>
#include <list>
#include <map>
#include <fstream>
#include "Doctor.h"
#include "Patient.h"
#include "Helper.h"

using namespace std;


void menu(int & choice) {
	cout << "1. Добавить врача" << endl;
	cout << "2. Изменить врача" << endl;
	cout << "3. Просмотр всех врачей" << endl;
	cout << "4. Удаление врача" << endl;
	cout << "5. Добавить пациента" << endl;
	cout << "6. Изменить пациента" << endl;
	cout << "7. Просмотр пациентов" << endl;
	cout << "8. Удаление пациента" << endl;
	cout << "9. Сортировка врачей" << endl;
	cout << "10. Поиск пациента" << endl;
	cout << "11. Выход" << endl;
	do {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin >> choice;
	} while (!cin.good() && (choice < 1 || choice > 11));
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int choice, choice2, patIndex = 0;
	list<Doctor> doctors;
	map<int, Patient> patients;
	pair<int, Patient> pair;
	fstream f;
	Patient pat;
	Doctor doc;

	f.open("Users.txt", fstream::app || fstream::in);
	//f.open("Users.txt", fstream::out);
	int i = 0;
	while (f.peek() != EOF) {
		f.read((char*)&pat, sizeof(Patient));
		patients.insert({ i, pat });
		i++;
	}
	f.close();
	f.open("Doctors.txt", fstream::app || fstream::in);
	//f.open("Doctors.txt", fstream::out);
	while (f.peek() != EOF) {
		f.read((char*)&doc, sizeof(Doctor));
		doctors.push_back(doc);
	}
	f.close();
	do {
		system("pause");
		system("cls");
		menu(choice);
		switch (choice) {
		case 1: 
			doctors.push_back(Helper::input<Doctor>());
			break;	
		case 2: 
			doc = Helper::outputDoctors(doctors);
			if (doc.getEmail() != "\0") {
				Helper::menu_edit<Doctor>(choice2);
				doctors.remove(doc);
				doctors.push_back(Helper::input<Doctor>(&doc, choice2));
			}
			break;
		case 3:
			doc = Helper::outputDoctors(doctors);
			if (doc.getEmail() != "\0") {
				cout << doc << endl;
			}
			break;
		case 4: {
			doc = Helper::outputDoctors(doctors);
			if (doc.getEmail() != "\0") {
				doctors.remove(doc);
			}
			break;
		}
		case 5:
			patients.insert({ patIndex, Helper::input<Patient>() });
			patIndex++;
			break;
		case 6:
			pair = Helper::outputPatients(patients);
			if (pair.second.getEmail() != "\0") {
				Helper::menu_edit<Patient>(choice2);
				patients.erase(pair.first);
				patients.insert({ pair.first, Helper::input<Patient>(&pair.second, choice2) });
			}
			break;
		case 7:
			pair = Helper::outputPatients(patients);
			if (pair.second.getEmail() != "\0") {
				cout << pair.second << endl;
			}
			break;
		case 8:
			pair = Helper::outputPatients(patients);
			if (pair.second.getEmail() != "\0") {
				patients.erase(pair.first);
			}
			break;
		case 9:
			Helper::sort(doctors);
			break;
		case 10:
			Helper::search(patients);
			break;
		default:
			break;
		}
	} while (choice != 11);
}