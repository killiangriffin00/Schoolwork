/*
	NAME: Killian Griffin
	DATE: 5/3/20
	LAB SECTION: 5
	DESCRIPTION: This program enqueues characters from a file, asks the user for a character to search for, then outputs the number of 
				 the entered character to a file.
*/

#include "header.h"

int main()
{
	Queue** head = new Queue*;
	*head = nullptr;
	ifstream infile("problem4.txt");
	char compare;
	int n = 0;

	while (!infile.eof())
	{
		(*head)->enqueue(&infile, head);
	}
	infile.close();
	cout << "Enter a character: ";
	cin >> compare;

	while (*head != nullptr)
	{
		if (compare == (*head)->dequeue(head)->getC())
		{
			++n;
		}
	}
	ofstream outfile("resultsp4.txt");
	outfile << "Number of " << compare << ": " << n;
	outfile.close();
	return 1;
}