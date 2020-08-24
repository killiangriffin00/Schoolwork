/*
	NAME: Killian Griffin
	DATE: 10/29/19

	DESCRIPTION: We are making a program that lets the user play the game Battleship against an A.I.

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

typedef struct Space
{
	int y;
	int x;
	char status;

}sp;

int rules(void);
int initialize(sp array[][10], int row);
int valid_rand(sp array[][10], int ship, int* x, int* y, int* direction);
int print_board(sp array[][10]);
int place_rand(sp array[][10]);
int place_ship_rand(sp array[][10], int ship, int x, int y, int direction, char ship_type);
int place_manual(sp array[][10]);
int place_ship_manual(sp array[][10], char ship_name[], char ship_type, int ship_size);
int ship_check(sp array[][10], char check);

