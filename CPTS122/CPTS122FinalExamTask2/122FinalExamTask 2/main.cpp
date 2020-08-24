/*
	NAME: Killian Griffin
	DATE: 5/3/20
	LAB SECTION: 5
	DESCRIPTION: This program sorts arrays of various data types in descending order using the bubble sort method.
*/

#include "bubble.cpp"

int main()
{
	int intarray[5] = { 2, 1, 8, -3, 10 };
	double doublearray[6] = { 5.6, 9.4, 1.2, 3.3, 8.7, 1.1 };
	char chararray[4] = { 'T', 'A', '!', 'b' };

	bubbleSort(intarray, 5);
	bubbleSort(doublearray, 6);
	bubbleSort(chararray, 4);

	for (int index = 0; index < 5; ++index)
	{
		cout << intarray[index] << ' ';
	}
	cout << endl;
	for (int index = 0; index < 6; ++index)
	{
		cout << doublearray[index] << ' ';
	}
	cout << endl;
	for (int index = 0; index < 4; ++index)
	{
		cout << chararray[index] << ' ';
	}
	cout << endl;
	return 0;
}

