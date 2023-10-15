/*
*Author: Luis E. Ortiz
*Creation Date: 10/09/2018
*Modification Date: 10/14/2018
*Purpose: testing AVLTreeMap class template
*/

//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <string>

#include "stdafx.h"
#include "Entry.h"
#include "AVLTreeMap.h"


using namespace std;

void test_map_find(AVLTreeMap< Entry<int, int> >& T, int k);

int main() {
	AVLTreeMap< Entry<int, int> > T;

	T.put(44, 0);
	T.put(17, 1);
	T.put(78, 2);
	T.put(32, 3);
	T.put(50, 4);
	T.put(88, 5);
	T.put(48, 6);
	T.put(62, 7);

	cout << "Initial AVL Tree:" << endl;

	T.print();

	cout << "Testing double rotation (left,right) after inserting (54,8):" << endl;

	T.put(54, 8);

	T.print();

	cout << "Testing single rotation (right,right) after deleting key 32:" << endl;

	T.erase(32);

	T.print();

	cout << "Testing insertion as left child after inserting (70,9):" << endl;

	T.put(70, 9);

	T.print();

	cout << "Testing deletion of key at root (non-leaf node) after deleting key 62:" << endl;

	T.erase(62);

	T.print();

	test_map_find(T, 50);
	test_map_find(T, 70);
	test_map_find(T, 54);
	test_map_find(T, 55);
	test_map_find(T, 90);
	test_map_find(T, 72);

	cout << "Testing double rotation (right,left) after inserting (80,10):" << endl;

	T.put(80, 10);

	cout << "Testing single rotation (left,left) after inserting (75,11) & (72,12):" << endl;

	T.put(75, 11);
	T.put(72, 12);

	T.print();

	//system("pause");
	return EXIT_SUCCESS;
}

void test_map_find(AVLTreeMap< Entry<int, int> >& T, int k) {

	AVLTreeMap< Entry<int, int> >::Iterator w = T.find(k);

	if (w == T.end()) cout << "No map value found for key " << k << endl;
	else cout << "Map value of key " << (*w).key() << ": " << (*w).value() << endl;
}
