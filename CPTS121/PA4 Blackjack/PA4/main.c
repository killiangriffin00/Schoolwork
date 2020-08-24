/*
	Name: Killian Griffin
	Date: 10/5/19

	Description: We are making a program that allows the user to play a game of blackjack dice with up to 5 players.
*/

#include "header.h"

int main(void)
{
	int option = 0; // used to allow menu selection
	double balance = 0; // used to store initial balance

	option = menu(); // gets player option
	
	while (option < 1 || option > 4) // prints menu again if option is invalid
	{
		option = menu();
	}
	while (option != 0)
	switch (option)
	{
		case 1: // print rules
			print_rules();
			option = menu();
			break;

		case 2: // imput balance
			balance = get_balance();
			option = menu();
			break;

		case 3: // play game
			play_game(balance);
			option = menu();
			break;

		case 4: // exit game
			return 0;
			break;
	}
}