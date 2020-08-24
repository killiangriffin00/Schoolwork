/*
	NAME: Killian Griffin
	DATE: 5/3/20
	LAB SECTION: 5
	DESCRIPTION: This program enqueues characters from a file, asks the user for a character to search for, then outputs the number of
				 the entered character to a file.
*/

#include "header.h"

Queue::Queue()
{
	c = '\0';
	next = nullptr;
}

char Queue::getC()
{
	return c;
}

bool Queue::setC(char newC)
{
	c = newC;
	return true;
}

Queue* Queue::dequeue(Queue** head)
{
	Queue* temp = *head;
	*head = (*head)->next;
	return temp;
}

bool Queue::enqueue(ifstream* file, Queue** head)
{
	Queue* newQueue = new Queue;
	char newC;
	*file >> newC;
	newQueue->setC(newC);
	
	if (*head == nullptr)
	{
		*head = newQueue;
		return false;
	}

	Queue* temp = *head;

	while (temp->next != nullptr)
	{
		temp = temp->next;
	}
	temp->next = newQueue;
	return true;
}