/*
	NAME: Killian Griffin
	DATE: 4/4/20
	LAB SECTION: 5
	ASSIGNMENT: Exam 2 programming question 3
	DESCRIPTION: This program reads in a text document and outputs the amount of actual letters in the document.
*/

#include "header.h"

int createQueueNode(QueueNode** pHead, char data)
{
	QueueNode* newNode = new QueueNode;

	if (*pHead == nullptr)
	{
		newNode->letter = data;
		newNode->next = NULL;
		*pHead = newNode;
		return 0;
	}
	QueueNode* temp;

	temp = *pHead;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	newNode->letter = data;
	newNode->next = NULL;
	temp->next = newNode;
	return 1;
}

int letterCount(QueueNode* pHead)
{
	int result = 0;
	while (pHead->next != NULL)
	{
		if ((pHead->letter > 64 && pHead->letter < 91) || (pHead->letter > 96 && pHead->letter < 123))
		{
			++result;
		}
		pHead = pHead->next;
	}
	return result;
}
