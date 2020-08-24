/*
	NAME: Killian Griffin
	DATE: 5/3/20
	LAB SECTION: 5
	DESCRIPTION: This program uses classes to display the number of sick leave and vacation days an employee has.
*/

#include "header.h"

NumDays::NumDays(int numHours)
{
	setHours(numHours);
}


double NumDays::getHours()
{
	return hours;
}

bool NumDays::setHours(int newHours)
{
	hours = newHours;
	return true;
}

double NumDays::days()
{
	return hours / 8;
}

double operator+(NumDays& left, NumDays& right)
{
	return left.getHours() + right.getHours();
}


double operator-(NumDays& left, NumDays& right)
{
	return left.getHours() - right.getHours();
}


string TimeOff::getName()
{
	return name;
}

bool TimeOff::setName(string newName)
{
	name = newName;
	return true;
}

int TimeOff::getID()
{
	return id;
}

bool TimeOff::setID(int newID)
{
	id = newID;
	return true;
}

NumDays TimeOff::getMaxSickDays()
{
	return maxSickDays;
}

bool TimeOff::setMaxSickDays(double newMax)
{
	maxSickDays.setHours(newMax);
	return true;
}

NumDays TimeOff::getSickTaken()
{
	return sickTaken;
}

bool TimeOff::setSickTaken(double newSick)
{
	sickTaken.setHours(newSick);
	return true;
}

NumDays TimeOff::getMaxVacation()
{
	return maxVacation;
}

bool TimeOff::setMaxVacation(double newMax)
{
	if (newMax <= 240)
	{
		maxVacation.setHours(newMax);
	}
	return true;
}

NumDays TimeOff::getVacTaken()
{
	return vacTaken;
}

bool TimeOff::setVacTaken(double newVac)
{
	vacTaken.setHours(newVac);
	return true;
}

NumDays TimeOff::getUnpaid()
{
	return unpaidTaken;
}

bool TimeOff::setUnpaid(double newUnpaid)
{
	unpaidTaken.setHours(newUnpaid);
	return true;
}