/*
	NAME: Killian Griffin
	DATE: 4/4/20
	LAB SECTION: 5
	ASSIGNMENT: Exam 2 programming question 1
	DESCRIPTION: This program contains a class with an array of floating point numbers and functions for each operation: storing values
				 in the array, retrieving numbers from the array, returning the highest value in the array, returning the lowest value 
				 in the array, and returning the average of all of the values in the array.
*/

#ifndef HEADER_H
#define HEADER_H

#include <iostream>

using namespace std;

class Storage
{
private:
	double* arrayPtr;
	int arraySize;

public:
	Storage(int size);
	~Storage(){}
	int setNum(double newNum, int position);
	double getNum(int position);
	double getHighest();
	double getLowest();
	double getAverage();
};
#endif

