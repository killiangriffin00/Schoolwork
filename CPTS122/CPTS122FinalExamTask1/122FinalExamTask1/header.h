/*
	NAME: Killian Griffin
	DATE: 5/3/20
	LAB SECTION: 5
	DESCRIPTION: This program reads characters from a text file into a stack and outputs them into another text file in reverse order.
*/

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>

using namespace std;

class Stack
{
private:
	char c;
	Stack* next;

public:
	Stack() {}
	Stack(Stack** head);
	char getC();
	bool setC(char newC);
	Stack* pop();
	bool pull(ifstream* file, Stack** head);
	bool print(ofstream* file, Stack** head);
};






#endif