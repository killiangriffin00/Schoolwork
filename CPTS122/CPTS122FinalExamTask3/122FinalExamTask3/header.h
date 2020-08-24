/*
	NAME: Killian Griffin
	DATE: 5/3/20
	LAB SECTION: 5
	DESCRIPTION: This program uses classes to display the number of sick leave and vacation days an employee has.
*/

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>

using namespace std;

class NumDays
{
private:
	double hours;

public:
	NumDays() {}
	NumDays(int numHours);
	double getHours();
	bool setHours(int newHours);
	double days();
	friend double operator+(NumDays &left, NumDays &right);
	friend double operator-(NumDays& left, NumDays& right);
};

class TimeOff
{
private:
	string name;
	int id;
	NumDays maxSickDays;
	NumDays sickTaken;
	NumDays maxVacation;
	NumDays vacTaken;
	NumDays unpaidTaken;

public:
	TimeOff() {}
	string getName();
	bool setName(string newName);
	int getID();
	bool setID(int newID);
	NumDays getMaxSickDays();
	bool setMaxSickDays(double newMax);
	NumDays getSickTaken();
	bool setSickTaken(double newSick);
	NumDays getMaxVacation();
	bool setMaxVacation(double newMax);
	NumDays getVacTaken();
	bool setVacTaken(double newVac);
	NumDays getUnpaid();
	bool setUnpaid(double newUnpaid);
};


#endif