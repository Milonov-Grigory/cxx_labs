#include "stdafx.h"
#include "header.h"

#include <iostream>

int main() {
	List<int> list;
	list.append(14);
	list.append(77);
	list.append(404);
	list.show();
	list.append(2, 1);
	list.show();
	list.remove(3);
	list.show();
	list.removeHead();
	list.show();
	List<int> copy(list);
	cout << "COPIED:" << endl;
	copy.show();

	return 0;
}