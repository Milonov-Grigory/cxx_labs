
#include "stdafx.h"
#include <iostream>


using namespace std;

class test {
private:
	int a;
public:
	test() {
		a = 0;
		cout << a << " - тут сработал конструктор и вывел значение а";
	}
	void settest() {
		cin >> a;
	}
	void gettest() {
		cout << a;
	}
	~test() {
		cout << "Сработал деструктор";
	}

};

int main() {
	setlocale(LC_ALL, "rus");
	test test1;
	static test test2;
	test *test3 = new test;

	test1.settest();
	test1.gettest();
	test2.settest();
	test2.gettest();
	test3->settest();
	test3->gettest();
	delete test3;
	return 0;
}