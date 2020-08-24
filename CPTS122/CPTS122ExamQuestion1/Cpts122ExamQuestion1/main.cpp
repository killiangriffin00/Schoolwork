/*
	NAME: Killian Griffin
	DATE: 4/4/20
	LAB SECTION: 5
	ASSIGNMENT: Exam 2 programming question 1
	DESCRIPTION: This program contains a class with an array of floating point numbers and functions for each operation: storing values
				 in the array, retrieving numbers from the array, returning the highest value in the array, returning the lowest value
				 in the array, and returning the average of all of the values in the array.
*/

#include "header.h"

int main()
{
	int option = 0, size = 0;
	double newValue = 0;

	cout << "How large do you want the array to be?\n";
	cin >> size;

	system("cls");
	while (size < 1)
	{
		cout << "How large do you want the array to be?\n";
		cin >> size;

		system("cls");
	}
	Storage store(size);

	for (int index = 0; index <= size; ++index)
	{
		cout << "Enter a value for position " << index << " in the array:\n";
		cin >> newValue;
		store.setNum(newValue, index);
		system("cls");
	}

	cout << "ARRAY: [";

	for (int index = 0; index <= size; ++index)
	{
		cout << " " << store.getNum(index) << " ";
	}

	cout << "]\nHIGHEST VALUE: " << store.getHighest() << endl << "LOWEST VALUE: " << store.getLowest() << endl << "AVERAGE OF VALUES: " <<
		store.getAverage();

	return 0;
}