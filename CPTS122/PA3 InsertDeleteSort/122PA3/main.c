/*
	NAME: Killian Griffin
	DATE : 2 / 23 / 20
	ASSIGNMENT : PA3
	LAB SECTION : 5
	DESCRIPTION : This program is a movie playlist manager that loads a playlist into the program, stores a playlist in a file, displays movie
	info, adds movies, deletes movies, edits the attributes of a record, sorts the playlist, rates movies, plays the playlist, and shuffles 
	the play order of the movies.
*/

#include "header.h"

int main(void)
{
	Node* pHead = NULL, * pTail = NULL;
	FILE* infile = NULL, * outfile = NULL;
	int option = 0;
	char topline[80];

	while (option == option) // infinite loop can only be terminated if exit is chosen
	{
		option = printMenu(); // accepts an option from the user
		switch (option)
		{
		case 1: // load
			infile = fopen("moviePlayList.csv", "r");
			readFile(infile, &pHead, &pTail);
			fclose(infile);
			system("cls");
			printf("PLAYLIST LOADED\n");
			break;

		case 2: // store
			outfile = fopen("moviePlayList.csv", "w");
			writeFile(outfile, pHead, pTail);
			system("cls");
			printf("PLAYLIST STORED\n");
			fclose(outfile);
			break;

		case 3: // display
			system("cls");
			displayList(pHead, pTail);
			system("cls");
			break;

		case 4: // insert
			system("cls");
			insertList(&pHead, &pTail);
			system("cls");
			break;

		case 5: // delete
			system("cls");
			deleteList(&pHead, &pTail);
			system("cls");
			break;

		case 6: // edit
			system("cls");
			editList(&pHead, &pTail);
			system("cls");
			break;

		case 7: // sort
			system("cls");
			sortList(&pHead, &pTail);
			system("cls");
			break;

		case 8: // rate
			system("cls");
			rateList(&pHead, &pTail);
			system("cls");
			break;

		case 9: // play
			system("cls");
			playList(pHead, pTail);
			system("cls");
			break;

		case 10: // shuffle
			system("cls");
			shuffleList(pHead, pTail);
			system("cls");
			break;

		case 11: // exit
			outfile = fopen("moviePlayList.csv", "w");
			writeFile(outfile, pHead, pTail);
			fclose(outfile);
			return 0;
			break;
		}
	}
}