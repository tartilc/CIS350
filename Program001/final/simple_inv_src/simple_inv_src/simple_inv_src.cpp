/*
*Author: Tartil Chowdhury
*Creation Date: 10/23/2018
*Modification Date: 10/26/2018
*Purpose: simple inventory management using provided avl tree source
*/

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <vector>
#include "Entry.h"
#include "AVLTreeMap.h"

using namespace std;

class ADT {
private:
	AVLTreeMap< Entry<int, int> > map;

	int n;
	int count;
	int temp;
	int totalProducts;

public:
	ADT()
	{
		n = 0;
		temp = 0;
		count = 0;
		totalProducts = 0;
	}

	int num_products()
	{
		n = map.size();
		return n;
	}

	int available(ofstream& error, int product_id)
	{
		AVLTreeMap< Entry<int, int> >::Iterator w = map.find(product_id);

		if (w == map.end()) {
			cout << "Product " << product_id << " not found." << endl;
			error << "Product " << product_id << " not found." << endl;
		}
		else {
			product_id = (*w).key();
			count = (*w).value();
		}

		return count;
	}

	int size()
	{
		totalProducts = 0;

		AVLTreeMap< Entry<int, int> >::Iterator w = map.begin();

		while (w != map.end())
		{
			totalProducts += (*w).value();
			w.operator++();
		}
		return totalProducts;
	}

	void in(int product_id, int numItems)
	{
		AVLTreeMap< Entry<int, int> >::Iterator w = map.find(product_id);
		if (w == map.end())
		{
			map.put(product_id, numItems);
		}
		else {
			count = (*w).value();
			count += numItems;
			(*w).setValue(count);
		}
		count = 0;
	}

	void out(ofstream& output, int product_id, int numItems)
	{
		AVLTreeMap< Entry<int, int> >::Iterator w = map.find(product_id);
		if (w == map.end())
		{
			cout << "Cannot delete " << product_id << ", product not found" << endl;
			output << "Cannot delete " << product_id << ", product not found" << endl;
		}
		else {
			count = (*w).value();
			temp = count - numItems;
			if (temp < 0)
			{
				cout << "error: Insufficient inventory: Product ID " << product_id <<
					", " << numItems << " requested, " << count << " available" << endl;

				output << "error: Insufficient inventory: Product ID " << product_id <<
					", " << numItems << " requested, " << count << " available";
			}
			else {
				(*w).setValue(temp);

				if ((*w).value() == 0)
				{
					int deleteKey = 0;
					deleteKey = (*w).key();
					map.erase(deleteKey);
				}
			}
		}
		count = 0;
	}

	void print_product(ofstream& output, int product_id)
	{
		AVLTreeMap< Entry<int, int> >::Iterator w = map.find(product_id);

		if (w == map.end())
		{
			cout << endl << "error: product " << product_id << " not found";
			output << endl << "error: product " << product_id << " not found";
		}
		else {
			count = (*w).value();
			cout << endl << product_id << " " << count << endl;
			output << endl << product_id << " " << count << endl;
		}
	}

	void print(ofstream& output)
	{
		AVLTreeMap< Entry<int, int> >::Iterator w = map.begin();
		int totalInv = 0;

		cout << endl;

		while (w != map.end())
		{
			cout << (*w).key() << " " << (*w).value() << endl;
			output << (*w).key() << " " << (*w).value() << endl;
			w.operator++();
		}

		totalInv = size();
		cout << "Inventory size: " << totalInv << endl;
		output << "Inventory size: " << totalInv << endl;
	}

	void save(string inventory)
	{
		ofstream out;
		out.open(inventory);

		AVLTreeMap< Entry<int, int> >::Iterator w = map.begin();

		while (w != map.end())
		{
			out << (*w).key() << " " << (*w).value() << endl;
			w.operator++();
		}

		out.close();
	}

	void open(string inventory)
	{
		ifstream inv;
		int tempID = 0;
		int tempCount = 0;

		inv.open(inventory);

		if (!inv.is_open())
		{
			cout << "error: file " << inventory << ".txt not found." << endl;
			exit(1);
		}
		else {
			if (!map.empty()) {
				AVLTreeMap< Entry<int, int> > temp;
				map = temp;
				while (!inv.eof())
				{
					inv >> tempID;
					inv >> tempCount;

					map.put(tempID, tempCount);
				}
			}
			else {
				while (!inv.eof())
				{
					inv >> tempID;
					inv >> tempCount;

					map.put(tempID, tempCount);
				}
			}

			inv.close();
		}
	}

	void process(ofstream& output, string transaction)
	{

		ifstream trans;

		int product_id = 0;
		int amount = 0;

		trans.open(transaction);

		if (!trans.is_open())
		{
			cout << "error: file " << transaction << ".txt not found" << endl;
			output << "error: file " << transaction << ".txt not found" << endl;
			exit(1);
		}
		else {
			while (!trans.eof())
			{
				string temp;
				int id = 0, num = 0;
				trans >> temp >> id;

				if (isdigit(trans.peek())) {
					trans >> num;
				}
				else {
					num = 1;
					trans >> num;
				}


				if (temp == "in") {
					in(id, num);
				}
				else {
					out(output, id, num);
				}
			}

			trans.close();
		}
	}
};

int main() {
	ADT t;

	string inputFileName, outputFileName;

	cin >> inputFileName >> outputFileName;

	ifstream input;
	input.open(inputFileName);

	ofstream output;
	output.open(outputFileName);

	if (input.is_open()) {

		while (!input.eof()) {
			string command, parameter;
			int temp = 0;
			input >> command;

			if (command == "open") {
				cout << "open" << endl;
				input >> parameter;
				t.open(parameter);
			}
			else if (command == "display") {
				getline(input, parameter);
				cout << "display";
				if (parameter == "") {
					if (t.size() == 0) {
						cout << "nothing to display!" << endl;
					}
					else {
						t.print(output);
					}
				}
				else {
					temp = stoi(parameter.substr(1, parameter.size() - 1));
					t.print_product(output, temp);
				}
			}
			else if (command == "process") {
				cout << "process" << endl;
				input >> parameter;
				t.process(output, parameter);
			}
			else if (command == "save") {
				input >> parameter;
				t.save(parameter);
			}
			else {
				cout << "Instruction not recognized!" << endl;
			}
		}
	}

	input.close();
	output.close();

	//system("pause");
	return 0;
}