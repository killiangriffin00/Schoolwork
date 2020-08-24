/*
	NAME: Killian Griffin
	DATE: 3/26/20
	ASSIGMNEMT: PA5
	LAB SECTION: 5
	DESCRIPTION: This program allows the user to play the card game Yu-Gi-Oh with another user
*/

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <ctime>

using namespace std;

struct Card
{
	char name[40];
	int attack;
	int defense;
	char type[20];
};

struct Node
{
	Card data;
	struct Node* next;
};

class Deck
{
private:
	Node *pTop;
	int numCards;

public:
	Deck();
	Deck(Deck &copyDeck);
	~Deck();
	Card getTop();
	int printDeck();
	int addCard(Card newCard);
	int subtractCard();
};


class Hand
{
private:
	Card inHand[5];
	Card nullCard;

public:
	Hand();
	Hand(Hand &copyHand);
	~Hand();
	int checkEmptySlots();
	int checkNullCard(int cardNum);
	int checkFull();
	int printHand();
	Card getCard(int cardNum);
	int drawCard(Deck yugioh);
	int discard(int cardNum);
	int drawToFull(Deck yugioh);
};

int readDeckFile(Deck* pDeck);

#endif