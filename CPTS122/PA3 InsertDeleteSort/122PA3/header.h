/*
	NAME: Killian Griffin
	DATE : 2 / 23 / 20
	ASSIGNMENT : PA3
	LAB SECTION : 5
	DESCRIPTION : This program is a movie playlist manager that loads a playlist into the program, stores a playlist in a file, displays movie
	info, adds movies, deletes movies, edits the attributes of a record, sorts the playlist, rates movies, plays the playlist, and shuffles
	the play order of the movies.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

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
int insertList(Node** pHead, Node** pTail);
int deleteList(Node** pHead, Node** pTail);
int editList(Node** pHead, Node** pTail);
int sortList(Node** pHead, Node** pTail);
int rateList(Node** pHead, Node** pTail);
void playList(Node* pHead, Node* pTail);
void shuffleList(Node* pHead, Node* pTail);
int alphabetical(char string1[], char string2[]);