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

Storage::Storage(int size)
{
	arrayPtr = new double[size];
	arraySize = size;
}

int Storage::setNum(double newNum, int position)
{
	if (position <= arraySize)
	{
		arrayPtr[position] = newNum;
		return 1;
	}
	return 0;
}

double Storage::getNum(int position)
{
	if (position <= arraySize)
	{
		return arrayPtr[position];
	}
	return 0;
}

double Storage::getHighest()
{
	double highest = arrayPtr[0];

	for (int index = 0; index <= arraySize; ++index)
	{
		if (highest < arrayPtr[index])
		{
			highest = arrayPtr[index];
		}
	}
	return highest;
}

double Storage::getLowest()
{
	double lowest = arrayPtr[0];

	for (int index = 0; index <= arraySize; ++index)
	{
		if (lowest > arrayPtr[index])
		{
			lowest = arrayPtr[index];
		}
	}
	return lowest;
}

double Storage::getAverage()
{
	double sum = 0;
	for (int index = 0; index <= arraySize; ++index)
	{
		sum = sum + arrayPtr[index];
	}
	return sum / (arraySize + 1);
}