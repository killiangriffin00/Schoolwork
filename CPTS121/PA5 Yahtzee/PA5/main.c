/*
	Name: Killian Griffin
	Date: 10/15/19

	Description: We are making a program that lets the user play the game Yahtzee.
*/

#include "header.h"

int main(void)
{
	int option = 0;

	option = print_menu();

	while (option == option)
	{
		switch (option)
		{
		case 1:
			print_rules();
			option = print_menu();
			break;

		case 2:
			play_game();
			option = print_menu();
			break;

		case 3:
			return 0;
			break;
		}
	}
}