/*
	NAME: Killian Griffin
	DATE: 5/3/20
	LAB SECTION: 5
	DESCRIPTION: This program uses classes to display the number of sick leave and vacation days an employee has.
*/

#include "header.h"

int main()
{
	TimeOff employee;
	string stemp;
	int itemp;
	double dtemp;

	cout << "Enter employee name: ";
	cin >> stemp;
	system("cls");
	cout << "Enter employee ID number: ";
	cin >> itemp;
	system("cls");
	cout << "Enter the months worked: ";
	cin >> dtemp;

	employee.setName(stemp);
	employee.setID(itemp);

	employee.setMaxVacation(12 * dtemp);
	employee.setMaxSickDays(8 * dtemp);

	cout << "VACATION HOURS: " << employee.getMaxVacation().getHours() << endl << "SICK HOURS: " << employee.getMaxSickDays().getHours();
}