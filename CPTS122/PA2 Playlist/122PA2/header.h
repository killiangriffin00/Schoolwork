/*
	NAME: Killian Griffin
	DATE: 2/6/20
	ASSIGNMENT: PA2
	LAB SECTION: 5
	DESCRIPTION: This program is a movie playlist manager that loads a playlist into the program, stores a playlist in a file, displays movie
	info, edits the attributes of a record, rates movies, and plays the playlist.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct duration
{
	int hours;
	int minutes;
}Duration;

typedef struct record
{
	char title[25];
	char director[25];
	char description[200];
	char genre[10];
	Duration runtime;
	int year;
	int played;
	int rating;
}Record;

typedef struct node
{
	Record data;
	struct Node* next;
	struct Node* previous;
}Node;

int printMenu(void);
int isEmpty(Node* pHead);
int readFile(FILE* infile, Node** pHead, Node** pTail);
int writeFile(FILE* outfile, Node* pHead, Node* pTail);
int displayList(Node* pHead, Node* pTail);
int editList(Node** pHead, Node** pTail);
int rateList(Node** pHead, Node** pTail);
void playList(Node* pHead, Node* pTail);