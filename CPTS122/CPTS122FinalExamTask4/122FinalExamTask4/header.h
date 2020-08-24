/*
	NAME: Killian Griffin
	DATE: 5/3/20
	LAB SECTION: 5
	DESCRIPTION: This program enqueues characters from a file, asks the user for a character to search for, then outputs the number of
				 the entered character to a file.
*/

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>

using namespace std;

class Queue
{
private:
	char c;
	Queue* next;

public:
	Queue();
	char getC();
	bool setC(char newC);
	Queue* dequeue(Queue** head);
	bool enqueue(ifstream* file, Queue** head);
};



#endif