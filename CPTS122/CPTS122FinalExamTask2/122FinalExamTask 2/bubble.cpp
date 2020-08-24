/*
	NAME: Killian Griffin
	DATE: 5/3/20
	LAB SECTION: 5
	DESCRIPTION: This program sorts arrays of various data types in descending order using the bubble sort method.
*/

#include <iostream>

using namespace std;

template <class T>

bool bubbleSort(T arr[], int size)
{
	bool isSwapped = true;
	T temp;
	while (isSwapped)
	{
		isSwapped = false;
		for (int index = 0; index < size - 1; ++index)
		{
			if (arr[index] < arr[index + 1])
			{
				temp = arr[index];
				arr[index] = arr[index + 1];
				arr[index + 1] = temp;
				isSwapped = true;
			}
		}
	}
	return true;
}