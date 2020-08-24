/*
	NAME: Killian Griffin
	DATE: 4/4/20
	LAB SECTION: 5
	ASSIGNMENT: Exam 2 programming question 2
	DESCRIPTION: This program alllows the user to enter an ammount of months and the ammount of rainfall during each month. The program 
				 stores this data in a linked list, then calculates the total ammount of rainfall, the average ammount of rainfall over the 
				 months, the month with the highest ammount of rainfall, and the month with the lowest ammount of rainfall.
*/

#ifndef HEADER_H
#define HEADER_H

#include <iostream>

using namespace std;

struct RainfallNode
{
	int month;
	double rain;
	RainfallNode* next;
};

int createNode(RainfallNode** pHead, int monthNum, double rainfall);
double totalRainfall(RainfallNode* pHead);
double avgRainfall(RainfallNode* pHead);
int maxRainfall(RainfallNode* pHead);
int minRainfall(RainfallNode* pHead);

#endif