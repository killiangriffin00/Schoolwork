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

int main()
{
	RainfallNode** pHead = new RainfallNode*;
	int months = 0, rain = 0;
	*pHead = nullptr;
	cout << "Enter the ammount of months: \n";
	cin >> months;
	system("cls");

	while (months < 1)
	{
		cout << "Enter the ammount of months: \n";
		cin >> months;
		system("cls");
	}

	for (int index = 0; index < months; ++index)
	{
		cout << "Enter the ammount of rainfall for month " << index + 1 << ":\n";
		cin >> rain;
		system("cls");
		while (rain < 0)
		{
			cout << "Enter the ammount of rainfall for month " << index + 1 << ":\n";
			cin >> rain;
			system("cls");
		}

		createNode(pHead, index + 1, rain);
	}

	cout << "TOTAL RAINFALL: " << totalRainfall(*pHead) << endl << "AVERAGE RAINFALL: " << avgRainfall(*pHead) << endl << 
		"MONTH WITH MOST RAIN: " << maxRainfall(*pHead) << endl << "MONTH WITH LEAST RAIN: " << minRainfall(*pHead);


	return 0;
}