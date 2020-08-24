/*
	NAME: Killian Griffin
	DATE: 4/9/20
	LAB SECTION: 5
	ASSIGNMENT: PA6
	DESCRIPTION: This program takes english characters and converts them to morse code
*/

#include "header.h"

int main()
{
	ifstream tableFile("MorseTable.txt"), translateFile("Convert.txt");
	MorseBST MorseTable(&tableFile);
	char letter = '\0';

	MorseTable.printBST();
	
	while (!translateFile.eof())
	{
		translateFile >> letter;

		if (letter <= 'z' && letter >= 'a')
		{
			letter -= 32;
		}

		if (letter == ' ')
		{
			cout << "   ";
		}
		else
			cout << " " << MorseTable.searchMorse(letter) << " ";
	}
	
	return 0;
}