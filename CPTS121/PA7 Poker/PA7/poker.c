/*
	NAME: Killian Griffin
	DATE: 11/13/19

	DESCRIPTION: We will be making a program that allows the user to play a game of poker against the computer.
*/

#include "header.h"

int menu(void)
{
	int option = 0;

	printf("|||||||||| WELCOME TO POKER ||||||||||\n");
	printf("| 1. View rules of the game          |\n");
	printf("| 2. Play the game                   |\n");
	printf("| 3. Exit                            |\n");
	printf("|____________________________________|\n");
	printf("\nChoose an option: ");

	scanf("%d", &option);

	while (option < 1 || option > 3)
	{
		printf("\nChoose an option: ");

		scanf("%d", &option);
	}
	
	system("cls");

	return option;
}

void rules(void)
{
	printf("The objective of 5-Card-Draw Poker is to get a better hand than the opponent. The game\n");
	printf("is played in rounds. Each round starts with a drawing phase, during which each player is\n");
	printf("dealt five cards. After the drawing phase, the players take turns choosing which cards to\n");
	printf("swap with the dealer. The goal is to get the highest card combination. The combinations, from\n");
	printf("lowest to highest are a pair (two cards with the same face), two pairs (two sets of cards with\n");
	printf("the same faces), three-of-a-kind (three cards with the same faces), four-of-a-kind (four cards\n");
	printf("with the same face), flush (five cards of the same suit), and a straight (a sequence of faces\n");
	printf("on five cards). If two opponents get the same combination, the sums of the player's cards decide\n");
	printf("the victor.\n\n");

	system("pause");
	system("cls");
}

/* shuffle cards in deck */

void shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

/* deal cards in deck */
void deal_p(const int wDeck[][13], const char* wFace[], const char* wSuit[], const int deal_n, int* deck_num, card cards[])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card_count = 0;   /* card counter */
	int limit = *deck_num;
	int index = 0;
	/* deal each of the 5 cards */
	for (card_count = *deck_num + 1; card_count <= deal_n + limit; card_count++)
	{
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				/* if slot contains current card, display card */
				if (wDeck[row][column] == card_count)
				{
					printf("%s of %s\n", wFace[column], wSuit[row]);

					cards[index].face = column;
					cards[index].suit = row;

					++* deck_num;
				}
			}
		}
		++index;
	}
}

/* deal cards in deck */
void deal_c(const int wDeck[][13], const char* wFace[], const char* wSuit[], const int deal_n, int* deck_num, card cards[])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card_count = 0;   /* card counter */
	int limit = *deck_num;
	int index = 0;

	/* deal each of the 5 cards */
	for (card_count = *deck_num; card_count <= deal_n + limit; card_count++)
	{
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				/* if slot contains current card, display card */
				if (wDeck[row][column] == card_count)
				{
					cards[index].face = column;
					cards[index].suit = row;

					++* deck_num;
				}
			}
		}
		++index;
	}
}

void print_hand(const char* wFace[], const char* wSuit[], card cards[])
{
	printf("1. %s of %s\n", wFace[cards[0].face], wSuit[cards[0].suit]);
	printf("2. %s of %s\n", wFace[cards[1].face], wSuit[cards[1].suit]);
	printf("3. %s of %s\n", wFace[cards[2].face], wSuit[cards[2].suit]);
	printf("4. %s of %s\n", wFace[cards[3].face], wSuit[cards[3].suit]);
	printf("5. %s of %s\n", wFace[cards[4].face], wSuit[cards[4].suit]);
}

void scan_replace(const int wDeck[][13], int array[], int* deck_num, card cards[])
{
	int end = 0;
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card_count = 0;   /* card counter */
	int limit = deck_num;

	for (int index = 0; index < 5 && end == 0; ++index)
	{
		switch (array[index])
		{
		case 0:
			end = 1;
			break;

		case 1:
			/* deal each of the 5 cards */
			for (card_count = deck_num; card_count <= 1 + limit; card_count++)
			{
				/* loop through rows of wDeck */
				for (row = 0; row <= 3; row++)
				{
					/* loop through columns of wDeck for current row */
					for (column = 0; column <= 12; column++)
					{
						/* if slot contains current card, display card */
						if (wDeck[row][column] == card_count)
						{
							cards[0].face = column;
							cards[0].suit = row;

							++deck_num;
						}
					}
				}
			}
			break;

		case 2:
			/* deal each of the 5 cards */
			for (card_count = deck_num; card_count <= 1 + limit; card_count++)
			{
				/* loop through rows of wDeck */
				for (row = 0; row <= 3; row++)
				{
					/* loop through columns of wDeck for current row */
					for (column = 0; column <= 12; column++)
					{
						/* if slot contains current card, display card */
						if (wDeck[row][column] == card_count)
						{
							cards[1].face = column;
							cards[1].suit = row;

							++deck_num;
						}
					}
				}
			}
			break;

		case 3:
			/* deal each of the 5 cards */
			for (card_count = deck_num; card_count <= 1 + limit; card_count++)
			{
				/* loop through rows of wDeck */
				for (row = 0; row <= 3; row++)
				{
					/* loop through columns of wDeck for current row */
					for (column = 0; column <= 12; column++)
					{
						/* if slot contains current card, display card */
						if (wDeck[row][column] == card_count)
						{
							cards[2].face = column;
							cards[2].suit = row;

							++deck_num;
						}
					}
				}
			}
			break;

		case 4:
			/* deal each of the 5 cards */
			for (card_count = deck_num; card_count <= 1 + limit; card_count++)
			{
				/* loop through rows of wDeck */
				for (row = 0; row <= 3; row++)
				{
					/* loop through columns of wDeck for current row */
					for (column = 0; column <= 12; column++)
					{
						/* if slot contains current card, display card */
						if (wDeck[row][column] == card_count)
						{
							cards[3].face = column;
							cards[3].suit = row;

							++deck_num;
						}
					}
				}
			}
			break;

		case 5:

			/* deal each of the 5 cards */
			for (card_count = deck_num; card_count <= 1 + limit; card_count++)
			{
				/* loop through rows of wDeck */
				for (row = 0; row <= 3; row++)
				{
					/* loop through columns of wDeck for current row */
					for (column = 0; column <= 12; column++)
					{
						/* if slot contains current card, display card */
						if (wDeck[row][column] == card_count)
						{
							cards[4].face = column;
							cards[4].suit = row;

							++deck_num;
						}
					}
				}
			}
			break;
		}
	}
}

int flush(card cards[])
{
	int flush = 0, same_suit = 0;

	for (int index = 0; index < 4; ++index)
	{
		if (cards[0].suit == cards[index + 1].suit)
		{
			++same_suit;
		}
	}
	if (same_suit == 4)
	{
		flush = 1;
	}
	return flush;
}

int straight(card cards[])
{
	int order[5] = { 0,0,0,0,0 }, temp = 0, least = 0, least_in = 0, straight = 0;

	for (int index = 0; index < 5; ++index)
	{
		order[index] = cards[index].face;
	}
	for (int div = 0; div < 5; ++div)
	{
		least = order[div];
		least_in = div;
		for (int index = 0 + div; index < 5; ++index)
		{
			if (order[index] < least)
			{
				least_in = index;
				least = order[index];
			}
		}
		temp = order[div];
		order[div] = order[least_in];
		order[least_in] = temp;
	}
	if (order[0] + 1 == order[1] && order[1] + 1 == order[2] && order[2] + 1 == order[3] && order[3] + 1 == order[4])
	{
		straight = 1;
	}
	return straight;
}

int three_of_kind(card cards[])
{
	int kind = 0, three_kind = 0;
	for (int number = 1; number < 13 && kind < 3; ++number)
	{
		for (int index = 0; index < 5; ++index)
		{
			if (cards[index].face == number)
			{
				++kind;
			}
		}
		if (kind >= 3)
		{
			three_kind = 1;
		}
		kind = 3;
	}
	return three_kind;
}

int four_of_kind(card cards[])
{
	int kind = 0, four_kind = 0;
	for (int number = 1; number < 13 && kind < 4; ++number)
	{
		for (int index = 0; index < 5; ++index)
		{
			if (cards[index].face == number)
			{
				++kind;
			}
		}
		if (kind >= 4)
		{
			four_kind = 1;
		}
		kind = 0;
	}
	return four_kind;
}

int pair(card cards[])
{
	int kind = 0, two_kind = 0;
	for (int number = 1; number < 13 && kind < 4; ++number)
	{
		for (int index = 0; index < 5; ++index)
		{
			if (cards[index].face == number)
			{
				++kind;
			}
		}
		if (kind >= 2)
		{
			two_kind = 1;
		}
		kind = 0;
	}
	return two_kind;
}

int two_pair(card cards[])
{
	int kind = 0, two_pair = 0, pair_number = 0;
	for (int number = 1; number < 13 && kind < 4; ++number)
	{
		for (int index = 0; index < 5; ++index)
		{
			if (cards[index].face == number)
			{
				++kind;
			}
		}
		if (kind >= 2)
		{
			pair_number = number;
		}
		kind = 0;
	}
	for (int number = 1; number < 13 && kind < 4; ++number)
	{
		for (int index = 0; index < 5; ++index)
		{
			if (cards[index].face == number && number != pair_number)
			{
				++kind;
			}
		}
		if (kind >= 2)
		{
			two_pair = 1;
		}
		kind = 0;
	}
	return two_pair;
}

int compare_hands(card card_p[], card card_c[])
{
	int player = 0, comp = 0, total_c = 0, total_p = 0, win = 0;

	if (pair(card_p) == 1)
	{
		player = 1;
	}
	if (two_pair(card_p) == 1)
	{
		player = 2;
	}
	if (three_of_kind(card_p) == 1)
	{
		player = 3;
	}
	if (four_of_kind(card_p) == 1)
	{
		player = 4;
	}
	if (flush(card_p) == 1)
	{
		player = 5;
	}
	if (straight(card_p) == 1)
	{
		player = 6;
	}
	
	if (pair(card_c) == 1)
	{
		comp = 1;
	}
	if (two_pair(card_c) == 1)
	{
		comp = 2;
	}
	if (three_of_kind(card_c) == 1)
	{
		comp = 3;
	}
	if (four_of_kind(card_c) == 1)
	{
		comp = 4;
	}
	if (flush(card_c) == 1)
	{
		comp = 5;
	}
	if (straight(card_c) == 1)
	{
		comp = 6;
	}

	if (comp < player)
	{
		win = 1;
	}
	if (comp > player)
	{
		win = 2;
	}
	if (comp == player)
	{
		for (int index = 0; index < 5; ++index)
		{
			total_p = total_p + card_p[index].face;
		}
		for (int index = 0; index < 5; ++index)
		{
			total_c = total_c + card_c[index].face;
		}

		if (total_c < total_p)
		{
			win = 1;
		}
		if (total_c > total_p)
		{
			win = 2;
		}
	}
	return win;
}

int AI(const int wDeck[][13], hand c_hand, int *deck_num)
{
	int stay = 0, replace1 = 0, replace2 = 0;

	if (three_of_kind(c_hand.cards) == 1)
	{
		stay = rand() % 2;
	}
	if (four_of_kind(c_hand.cards) == 1)
	{
		stay = 1;
	}
	if (flush(c_hand.cards) == 1)
	{
		stay = 1;
	}
	if (straight(c_hand.cards) == 1)
	{
		stay = 1;
	}

	if (stay == 0)
	{
		if (three_of_kind(c_hand.cards) != 1)
		{
			if (pair(c_hand.cards) == 1)
			{
				int kind = 0, two_pair = 0, pair_number = 0;
				for (int number = 1; number < 13 && kind < 4; ++number)
				{
					for (int index = 0; index < 5; ++index)
					{
						if (c_hand.cards[index].face == number)
						{
							++kind;
						}
					}
					if (kind >= 2)
					{
						pair_number = number;
					}
					kind = 0;
				}
				for (int choose = 0; choose == 0;)
				{
					int random1 = rand() % 5;
					int random2 = rand() % 5;
					if (c_hand.cards[random1].face != pair_number)
					{
						replace1 = random1;
						if (c_hand.cards[random2].face != pair_number)
						{
							replace2 = random2;
							choose = 1;
						}
					}
				}
			}
		}
		if (three_of_kind(c_hand.cards) == 1)
		{
			int kind = 0, two_pair = 0, pair_number = 0;
			for (int number = 1; number < 13 && kind < 4; ++number)
			{
				for (int index = 0; index < 5; ++index)
				{
					if (c_hand.cards[index].face == number)
					{
						++kind;
					}
				}
				if (kind >= 3)
				{
					pair_number = number;
				}
				kind = 0;
			}
			for (int choose = 0; choose == 0;)
			{
				int random1 = rand() % 5;
				int random2 = rand() % 5;
				if (c_hand.cards[random1].face != pair_number)
				{
					replace1 = random1;
					if (c_hand.cards[random2].face != pair_number)
					{
						replace2 = random2;
						choose = 1;
					}
				}
			}
		}
	}
	int flush = 0, same_suit = 0, max_suit = 0;

	for (int index = 0; index < 4; ++index)
	{
		if (c_hand.cards[0].suit == c_hand.cards[index + 1].suit)
		{
			++same_suit;
			max_suit = index;
		}
	}
	if (same_suit == 3)
	{
		for (int choose = 0; choose == 0;)
		{
			int random1 = rand() % 5;
			int random2 = rand() % 5;
			if (c_hand.cards[random1].suit != max_suit)
			{
				replace1 = random1;
				if (c_hand.cards[random2].suit != max_suit)
				{
					replace2 = random2;
					choose = 1;
				}
			}
		}
	}
	int order[5] = { 0,0,0,0,0 }, temp = 0, least = 0, least_in = 0;

	for (int index = 0; index < 5; ++index)
	{
		order[index] = c_hand.cards[index].face;
	}
	for (int div = 0; div < 5; ++div)
	{
		least = order[div];
		least_in = div;
		for (int index = 0 + div; index < 5; ++index)
		{
			if (order[index] < least)
			{
				least_in = index;
				least = order[index];
			}
		}
		temp = order[div];
		order[div] = order[least_in];
		order[least_in] = temp;
	}
	if (order[0] + 1 == order[1] && order[1] + 1 == order[2] && order[2] + 1 == order[3])
	{
		replace1 = order[4];
	}

	if (order[1] + 1 == order[2] && order[2] + 1 == order[3] && order[3] + 1 == order[4])
	{
		replace1 = order[0];
	}

	int replace_num[5] = { 0,0,0,0,0 };

	for (int index = 0; index < 5; ++index)
	{
		if (c_hand.cards[index].face == replace1)
		{
			replace_num[0] = replace1;
		}
		if (c_hand.cards[index].face == replace2)
		{
			replace_num[1] = replace2;
		}
	}

	scan_replace(wDeck, replace_num, &*deck_num, c_hand.cards);
	
	return 0;
}