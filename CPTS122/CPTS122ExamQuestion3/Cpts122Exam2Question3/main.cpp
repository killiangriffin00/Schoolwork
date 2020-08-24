/*
	NAME: Killian Griffin
	DATE: 4/4/20
	LAB SECTION: 5
	ASSIGNMENT: Exam 2 programming question 3
	DESCRIPTION: This program reads in a text document and outputs the amount of actual letters in the document.
*/

#include "header.h"

int main()
{
	QueueNode** pHead = new QueueNode*;
	*pHead = nullptr;
	ifstream input("letters.txt");
	int letterNum = 0;
	char letter = '\0';

	while (!input.eof())
	{
		input >> letter;
		createQueueNode(pHead, letter);
	}

	cout << "AMMOUNT OF LETTERS: " << letterCount(*pHead) << endl;

	return 0;
}