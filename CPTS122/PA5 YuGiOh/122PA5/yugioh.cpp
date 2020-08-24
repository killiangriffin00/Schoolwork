/*
	NAME: Killian Griffin
	DATE: 3/26/20
	ASSIGMNEMT: PA5
	LAB SECTION: 5
	DESCRIPTION: This program allows the user to play the card game Yu-Gi-Oh with another user
*/

#include "header.h"

Deck::Deck()
{
	pTop = new Node;
	pTop = nullptr;
	numCards = 0;
}

Deck::Deck(Deck& copyDeck)
{
	pTop = copyDeck.pTop;
}

Deck::~Deck(){}

int Deck::addCard(Card newCard)
{
	Node *newNode = nullptr;
	newNode = new Node;
	if (numCards == 0)
	{
		pTop = newNode;
		++numCards;
		newNode->data = newCard;
		return 0;
	}

	newNode->next = pTop;
	newNode->data = newCard;

	pTop = newNode;
	return 1;
}

int Deck::subtractCard()
{
	if (numCards == 0)
	{
		return 0;
	}
	Node *temp = new Node;
	
	*temp = *pTop;
	*pTop = *pTop->next;
	delete temp;

	return 1;
}

Card Deck::getTop()
{
	return pTop->data;
}

int Deck::printDeck()
{
	Node* temp = pTop;

	for (int index = 0; index < 30; ++index)
	{
		cout << pTop->data.name << "  ATTACK: " << pTop->data.attack << "  DEFENSE: " << pTop->data.defense << "  TYPE: "
			<< pTop->data.type << endl;
		if(index )
		pTop = pTop->next;
	}
	*pTop = *temp;
	system("pause");
	system("cls");
	return 1;
}

Hand::Hand()
{
	nullCard.name[0] = '\0';
	nullCard.attack = NULL;
	nullCard.defense = NULL;
	nullCard.type[0] = '\0';

	for (int index = 0; index < 5; ++index)
	{
		inHand[index] = nullCard;
	}
}

Hand::Hand(Hand& copyHand)
{
	for (int index = 0; index < 5; ++index)
	{
		inHand[index] = copyHand.inHand[index];
	}
}

Hand::~Hand(){}

int Hand::checkEmptySlots()
{
	int empty = 0;
	for (int index = 0; index < 5; ++index)
	{
		if (checkNullCard(index))
		{
			++empty;
		}
	}

	return empty;
}

int Hand::checkNullCard(int cardNum)
{
	if ((inHand[cardNum].attack == NULL && inHand[cardNum].defense == NULL) && (inHand[cardNum].name[0] == '\0' 
		&& inHand[cardNum].type[0] == '\0'))
	{
		return 1;
	}
	return 0;
}

int Hand::checkFull()
{
	int empty = 0;
	for (int index = 0; index < 5; ++index)
	{
		if (checkNullCard(index))
		{
			empty = 1;
		}
	}
	if (empty == 1)
	{
		return 0;
	}
	return 1;
}

int Hand::printHand()
{
	for (int index = 0; index < 5; ++index)
	{
		cout << index + 1 << ". " << inHand[index].name << "  ATTACK: " << inHand[index].attack << "  DEFENSE: " << inHand[index].defense << 
			"  TYPE: " << inHand[index].type << endl;
	}
	return 1;
}

Card Hand::getCard(int cardNum)
{
	return inHand[cardNum];
}

int Hand::drawCard(Deck yugioh)
{
	int empty = -1;
	for (int index = 0; index < 5 && empty == -1; ++index)
	{
		if (checkNullCard(index))
		{
			empty = index;
		}
	}
	inHand[empty] = yugioh.getTop();
	yugioh.subtractCard();
	return 1;
}

int Hand::discard(int cardNum)
{
	if (!checkNullCard(cardNum))
	{
		inHand[cardNum] = nullCard;
		return 1;
	}
	return 0;
}

int Hand::drawToFull(Deck yugioh)
{
	if (checkFull())
	{
		return 0;
	}
	for (int index = 0; index < 5; ++index)
	{
		if (checkNullCard(index))
		{
			drawCard(yugioh);
		}
	}
	return 1;
}

int readDeckFile(Deck* pDeck)
{
	ifstream premadeDeck("premadeDeck.txt");
	for (int index1 = 0; index1 < 30; ++index1)
	{
		Card newCard;
		int index = 1;
		char trash = 0;
		premadeDeck >> newCard.name[index - 1];
		for (; newCard.name[index - 1] != ','; ++index)
		{
			premadeDeck >> newCard.name[index];
		}
		newCard.name[index - 1] = NULL;
		index = 1;

		premadeDeck >> newCard.attack;
		premadeDeck >> trash;
		premadeDeck >> newCard.defense;
		premadeDeck >> trash;

		premadeDeck >> newCard.type[index - 1];
		for (; newCard.type[index - 1] != ','; ++index)
		{
			premadeDeck >> newCard.type[index];
		}
		newCard.type[index - 1] = NULL;
		index = 1;

		pDeck->addCard(newCard);
	}
	return 1;
}