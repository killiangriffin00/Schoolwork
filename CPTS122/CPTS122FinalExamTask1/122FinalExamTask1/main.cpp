/*
	NAME: Killian Griffin
	DATE: 5/3/20
	LAB SECTION: 5
	DESCRIPTION: This program reads characters from a text file into a stack and outputs them into another text file in reverse order.
*/

#include "header.h"

int main()
{
	Stack** head = new Stack*;
	ifstream infile("input.txt");
	*head = nullptr;

	while (!infile.eof())
	{
		(*head)->pull(&infile, head);
	}
	infile.close();

	ofstream outfile("output.txt");
	(*head)->print(&outfile, head);
	outfile.close();
}
