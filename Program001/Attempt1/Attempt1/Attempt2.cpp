/*
*Author: Luis E. Ortiz
*Creation Date: 10/09/2018
*Modification Date: 10/14/2018
*Purpose: testing AVLTreeMap class template
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Entry.h"
#include "AVLTreeMap.h"
#include "AVLTree.h"

using namespace std;

int main() {
	AVLTreeMap< Entry<int, int> > T;
	ifstream readFile, readFile2, readFile3;
	readFile.open("input.txt");
	while (!readFile.eof()) {
		string command, parameter;
		readFile >> command;
		if (command == "open") {
			readFile >> parameter;
			readFile2.open(parameter);
		}
		else if (command == "display") {
			getline(readFile, parameter);
			if (parameter == "") {
				while (!readFile2.eof()) {
					string currLine;
					getline(readFile2, currLine);
					cout << currLine << endl;
				}
				readFile2.clear();
				readFile2.seekg(0, ios::beg);
			}
			else {
				while (!readFile2.eof()) {
					string productId, numItems;
					readFile2 >> productId >> numItems;
					if (productId == parameter.substr(1, parameter.size() - 1)) {
						cout << productId << " " << numItems << endl;
					}
				}
				readFile2.clear();
				readFile2.seekg(0, ios::beg);
			}
		}
		else if (command == "process") {
			readFile >> parameter;
			readFile3.open(parameter);

			while (!readFile3.eof())
			{
				string processor, key, quantity;
				readFile3 >> processor >> key;
				if (processor == "in") {
					readFile3 >> quantity;
					T.put(stoi(key), stoi(quantity));
				}
				else {
					getline(readFile3, quantity);
					if (quantity == "") {
						T.erase(stoi(key));
					}
					else {
						T.put(stoi(key), stoi(quantity.substr(1, quantity.size() - 1)));
					}
				}
			}
		}
	}

	readFile.close();


	system("pause");
	return EXIT_SUCCESS;
}