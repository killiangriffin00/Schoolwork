/*
	NAME: Killian Griffin
	DATE: 4/4/20
	LAB SECTION: 5
	ASSIGNMENT: Exam 2 programming question 3
	DESCRIPTION: This program reads in a text document and outputs the amount of actual letters in the document.
*/

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>

using namespace std;

struct QueueNode
{
	char letter;
	QueueNode* next;
};

int createQueueNode(QueueNode** pHead, char data);
int letterCount(QueueNode* pHead);


#endif