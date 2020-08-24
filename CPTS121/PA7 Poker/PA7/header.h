/*
	NAME: Killian Griffin
	DATE: 11/13/19

	DESCRIPTION: We will be making a program that allows the user to play a game of poker against the computer.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct card
{
	int face;
	int suit;
}card;

typedef struct hand
{
	card cards[5];
}hand;

int menu(void);
void rules(void);
void deal_p(const int wDeck[][13], const char* wFace[], const char* wSuit[], const int deal_n, int* deck_num, card cards[]);
void deal_c(const int wDeck[][13], const char* wFace[], const char* wSuit[], const int deal_n, int* deck_num, card cards[]);
void scan_replace(const int wDeck[][13], int array[], int* deck_num, card cards[]);
void shuffle(int wDeck[][13]);
void print_hand(const char* wFace[], const char* wSuit[], card cards[]);
int flush(card cards[]);
int straight(card cards[]);
int three_of_kind(card cards[]);
int four_of_kind(card cards[]);
int pair(card cards[]);
int two_pair(card cards[]);
int compare_hands(card card_p[], card card_c[]);
int AI(const int wDeck[][13], hand c_hand, int* deck_num);
