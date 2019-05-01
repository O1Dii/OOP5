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
#include "Doctor.h"
#include "Patient.h"

using namespace std;


class Helper
{
private:
	template <class T>
	static void helper(T * person, int field = 0);
public:
	template <class T>
	static bool del(T);
	template <class T>
	static void menu_edit(int & choice);
	template <class T>
	static T input(T * person = nullptr, int field = 0);
	template <class T>
	static void writeFile(T & person);
	static Doctor outputDoctors(list<Doctor> doctors);
	static pair<int, Patient> outputPatients(map<int, Patient> patients);
	static void sort(list<Doctor> & doctors);
	static void search(map<int, Patient> & patients);
};


inline void Helper::sort(list<Doctor> & doctors) {
	list<Doctor>::iterator i, j, temp;
	auto begin = doctors.begin(), end = doctors.end();
	char tempI[20], tempJ[20];
	if (begin != end) {
		for (i = begin; i != end; i++) {
			strcpy_s(tempI, 20, i->getName());
			temp = i;
			for (j = i; j != end; j++) {
				strcpy_s(tempJ, 20, j->getName());
				if (strcmp(tempI, tempJ) > 0) {
					strcpy_s(tempI, 20, tempJ);
					temp = j;
				}
			}
			iter_swap(i, temp);
		}
	}
}

inline void Helper::search(map<int, Patient> & patients) {
	cout << "Введите нужную фамилию" << endl;
	string str;
	cin >> str;
	map<int, Patient> temp;
	for (auto & pat : patients) {
		if (pat.second.getSecName() == str)
			temp.insert({ pat.first, pat.second });
	}
	auto output = Helper::outputPatients(temp);
	if (output.second.getEmail()[0] != '\0')
		cout << output.second;
}


template<class T>
inline void Helper::writeFile(T & person)
{
	ofstream f;
	if (is_same<T, Doctor>::value) {
		f.open("Doctors.txt", ofstream::app);
	}
	else if (is_same<T, Patient>::value) {
		f.open("Users.txt", ofstream::app);
	}

	//cout << '\n' << E << " " << P << " " << Tel << " " << N << " " << SN << " " << Pat << " " << Addr << " " << atoi(num.c_str()) << " " << atoi(korp.c_str()) << " " << atoi(kv.c_str()) << endl;
	if (f.is_open()) {
		f.write((char*)&person, sizeof(T));
		f.close();
	}
}


template<>
inline Doctor Helper::input<Doctor>(Doctor * person, int field) {
	Doctor doc;
	if (person != nullptr)
		doc = *person;
	if (field != 0) {
		Helper::del<Doctor>(doc);
	}
	Helper::helper(&doc, field);
	if (doc.getEmail() != "\0") {
		string str;
		if (field == 0 || field == 11) {
			cout << "\nВведите описание" << endl;
			cin >> str;
			doc.setDescription(str);
		}
		Helper::writeFile<Doctor>(doc);
	}
	return doc;
}

template<>
inline Patient Helper::input<Patient>(Patient * person, int field) {
	Patient pat;
	if (person != nullptr)
		pat = *person; 
	if (field != 0) {
		Helper::del<Patient>(pat);
	}
	Helper::helper(&pat, field);
	if (pat.getEmail() != "\0") {
		string str;
		if (field == 0 || field == 11) {
			cout << "\nВведите болезнь" << endl;
			cin >> str;
			pat.setIssue(str);
		}
		if (field == 0 || field == 12) {
			cout << "\nВведите текущее состояние" << endl;
			cin >> str;
			pat.setCurrentState(str);
		}
		Helper::writeFile<Patient>(pat);
	}
	return pat;
}

template<class T>
inline void Helper::helper(T * per, int field)
{
	string output;
	char ch = 0, E[50], P[50], Tel[20], N[20], SN[20], Pat[20], Addr[50];
	string mask = "@mail.ru";
	string mask_t = "+375(**)***-**-**";
	string email;
	string password;
	string Name;
	string SecName;
	string Patronumic;
	string addr;
	string num;
	string korp = "0";
	string kv;
	strcpy_s(E, 50, per->getEmail());
	strcpy_s(P, 50, per->getPassword());
	strcpy_s(N, 20, per->getName());
	strcpy_s(SN, 20, per->getSecName());
	strcpy_s(Pat, 20, per->getPatronymic());
	strcpy_s(Tel, 20, per->getTel());
	strcpy_s(Addr, 50, per->getAddr().addr);
	num = to_string(per->getAddr().num);
	korp = to_string(per->getAddr().korpus);
	kv = to_string(per->getAddr().kv);
	bool dot = false, flag = true;
	ifstream f1;
	int format = 0, i = 0, format_pos = 50;
	switch (field) {
	case 0:
	case 1: {
		output += "Введите Email";
		system("cls");
		cout << output;
		while (email.empty()) {
			ch = 0;
			while (ch != 13) {
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)i, 1 });
				ch = _getch();
				if (ch == '\b' && !email.empty()) {
					if (format == 1)
						format = 0;
					else if (format == 1) {
						if (email[email.length() - 1] == '@')
							format = 0;
					}
					else if (format == 2) {
						if (email[email.length() - 2] == '@')
							format = 1;
					}
					else if (format == 3) {
						if (email[email.length() - 1] == '.') {
							dot = false;
							format = 2;
						}
					}
					i--;
					email.pop_back();
				}
				if ((ch >= 'A' && ch <= 'Z') || (ch == '_') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) {
					email += ch;
					i++;
				}
				else if (ch == '@') {
					email += ch;
					i++;
					format = 1;
					format_pos = i;
				}
				if (i > format_pos) {
					if (format != 3 && format != 2)
						format = 2;
					if (ch == '.') {
						if (dot == false) {
							format = 3;
							email += ch;
							i++;
							dot = true;
						}
						else
							continue;
					}
				}
				system("cls");
				cout << output << endl;
				cout << email;
				if (format == 0)
					cout << mask;
				if (format == 1)
					cout << "mail.ru";
				if (format == 2)
					cout << ".ru";
			}
		}
		if (format == 0) {
			email.append("@mail.ru");
		}
		else if (format == 1) {
			email.append("mail.ru");
		}
		else if (format == 2) {
			email.append(".ru");
		}
		output += '\n';
		output += email;
		output += '\n';
		Patient pat;
		Doctor doc;
		f1.open("Users.txt");
		while (f1.peek() != EOF) {
			f1.read((char*)&pat, sizeof(Patient));
			if (!strcmp(pat.getEmail(), email.c_str())) {
				flag = false;
			}
		}
		f1.close();
		f1.open("Doctors.txt");
		while (f1.peek() != EOF) {
			f1.read((char*)&doc, sizeof(Doctor));
			if (!strcmp(doc.getEmail(), email.c_str())) {
				flag = false;
			}
		}
		f1.close();
		if (flag == false) {
			cout << "Такой пользователь уже существует" << endl;
			system("pause");
			return;
		}
		//if (!doctor_email.empty()) {
		//	class Console cons;
		//	system("cls");
		//	int choice = 2;
		//	do {
		//		if (admin == false) {
		//			choice = cons.Set_menu("  Хотите стать лечащим врачом для данного пациента?\n  Да\n  Нет");
		//			if (choice == 2)
		//				change_doc = true;
		//			else if (choice == 3)
		//				change_doc = false;
		//		}
		//		else
		//			change_doc = true;
		//	} while (choice == 1);
		//	if (flag == false)
		//		break;
		//}
		//else {
		//	if (flag == false) {
		//		cout << "\nТакой пользователь уже существует" << endl;
		//		system("pause");
		//		break;
		//	}
		//}
		if (field != 0) {
			strcpy_s(E, 50, email.c_str());
			break;
		}
		strcpy_s(E, 50, email.c_str());
	}
	case 2:
		output += "Введите пароль";
		system("cls");
		cout << output << endl;
		output += '\n';
		ch = 0;
		while (ch != 13) {
			ch = _getch();
			if (ch == '\b' && !password.empty()) {
				password.pop_back();
				system("cls");
				output.pop_back();
				cout << output;
			}
			if (ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z' || ch == '_' || ch >= '0' && ch <= '9') {
				password += ch;
				cout << ch;
				output += ch;
			}
		}
		system("cls");
		cout << output << endl;
		strcpy_s(P, 50, password.c_str());
		if (field != 0) {
			break;
		}
		output += '\n';
	case 3:
	{
		output += "Введите имя(на русском)";
		system("cls");
		cout << output << endl;
		output += '\n';
		ch = 0;
		while (ch != 13) {
			ch = _getch();
			if (ch == '\b' && !Name.empty()) {
				Name.pop_back();
				system("cls");
				output.pop_back();
				cout << output;
			}
			if (ch >= 'А' && ch <= 'Я') {
				ch += 32;
				Name += ch;
				output += ch;
				cout << ch;
			}
			else if (ch >= 'а' && ch <= 'я') {
				Name += ch;
				output += ch;
				cout << ch;
			}
		}
		system("cls");
		cout << output << endl;
	}
	strcpy_s(N, 20, Name.c_str());
	if (field != 0) {
		break;
	}
	output += '\n';
	case 4:
	{
		output += "Введите фамилию";
		system("cls");
		cout << output << endl;
		output += '\n';
		ch = 0;
		while (ch != 13) {
			ch = _getch();
			if (ch == '\b' && !SecName.empty()) {
				SecName.pop_back();
				system("cls");
				output.pop_back();
				cout << output;
			}
			if (ch >= 'А' && ch <= 'Я') {
				ch += 32;
				SecName += ch;
				output += ch;
				cout << ch;
			}
			else if (ch >= 'а' && ch <= 'я') {
				SecName += ch;
				output += ch;
				cout << ch;
			}
		}
		system("cls");
		cout << output << endl;
		strcpy_s(SN, 20, SecName.c_str());
		if (field != 0) {
			break;
		}
		output += '\n';
	}
	case 5:
	{
		output += "Введите отчество";
		system("cls");
		cout << output << endl;
		output += '\n';
		ch = 0;
		while (ch != 13) {
			ch = _getch();
			if (ch == '\b' && !Patronumic.empty()) {
				Patronumic.pop_back();
				system("cls");
				output.pop_back();
				cout << output;
			}
			if (ch >= 'А' && ch <= 'Я') {
				ch += 32;
				Patronumic += ch;
				output += ch;
				cout << ch;
			}
			else if (ch >= 'а' && ch <= 'я') {
				Patronumic += ch;
				output += ch;
				cout << ch;
			}
		}
		system("cls");
		cout << output << endl;
		strcpy_s(Pat, 20, Patronumic.c_str());
		if (field != 0) {
			break;
		}
		output += '\n';
	}
	case 6:
	{
		output += "Введите свой мобильный телефон";
		system("cls");
		cout << output << endl;
		int length = 0;
		int pospos = 0;
		int posarrays[10] = { 5,6,8,9,10,12,13,15,16 };
		int pos = posarrays[pospos];
		cout << mask_t;
		ch = 0;
		while (length != 9 && ch != 13) {
			ch = _getch();
			if (ch == '\b' && length != 0) {
				length--;
				pospos--;
				pos = posarrays[pospos];
				mask_t[pos] = '*';
				system("cls");
				cout << output << endl;
				cout << mask_t;
			}
			if (ch >= '0' && ch <= '9') {
				length++;
				mask_t[pos] = ch;
				pospos++;
				pos = posarrays[pospos];
				system("cls");
				cout << output << endl;
				cout << mask_t;
			}
		}
		strcpy_s(Tel, 20, mask_t.c_str());
		if (field != 0) {
			break;
		}
		output += '\n';
		output += mask_t;
		output += '\n';
	}
	case 7:
	{
		short int pos = 0;
		vector<string> vect = { "улица", "проспект", "переулок", "тракт", "проезд" };
		string temp_str = vect[0];
		output += "Введите адрес(Например: улица Космонавтов)";
		system("cls");
		cout << output << endl;
		output += '\n';
		cout << temp_str << " ";
		ch = 0;
		while (ch != 13) {
			ch = _getch();
			if (ch == -32) {
				ch = _getch();
				if (ch == 75) {
					pos--;
					if (pos < 0)
						pos = (short)vect.size() - 1;
					temp_str = vect[pos];
					system("cls");
					cout << output;
					cout << temp_str;
					cout << " " << addr;
				}
				else if (ch == 77) {
					pos++;
					if (pos > (short)vect.size() - 1)
						pos = 0;
					temp_str = vect[pos];
					system("cls");
					cout << output;
					cout << temp_str;
					cout << " " << addr;
				}
				else if (ch == '\0')
					ch = 'а';
			}
			if (ch == '\b' && !addr.empty()) {
				addr.pop_back();
				system("cls");
				cout << output;
				cout << temp_str << " " << addr;
			}
			if (ch >= 'А' && ch <= 'Я') {
				ch += 32;
				addr += ch;
				cout << ch;
			}
			else if (ch >= 'а' && ch <= 'я') {
				addr += ch;
				cout << ch;
			}
		}
		temp_str += " ";
		temp_str += addr;
		strcpy_s(Addr, 50, temp_str.c_str());
		if (field != 0) {
			break;
		}
		output += temp_str;
		output += '\n';
	}
	case 8:
		output += "Введите номер дома";
		system("cls");
		cout << output << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		num.clear();
		while (num.length() == 0) {
			ch = 0;
			while (ch != 13) {
				ch = _getch();
				if (ch == '\b' && num.length() != 0) {
					num.pop_back();
					system("cls");
					cout << output << endl;
					cout << num;
				}
				if (ch >= '0' && ch <= '9' && num.length() <= 2) {
					num += ch;
					cout << ch;
				}
			}
		}
		if (field != 0) {
			break;
		}
	case 9:
		output += '\n';
		output += num;
		output += '\n';
		output += "Введите номер корпуса(оставьте пустым, если корпуса нет)";
		system("cls");
		cout << output << endl;
		ch = 0;
		while (ch != 13) {
			ch = _getch();
			if (ch == '\b' && korp.length() != 1) {
				korp.pop_back();
				system("cls");
				cout << output << endl;
				for (int i = 1; i < (int)korp.length(); i++)
					cout << korp[i];
			}
			if (ch >= '0' && ch <= '9' && korp.length() <= 2) {
				korp += ch;
				cout << ch;
			}
		}
		if (field != 0) {
			break;
		}
	case 10:
		output += '\n';
		if (korp != "0")
			output += korp;
		output += '\n';
		output += "Введите номер квартиры";
		system("cls");
		cout << output << endl;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		kv.clear();
		while (kv.length() == 0) {
			ch = 0;
			while (ch != 13) {
				ch = _getch();
				if (ch == '\b' && kv.length() != 0) {
					kv.pop_back();
					system("cls");
					cout << output << endl;
					cout << kv;
				}
				if (ch >= '0' && ch <= '9' && kv.length() <= 2) {
					kv += ch;
					cout << ch;
				}
			}
		}
		if (field != 0) {
			break;
		}
	default:
		break;
	}

	per->setValues(*E, *P, *Tel, *N, *SN, *Pat, *Addr, atoi(num.c_str()), atoi(korp.c_str()), atoi(kv.c_str()));
}

template <class T>
inline bool Helper::del(T ob)
{
	string file = "Users.txt";
	fstream f;
	if (is_same<T, Doctor>::value) {
		file = "Doctors.txt";
	}
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
	int user = true;
	cout << "1. Email" << endl;
	cout << "2. Пароль" << endl;
	cout << "3. Имя" << endl;
	cout << "4. Фамилия" << endl;
	cout << "5. Отчество" << endl;
	cout << "6. Мобильный телефон" << endl;
	cout << "7. Адрес" << endl;
	cout << "8. Номер дома" << endl;
	cout << "9. Номер корпуса" << endl;
	cout << "10. Номер квартиры" << endl;
	if (is_same<T, Doctor>::value) {
		cout << "11. Описание" << endl;
		cout << "12. Выход" << endl;
		user = false;
	}
	else {
		cout << "11. Болезнь" << endl;
		cout << "12. Текущее состояние" << endl;
		cout << "13. Выход" << endl;
	}	
	do {
		cin >> choice;
	} while (!cin.good() && (choice < 1 || choice > user ? 13 : 12));
}