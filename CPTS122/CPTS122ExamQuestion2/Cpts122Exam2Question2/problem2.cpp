/*
	NAME: Killian Griffin
	DATE: 4/4/20
	LAB SECTION: 5
	ASSIGNMENT: Exam 2 programming question 2
	DESCRIPTION: This program alllows the user to enter an ammount of months and the ammount of rainfall during each month. The program
				 stores this data in a linked list, then calculates the total ammount of rainfall, the average ammount of rainfall over the
				 months, the month with the highest ammount of rainfall, and the month with the lowest ammount of rainfall.
*/

#include "header.h"

int createNode(RainfallNode** pHead, int monthNum, double rainfall)
{
	RainfallNode* newNode = new RainfallNode;
	if (*pHead == nullptr)
	{
		newNode->month = monthNum;
		newNode->rain = rainfall;
		newNode->next = NULL;
		*pHead = newNode;
		return 0;
	}
	newNode->next = *pHead;
	*pHead = newNode;
	newNode->month = monthNum;
	newNode->rain = rainfall;

	return 1;
}

double totalRainfall(RainfallNode* pHead)
{
	double total = 0;
	while (pHead != nullptr)
	{
		total = total + pHead->rain;
		pHead = pHead->next;
	}
	return total;
}

double avgRainfall(RainfallNode* pHead)
{
	int monthNum = 0, total = totalRainfall(pHead);
	while (pHead != nullptr)
	{
		++monthNum;
		pHead = pHead->next;
	}

	return total / monthNum;
}

int maxRainfall(RainfallNode* pHead)
{
	int monthMax = pHead->month, rainMax = pHead->rain;
	while (pHead != nullptr)
	{
		if (pHead->rain > rainMax)
		{
			rainMax = pHead->rain;
			monthMax = pHead->month;
		}
		pHead = pHead->next;
	}
	return monthMax;
}

int minRainfall(RainfallNode* pHead)
{
	int monthMin = pHead->month, rainMin = pHead->rain;
	while (pHead != nullptr)
	{
		if (pHead->rain < rainMin)
		{
			rainMin = pHead->rain;
			monthMin = pHead->month;
		}
		pHead = pHead->next;
	}
	return monthMin;
}