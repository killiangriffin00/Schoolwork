/*
	NAME: Killian Griffin
	DATE: 11/13/19

	DESCRIPTION: We will be making a program that allows the user to play a game of poker against the computer.
*/

#include "header.h"

int main(void)
{
	int option = 0, game = 0;

	card c_init;
	c_init.face = 0;
	c_init.suit = 0;

	hand p_hand;
	for (int index = 0; index < 5; ++index)
	{
		p_hand.cards[index] = c_init;
	}

	hand c_hand;
	for (int index = 0; index < 5; ++index)
	{
		c_hand.cards[index] = c_init;
	}

	
	while (option == option)
	{
		option = menu();

		switch (option)
		{
		case 1:
			rules();
			break;

		case 2:

			srand((unsigned)time(NULL)); /* seed random-number generator */

			for (int end = 0; end == 0;)
			{
				system("cls");

				int turn = 0, replace[5] = { 0,0,0,0,0 }, check = 0, deck_count = 0, winner = 0;
				char yn = '\0';

				/* initialize suit array */
				const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

				/* initialize face array */
				const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
					"Nine", "Ten", "Jack", "Queen", "King" };

				/* initalize deck array */
				int deck[4][13] = { 0 };

				shuffle(deck);
				deal_p(deck, face, suit, 5, &deck_count, p_hand.cards);
				deal_c(deck, face, suit, 5, &deck_count, c_hand.cards);
				

				turn = (rand() % 2) + 1;

				switch (turn)
				{
				case 1:
					printf("\nYou go first\n\n");
					printf("Would you like to replace some cards? (y for yes, n for no)\n");
					scanf(" %c", &yn);

					while (yn != 'y' && yn != 'n')
					{
						printf("Would you like to replace some cards? (y for yes, n for no)\n");
						scanf(" %c", &yn);
					}
					if (yn == 'y')
					{
						system("cls");
						printf("Choose numbers that correspond to cards in your hand and enter the rest as zeros:\n");
						print_hand(face, suit, p_hand.cards);
						scanf("%d%d%d%d%d", &replace[0], &replace[1], &replace[2], &replace[3], &replace[4]);

						for (int first = 1; first == 1 || check == 1;)
						{
							for (int index = 0; index < 5 && check == 0; ++index)
							{
								if (replace[index] < 0 || replace[index] > 5)
								{
									check = 1;
								}
							}
							if (check == 1)
							{
								printf("Choose numbers for cards you want to replace, and enter the rest as zeros:\n");
								print_hand(face, suit, p_hand.cards);
								scanf("%d%d%d%d%d", &replace[0], &replace[1], &replace[2], &replace[3], &replace[4]);
							}
							first = 0;
						}

						scan_replace(deck, replace, &deck_count, p_hand.cards);
						system("cls");
						AI(deck, c_hand, &deck_count);
						print_hand(face, suit, p_hand.cards);
						printf("\n\n");
						print_hand(face, suit, c_hand.cards);
						printf("\n\n");

						winner = compare_hands(p_hand.cards, c_hand.cards);
						if (winner == 1)
						{
							printf("You won the round!\n");
							printf("Wanna go for another? (y, n)");
						}
						if (winner == 2)
						{
							printf("You lost the round...\n");
							printf("Wanna go for another? (y, n)");
						}
						scanf(" %c", &yn);
						while (yn != 'y' && yn != 'n')
						{
							printf("Wanna go for another? (y, n)");
							scanf(" %c", &yn);
						}
						if (yn == 'n')
						{
							end = 1;
						}
					}
					break;

				case 2:
					printf("\nComputer goes first\n\n");
					AI(deck, c_hand, &deck_count);
					system("pause");
					system("cls");
					print_hand(face, suit, p_hand.cards);
					printf("Would you like to replace some cards? (y for yes, n for no)\n");
					scanf(" %c", &yn);

					while (yn != 'y' && yn != 'n')
					{
						printf("Would you like to replace some cards? (y for yes, n for no)\n");
						scanf(" %c", &yn);
					}
					if (yn == 'y')
					{
						system("cls");
						printf("Choose numbers that correspond to cards in your hand and enter the rest as zeros:\n");
						print_hand(face, suit, p_hand.cards);
						scanf("%d %d %d %d %d", &replace[0], &replace[1], &replace[2], &replace[3], &replace[4]);

						for (int first = 1; first == 1 || check == 1;)
						{
							for (int index = 0; index < 5 && check == 0; ++index)
							{
								if (replace[index] < 0 || replace[index] > 5)
								{
									check = 1;
								}
							}
							if (check == 1)
							{
								printf("Choose numbers for cards you want to replace, and enter the rest as zeros:\n");
								print_hand(face, suit, p_hand.cards);
								scanf("%d%d%d%d%d", &replace[0], &replace[1], &replace[2], &replace[3], &replace[4]);
							}
							first = 0;
						}

						scan_replace(deck, replace, &deck_count, p_hand.cards);
						system("cls");
						print_hand(face, suit, p_hand.cards);
						printf("\n\n");
						print_hand(face, suit, c_hand.cards);

						winner = compare_hands(p_hand.cards, c_hand.cards);
						if (winner == 1)
						{
							printf("You won the round!\n");
							printf("Wanna go for another? (y, n)\n");
						}
						if (winner == 2)
						{
							printf("You lost the round...\n");
							printf("Wanna go for another? (y, n)\n");
						}
						scanf(" %c", &yn);
						while (yn != 'y' && yn != 'n')
						{
							printf("Wanna go for another? (y, n)\n");
							scanf(" %c", &yn);
						}
						if (yn == 'n')
						{
							end = 1;
						}
					}
					break;
				}
			}
			break;

		case 3:
			return 0;
			break;
		}
	}
}