/*
	NAME: Killian Griffin
	DATE: 5/3/20
	LAB SECTION: 5
	DESCRIPTION: This program reads characters from a text file into a stack and outputs them into another text file in reverse order.
*/

#include "header.h"

Stack::Stack(Stack** head)
{
	c = '\0';
	next = *head;
	*head = this;
}

char Stack::getC()
{
	return c;
}

bool Stack::setC(char newC)
{
	c = newC;
	return true;
}

Stack* Stack::pop()
{
	Stack* temp = next;
	if (next != nullptr)
	{
		next = next->next;
	}
	return temp;
}

bool Stack::pull(ifstream* file, Stack** head)
{
	Stack* newNode = new Stack(head);
	char temp;
	*file >> temp;
	newNode->setC(temp);
	return true;
}

bool Stack::print(ofstream* file, Stack** head)
{
	while ((*head)->next != nullptr)
	{
		*file << (*head)->pop()->getC();
	}
	return true;
}

