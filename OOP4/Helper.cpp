#include "Helper.h"


Doctor Helper::outputDoctors(list<Doctor> doctors)
{
	int temp, i = 1;
	if (doctors.empty()) {
		cout << "Нет пациентов" << endl;
		return Doctor();
	}
	for (auto & person : doctors) {
		cout << i << ". " << person.getName() << " " << person.getSecName() << endl;
		i++;
	}
	do {
		cin >> temp;
	} while (!cin.good() || temp < 1 || temp >(int)doctors.size());
	return *std::next(doctors.begin(), temp - 1);
}


pair<int, Patient> Helper::outputPatients(map<int, Patient> patients)
{
	int temp, i = 1;
	if (patients.empty()) {
		cout << "Нет пациентов" << endl;
		Patient temp_pat;
		return { 0, temp_pat };
	}
	for (auto & person : patients) {
		cout << i << ". " << person.second.getName() << " " << person.second.getSecName() << endl;
		i++;
	}
	do {
		cin >> temp;
	} while (!cin.good() || temp < 1 || temp >(int)patients.size());
	return (*std::next(patients.begin(), temp - 1));
}