/*
	Name: Killian Griffin
	Date: 10/5/19

	Description: We are making a program that allows the user to play a game of blackjack dice with up to 5 players.
*/

#include "header.h"

/*************************************************************
* Function: menu()                                           *
* Date Created: 10/5/19                                      *
* Date Last Modified: 10/5/19                                *
* Description: Prints the main menu to the screen            *
* Input parameters: None                                     *
* Returns: Option                                            *
* Preconditions: Start of the program                        *
* Postconditions: Option selected                            *
*************************************************************/

int menu(void)
{
	int option;

	printf("~~~~~~~~~~WELCOME TO BLACKJACK DICE~~~~~~~~~~\n");
	printf("1. Display Rules\n");
	printf("2. Add betting funds\n");
	printf("3. Play game\n");
	printf("4. Exit\n\n");
	printf("Enter a number that corresponds to an option: ");

	scanf("%d", &option); // scans a number that is put into a switch statement for activating a correspinding function

	return option;
}

/*************************************************************
* Function: print_rules()                                    *
* Date Created: 10/5/19                                      *
* Date Last Modified: 10/9/19                                *
* Description: Prints the rules of the game to the screen    *
* Input parameters: None                                     *
* Returns: Nothing                                           *
* Preconditions: Selected 1st option                         *
* Postconditions: Return to menu                             *
*************************************************************/

int print_rules(void)
{
	printf("\nBlackjack Dice involves each player rolling a die several times during their\n");
	printf("turn. At the beginning of a player's turn, they are asked to bet a sum of\n");
	printf("money. Next, they roll a die, and are asked if they would like to bet more\n");
	printf("money. This continues, and each number the player rolls is added to a grand\n");
	printf("score. The goal of this game is to get your score closest to 21 without\n");
	printf("exceeding 21. Once the score reaches or exceeds 16, the player is then asked if\n");
	printf("they would like to stop rolling. If they choose to, their turn ends, and the\n");
	printf("next player starts .The player may roll as many times as they like during their turn\n");
	printf("to get their score as close to 21 as they like. But, if the score exceeds 21, then\n");
	printf("their turn ends, and all of the money that they bet is lost. Once all of the\n");
	printf("player's turns end, whoever has the score closest to 21 gains 1.5 times the money that\n");
	printf("they bet. If any player has a score equal to 21, then they get double the money back,\n");
	printf("and the rest get nothing. The players may go for as many rounds as they want, and\n");
	printf("whoever has the greatest sum of money by the end wins the game!\n\n");
	printf("So how about it? are you ready to start?\n\n");

	return 0;
}

/*************************************************************
* Function: get_balance()                                    *
* Date Created: 10/5/19                                      *
* Date Last Modified: 10/5/19                                *
* Description: Prompts player to give a chosen starting      *
*              balance for each player                       *
* Input parameters: None                                     *
* Returns: Starting balance                                  *
* Preconditions: Selected 2nd option                         *
* Postconditions: Balance stored                             *
*************************************************************/

double get_balance(void)
{
	double balance = 0;

	printf("Enter player's account balance for the game: ");

	scanf("%lf", &balance);

	return balance;
}

/*************************************************************
* Function: get_wager()                                      *
* Date Created: 10/5/19                                      *
* Date Last Modified: 10/6/19                                *
* Description: Prompts plaer for a wager, checks if it is    *
*              less than or equal to their total balance,    *
*              and returns it.                               *
* Input parameters: player_count, playerbal, wager           *
* Returns: new_wager                                         *
* Preconditions: Start of round, or yes selection upon prompt*
* Postconditions: New wager added to old wager and subtracted*
*                 from balance                               *
*************************************************************/

double get_wager(int player_count, double playerbal, double wager)
{
	double new_wager = 0;

	printf("Player %d, place your bet:\n", player_count);

	scanf("%lf", &new_wager);
	
	while (playerbal < new_wager || new_wager < 0) // as long as player enters values not following the consraints, the loop prints the same command
	{
		printf("Player %d, your wager cannot be less than 0, or greater than your account balance\n\n", player_count);
		printf("Player %d, place your bet:\n", player_count);
		scanf("%lf", &new_wager);
	}

	return new_wager;
}

/*************************************************************
* Function: roll_die()                                       *
* Date Created: 10/5/19                                      *
* Date Last Modified: 10/5/19                                *
* Description: Finds a random number between 0 and 7 and     * 
*              returns it                                    *
* Input parameters: None                                     *
* Returns: die                                               *
* Preconditions: Player rolls a die                          *
* Postconditions: Die is added to score                      *
*************************************************************/

int roll_die(void)
{
	int die = 0;

	die = rand() % 6; // creates a range for the random number

	die++; // range is 0 - 5; adding one makes it 1 - 6

	return die;
}

/*************************************************************
* Function: calc_sum_dice()                                  *
* Date Created: 10/5/19                                      *
* Date Last Modified: 10/6/19                                *
* Description: Adds the last dice roll to the sum            *
* Input parameters: die, score                               *
* Returns: new_score                                         *
* Preconditions: A die roll is calculated                    *
* Postconditions: The die roll is added to the score         *
*************************************************************/

int calc_sum_dice(int die, int score)
{
	int new_score = 0;

	new_score = score + die;

	return new_score;
}

/*************************************************************
* Function: play_game()                                      *
* Date Created: 10/5/19                                      *
* Date Last Modified: 10/9/19                                *
* Description: Executes all prompts and calculations         *
*              nessisary to play the game                    *
* Input parameters: balance                                  *
* Returns: Nothing                                           *
* Preconditions: Selected option 3                           *
* Postconditions: Return to menu                             *
*************************************************************/

int play_game(double balance)
{
	int die = 0, score = 0, score1 = 0, score2 = 0, score3 = 0, score4 = 0, score5 = 0, stop = 0, score21 = 0, score_equal = 0, players = 0, player_count = 0, end = 1, yn = 2;
	double wager = 0, wager1 = 0, wager2 = 0, wager3 = 0, wager4 = 0, wager5 = 0, new_wager = 0;
	double playerbal = 0, player1bal = 0, player2bal = 0, player3bal = 0, player4bal = 0, player5bal = 0;
	// defined variables

	srand(time(NULL)); // allows the rand() function to work, only defined once

	printf("Enter the number of players: ");

	scanf("%d", &players);

	while (players < 2 || players > 5) // prevents players from allowing players outside acceptable range
	{
		printf("\nThe ammount of players cannot be less than 2 or exceed 5\n");
		printf("Enter the number of players: ");

		scanf("%d", &players);
	}

	player1bal = balance; // will always have at least 2 players, so first two player balances are initialized
	player2bal = balance;

	switch (players) // the rest are only initialized if the ammount of players allows for it
	{
		case 2:
			break;

		case 3:
			player3bal = balance;
			break;

		case 4:
			player3bal = balance;
			player4bal = balance;
			break;

		case 5:
			player3bal = balance;
			player4bal = balance;
			player5bal = balance;
	}
	while (end != 0) // end variable = 0 when the players wish to end the game
	{
		while (player_count + 1 <= players) 
		{
			player_count++; // player_count is used to define which player's turn it is. If player_count = 1, then it is player 1's turn, and so on

			switch (player_count) // playerbal is used to represent whichever balance belongs to the player who's turn it currently is
			{
			case 1:
				playerbal = player1bal;
				break;

			case 2:
				playerbal = player2bal;
				break;

			case 3:
				playerbal = player3bal;
				break;

			case 4:
				playerbal = player4bal;
				break;

			case 5:
				playerbal = player5bal;
				break;
			}

			new_wager = get_wager(player_count, playerbal, wager); //<--
			wager = wager + new_wager;                             //     } These lines are used whenever a player is adding to their wager.
			playerbal = playerbal - new_wager;                     //<--    It calls the get_wager function, then adds the new wager to the
			                                                       //       old one and subtracts the new wager from the balance.
			do
			{
				die = roll_die(); // dice roll is executed

				score = calc_sum_dice(die, score); // adds it to the score

				printf("Your roll: %d\n", die); // prints it for the player
				printf("Your score: %d\n", score);

				if (score >= 16 && score < 21) // starts prompting the player with the option to stop once score exceeds 16. Does not
				{                              // allow player to choose if their score is >= 21.
					printf("\nDo you want to stop rolling? (1 for yes, 0 for no)\n");
					scanf("%d", &yn);

					while (yn != 1 && yn != 0) // stops player from entering invalid values
					{
							printf("\nDo you want to stop rolling? (1 for yes, 0 for no)");
							scanf("%d", &yn);
					}
					if (yn == 1)
					{
						stop = 1;
					}
				} // end prompt done before betting prompt to disallow players from betting all their money after they know they won the round
				if (score >= 21)
				{
					stop = 1;
				}
				if (stop != 1) // bypasses betting phase if the player has chosen to stop, or has been stopped otherwise
				{
					printf("\nWould you like to bet more money? (1 for yes, 0 for no)\n");
					scanf("%d", &yn);

					while (yn != 1 && yn != 0) // stops player from entering invalid values
					{
						printf("\nWould you like to bet more money? (1 for yes, 0 for no)\n");
						scanf("%d", &yn);
					}
					if (yn == 1)
					{
						new_wager = get_wager(player_count, playerbal, wager);
						wager = wager + new_wager;
						playerbal = playerbal - new_wager;
					}
				}
			} while (stop != 1);  // when the stop variable = 1, the player has chosen to stop rolling, or their score is <= 21.
			
			if (score == 21)
			{
				score21 = 1; // used to define if one or more players scored a 21
			}

			if (score > 21) // sets score to a value guarenteed to be less than the other values
			{
				printf("\nSorry, looks like you busted!\n\n");
				score = 1;
			}
			
			switch (player_count) // updates the score and balance the player earned during the round
			{
				case 1:
					score1 = score;
					player1bal = playerbal;
					wager1 = wager;
					score = 0;
					stop = 0;
					break;

				case 2:
					score2 = score;
					player2bal = playerbal;
					wager2 = wager;
					score = 0;
					stop = 0;
					break;

				case 3:
					score3 = score;
					player3bal = playerbal;
					wager3 = wager;
					score = 0;
					stop = 0;
					break;

				case 4:
					score4 = score;
					player4bal = playerbal;
					wager4 = wager;
					score = 0;
					stop = 0;
					break;

				case 5:
					score5 = score;
					player5bal = playerbal;
					wager5 = wager;
					score = 0;
					stop = 0;
					break;
			}
		}

		if (score1 == 21) // if any player's score is equal to 21, the wager is doubled and returned to their balance 
		{
			player1bal = 2 * wager1 + player1bal;
		}
		if (score2 == 21)
		{
			player2bal = 2 * wager2 + player2bal;
		}
		if (score3 == 21)
		{
			player3bal = 2 * wager3 + player3bal;
		}
		if (score4 == 21)
		{
			player4bal = 2 * wager4 + player4bal;
		}
		if (score5 == 21)
		{
			player5bal = 2 * wager5 + player5bal;
		}

		if (score21 == 0) // if there are no 21s
		{
			if (score1 == score2) // it checks if any scores are equal
			{
				player1bal = wager1 + player1bal; // and returns the wagered ammount to each equal scoring player
				player2bal = wager2 + player2bal;
				score_equal = 1; // used to define if any of the scores are equal to each other
			}
			if (score1 == score3)
			{
				player1bal = wager1 + player1bal;
				player3bal = wager3 + player3bal;
				score_equal = 1;
			}
			if (score1 == score4)
			{
				player1bal = wager1 + player1bal;
				player4bal = wager4 + player4bal;
				score_equal = 1;
			}
			if (score1 == score5)
			{
				player1bal = wager1 + player1bal;
				player5bal = wager5 + player5bal;
				score_equal = 1;
			}
			if (score2 == score3)
			{
				player2bal = wager2 + player2bal;
				player3bal = wager3 + player3bal;
				score_equal = 1;
			}
			if (score2 == score4)
			{
				player2bal = wager2 + player2bal;
				player4bal = wager4 + player4bal;
				score_equal = 1;
			}
			if (score2 == score5)
			{
				player2bal = wager2 + player2bal;
				player5bal = wager5 + player5bal;
				score_equal = 1;
			}
			if (score3 == score4)
			{
				player3bal = wager3 + player3bal;
				player4bal = wager4 + player4bal;
				score_equal = 1;
			}
			if (score3 == score5)
			{
				player3bal = wager3 + player3bal;
				player5bal = wager5 + player5bal;
				score_equal = 1;
			}
			if (score4 == score5)
			{
				player4bal = wager4 + player4bal;
				player5bal = wager5 + player5bal;
				score_equal = 1;
			}

			if (score_equal != 1) // if no scores are equal
			{
				if (score1 > score2 && score1 > score3 && score1 > score4 && score1 > score5) // calculates which score is greatest
				{
					player1bal = 1.5 * wager1 + player1bal; // and adds the wager back * 1.5
				}
				else
				if (score2 > score1 && score2 > score3 && score2 > score4 && score2 > score5)
				{
					player2bal = 1.5 * wager2 + player2bal;
				}
				if (score3 > score1 && score3 > score2 && score3 > score4 && score3 > score5)
				{
					player3bal = 1.5 * wager3 + player3bal;
				}
				else
				if (score4 > score1 && score4 > score2 && score4 > score3 && score4 > score5)
				{
					player4bal = 1.5 * wager4 + player4bal;
				}
				else
				player5bal = 1.5 * wager5 + player5bal;
			}
		}
		switch (players) // lets the players see their standings
		{
			case 2:
				printf("Player 1 standing: $%lf\n\n", player1bal);
				printf("Player 2 standing: $%lf\n\n", player2bal);
				break;

			case 3:
				printf("Player 1 standing: $%lf\n\n", player1bal);
				printf("Player 2 standing: $%lf\n\n", player2bal);
				printf("Player 3 standing: $%lf\n\n", player3bal);
				break;

			case 4:
				printf("Player 1 standing: $%lf\n\n", player1bal);
				printf("Player 2 standing: $%lf\n\n", player2bal);
				printf("Player 3 standing: $%lf\n\n", player3bal);
				printf("Player 4 standing: $%lf\n\n", player4bal);
				break;

			case 5:
				printf("Player 1 standing: $%lf\n\n", player1bal);
				printf("Player 2 standing: $%lf\n\n", player2bal);
				printf("Player 3 standing: $%lf\n\n", player3bal);
				printf("Player 4 standing: $%lf\n\n", player4bal);
				printf("Player 5 standing: $%lf\n\n", player5bal);
				break;
		}

		printf("\nHow about another round? (1 for yes, 0 for no)\n"); // prompts for another round
		scanf("%d", &end);

		while (end != 0 && end != 1) // disallows invalid values
		{
			printf("\nHow about another round? (1 for yes, 0 for no)\n");
			scanf("%d", &end);
		}
		
		player_count = 0; // resets turn counter

	}
	if (player1bal > player2bal && player1bal > player3bal && player1bal > player4bal && player1bal > player5bal) // calculates player with the largest balance
	{
		printf("Player 1 wins!!\n\n"); // prints victory statement
		return 0;
	}
	else
	if (player2bal > player1bal && player2bal > player3bal && player2bal > player4bal && player2bal > player5bal)
	{
		printf("Player 2 wins!!\n\n");
		return 0;
	}
	else
	if (player3bal > player1bal && player3bal > player2bal && player3bal > player4bal && player3bal > player5bal)
	{
		printf("Player 3 wins!!\n\n");
		return 0;
	}
	else
	if (player4bal > player1bal && player4bal > player2bal && player4bal > player3bal && player4bal > player5bal)
	{
		printf("Player 4 wins!!\n\n");
		return 0;
	}
	else
	printf("Player 5 wins!!\n\n");
	return 0;
}