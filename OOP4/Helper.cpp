#include "Helper.h"


Good Helper::outputDoctors(my_priority_queue<Good> goods)
{
	int temp, i = 1;
	if (goods.empty()) {
		cout << "Нет товаров" << endl;
		return Good();
	}
	for (auto & doctor : goods) {
		cout << i << ". " << doctor.getName() << endl;
		i++;
	}
	do {
		cin >> temp;
	} while (!cin.good() || temp < 1 || temp >(int)goods.size());
	return *std::next(goods.begin(), temp - 1);
}
