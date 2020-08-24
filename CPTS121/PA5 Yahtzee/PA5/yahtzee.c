/*
	Name: Killian Griffin
	Date: 10/15/19

	Description: We are making a program that lets the user play the game Yahtzee.
*/

#include "header.h"

int print_menu(void)
{
	int option = 0;

	printf("-|-|-|-|-|WELCOME TO YAHTZEE|-|-|-|-|-\n");
	printf("1. Display rules\n");
	printf("2. Play game\n");
	printf("3. Exit\n");
	printf("Enter a number that corresponds to an option:\n");

	scanf("%d", &option);

	while (option < 1 && option > 3)
	{
		printf("Enter a number that corresponds to an option:\n");
		scanf("%d", &option);
	}
	system("cls");

	return option;
}

int print_rules(void)
{
	printf("Yahtzee is a two-player game in which players duel against each othe rot see who can\n");
	printf("score the most points. On each player's turn, they roll five dice simultaneously. The\n");
	printf("player can choose to reroll one of their dice three times, changing dice each time if\n");
	printf("they desire. The goal is to get the die faces to line up with a combination. There are\n");
	printf("thirteen diferent combinations with differing score values listed here:\n\n");
	printf("1. Sum of 1's: Sums together all dice with a 1 face\n");
	printf("2. Sum of 2's: Sums together all dice with a 2 face\n");
	printf("3. Sum of 3's: Sums together all dice with a 3 face\n");
	printf("4. Sum of 4's: Sums together all dice with a 4 face\n");
	printf("5. Sum of 5's: Sums together all dice with a 5 face\n");
	printf("6. Sum of 6's: Sums together all dice with a 6 face\n");
	printf("7. Three-of-a-kind: Three dice with the same face. Sums together all 5 dice\n");
	printf("8. Four-of-a-kind: Four dice with the same face. Sums together all 5 dice\n");
	printf("9. Full House: One Three-of-a-kind and one pair. Awards 25 points\n");
	printf("10. Small Straight: A sequence of four dice. Awards 30 points\n");
	printf("11. Large Straight: A sequence of five dice. Awards 40 points\n");
	printf("12. Yahtzee: Five dice with the same face. Awards 50 points\n");
	printf("13. Chance: Any combination of dice. Sums together all 5 dice\n\n");
	printf("Once a player has chosen a combination for their turn, they cannot choose that same\n");
	printf("combination for the rest of the game. The game goes for thirteen rounds, where one\n");
	printf("round ends when both players have taken their turn. When the game ends, whoever has\n");
	printf("the most points is the victor.\n\n");

	system("pause");
	system("cls");
}

int roll_dice(int dice[], int size)
{
	for (int index = 0; index < size; ++index)
	{
		dice[index] = (rand() % 6) + 1;
	}
}

int roll_spec_die(int dice[], int index)
{
	dice[index] = (rand() % 6 + 1);
}

int sum_number(int dice[], int size, int number)
{
	int num_num = 0, score = 0;
	for (int index = 0; index < size; ++index)
	{
		if (dice[index] == number)
		{
			++num_num;
		}
	}

	score = num_num * number;
	return score;
}

int three_of_kind(int dice[], int size)
{
	int kind = 0, score = 0;
	for (int number = 1; number < 6 && kind < 3; ++number)
	{
		for (int index = 0; index < size; ++index)
		{
			if (dice[index] == number)
			{
				++kind;
			}
		}
		if (kind >= 3)
		{
			score = dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
		}
		kind = 0;
	}
	return score;
}

int four_of_kind(int dice[], int size)
{
	int kind = 0, score = 0;
	for (int number = 1; number < 6 && kind < 4; ++number)
	{
		for (int index = 0; index < size; ++index)
		{
			if (dice[index] == number)
			{
				++kind;
			}
		}
		if (kind >= 4)
		{
			score = dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
		}
		kind = 0;
	}
	return score;
}

int full_house(int dice[], int size)
{
	int kind = 0, pair = 0, score = 0, kind_num = 0, pair_num1 = 0, pair_num2 = 0;
	for (int number = 1; number <= 6 && kind <= 3; ++number)
	{
		for (int index = 0; index < size; ++index)
		{
			if (dice[index] == number)
			{
				++kind;
				kind_num = number;
			}
		}
		if (kind == 3)
		{
			for (int index = 0; index < size; ++index)
			{
				if (dice[index] != kind_num)
				{
					if (pair_num1 == 0)
					{
						pair_num1 = dice[index];
					}
					else
					pair_num2 = dice[index];
				}
			}
			if (pair_num1 == pair_num2)
			{
				score = 25;
			}
		}
		kind = 0;
		kind_num = 0;
	}
	return score;
}

int chance(int dice[])
{
	int score = 0;

	score = dice[0] + dice[1] + dice[2] + dice[3] + dice[4];

	return score;
}

int large_straight(int dice[], int size)
{
	int order[5] = {0,0,0,0,0}, temp = 0, least = 0, least_in = 0, score = 0;

	for (int index = 0; index < size; ++index)
	{
		order[index] = dice[index];
	}
	for (int div = 0; div < size; ++div)
	{
		least = order[div];
		least_in = div;
		for (int index = 0 + div; index < size; ++index)
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
		score = 40;
	}
	return score;
}

int small_straight(int dice[], int size)
{
	int order[5] = { 0,0,0,0,0 }, temp = 0, least = 0, least_in = 0, score = 0;

	for (int index = 0; index < size; ++index)
	{
		order[index] = dice[index];
	}
	for (int div = 0; div < size; ++div)
	{
		least = order[div];
		least_in = div;
		for (int index = 0 + div; index < size; ++index)
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
		score = 30;
	}

	if (order[1] + 1 == order[2] && order[2] + 1 == order[3] && order[3] + 1 == order[4])
	{
		score = 30;
	}

	return score;
}

int yahtzee(int dice[], int size)
{
	int kind = 0, score = 0;
	for (int number = 1; number < 6 && kind < 5; ++number)
	{
		for (int index = 0; index < size; ++index)
		{
			if (dice[index] == number)
			{
				++kind;
			}
		}
		if (kind == 5)
		{
			score = 50;
		}
		kind = 0;
	}
	return score;
}

int combo_menu(int dice[])
{
	int option = 0;
	system("cls");

	printf("Choose a number corresponding to a combination (not selected yet) for your set of dice: \n%d, %d, %d, %d, %d\n\n", dice[0], dice[1], dice[2], dice[3], dice[4]);
	printf("1. Sum of 1's\n");
	printf("2. Sum of 2's\n");
	printf("3. Sum of 3's\n");
	printf("4. Sum of 4's\n");
	printf("5. Sum of 5's\n");
	printf("6. Sum of 6's\n");
	printf("7. Three-of-a-kind\n");
	printf("8. Four-of-a-kind\n");
	printf("9. Full house\n");
	printf("10. Small straight\n");
	printf("11. Large straight\n");
	printf("12. Yahtzee\n");
	printf("13. Chance\n\n");

	scanf("%d", &option);

	return option;
}

int play_game(void)
{
	int dice[5] = { 0,0,0,0,0 }, turn = 0, int_option = 0, combo_number = 0, sum1_1 = 0, sum2_1 = 0, sum3_1 = 0, sum4_1 = 0, sum5_1 = 0;
	int sum6_1 = 0, three_kind_1 = 0, four_kind_1 = 0, full_house_1 = 0, sm_str_1 = 0, lg_str_1 = 0, chance_1 = 0, sum1_2 = 0, sum2_2 = 0;
	int sum3_2 = 0, sum4_2 = 0, sum5_2 = 0, sum6_2 = 0, three_kind_2 = 0, four_kind_2 = 0, full_house_2 = 0, sm_str_2 = 0, lg_str_2 = 0;
	int chance_2 = 0, combo_selected = 0, score = 0, score1 = 0, score2 = 0, pass_turn = 0;
	char yn = '\0', char_option = '\0';

	srand(time(NULL));

	while (pass_turn != 26)
	{
		++turn;
		if (turn > 2)
		{
			turn = 1;
		}
		printf("Player %d, your turn.\n\n", turn);

		system("pause");

		roll_dice(dice, 5);

		printf("You rolled: %d, %d, %d, %d, %d\n\n", dice[0], dice[1], dice[2], dice[3], dice[4]);

		printf("Reroll one of your numbers? (y for yes, n for no)\n");

		scanf(" %c", &yn);
		while (yn != 'y' && yn != 'n')
		{
			printf("Reroll one of your numbers? (y for yes, n for no)\n");

			scanf(" %c", &yn);
		}

		if (yn == 'y')
		{
			for (int reroll = 0; reroll < 3 && yn != 'n'; ++reroll)
			{
				system("cls");
				printf("a. %d\nb. %d\nc. %d\nd. %d\ne. %d\n\n", dice[0], dice[1], dice[2], dice[3], dice[4]);
				printf("Type a letter corresponding to the die value you want to reroll.\n");

				scanf(" %c", &char_option);

				while ('a' > char_option > 'e')
				{
					printf("Type a letter corresponding to the die value you want to reroll.\n");

					scanf(" %c", &char_option);
				}

				switch (char_option)
				{
				case 'a':
					roll_spec_die(dice, 0);
					break;

				case 'b':
					roll_spec_die(dice, 1);
					break;

				case 'c':
					roll_spec_die(dice, 2);
					break;

				case 'd':
					roll_spec_die(dice, 3);
					break;

				case 'e':
					roll_spec_die(dice, 4);
					break;
				}

				printf("Your dice: %d, %d, %d, %d, %d\n\n", dice[0], dice[1], dice[2], dice[3], dice[4]);

				if (reroll < 2)
				{
					printf("Reroll one of your numbers? (y for yes, n for no)\n");

					scanf(" %c", &yn);

					while (yn != 'y' && yn != 'n')
					{
						printf("Reroll one of your numbers? (y for yes, n for no)\n");

						scanf(" %c", &yn);
					}
				}
			}
		}
		while (combo_selected == 0)
		{
			int_option = combo_menu(dice);

			while (int_option < 1 && int_option > 13)
			{
				int_option = combo_menu(dice);
			}
			if (turn == 1)
			{
				switch (int_option)
				{
				case 1:
					if (sum1_1 == 0)
					{
						score = sum_number(dice, 5, 1);
						sum1_1 = 1;
						combo_selected = 1;
					}
					break;

				case 2:
					if (sum2_1 == 0)
					{
						score = sum_number(dice, 5, 2);
						sum2_1 = 1;
						combo_selected = 1;
					}
					break;

				case 3:
					if (sum3_1 == 0)
					{
						score = sum_number(dice, 5, 3);
						sum3_1 = 1;
						combo_selected = 1;
					}
					break;

				case 4:
					if (sum4_1 == 0)
					{
						score = sum_number(dice, 5, 4);
						sum4_1 = 1;
						combo_selected = 1;
					}
					break;

				case 5:
					if (sum5_1 == 0)
					{
						score = sum_number(dice, 5, 5);
						sum5_1 = 1;
						combo_selected = 1;
					}
					break;

				case 6:
					if (sum6_1 == 0)
					{
						score = sum_number(dice, 5, 6);
						sum6_1 = 1;
						combo_selected = 1;
					}
					break;

				case 7:
					if (three_kind_1 == 0)
					{
						score = three_of_kind(dice, 5);
						three_kind_1 = 1;
						combo_selected = 1;
					}
					break;

				case 8:
					if (four_kind_1 == 0)
					{
						score = four_of_kind(dice, 5);
						four_kind_1 = 1;
						combo_selected = 1;
					}
					break;

				case 9:
					if (full_house_1 == 0)
					{
						score = full_house(dice, 5);
						full_house_1 = 1;
						combo_selected = 1;
					}
					break;

				case 10:
					if (sm_str_1 == 0)
					{
						score = small_straight(dice, 5);
						sm_str_1 = 1;
						combo_selected = 1;
					}
					break;

				case 11:
					if (lg_str_1 == 0)
					{
						score = large_straight(dice, 5);
						lg_str_1 = 1;
						combo_selected = 1;
					}
					break;

				case 12:
					score = yahtzee(dice, 5);
					combo_selected = 1;
					break;

				case 13:
					if (chance_1 == 0)
					{
						score = chance(dice, 5);
						chance_1 = 1;
						combo_selected = 1;
					}
					break;
				}
			}
			if (turn == 2)
			{
				switch (int_option)
				{
				case 1:
					if (sum1_2 == 0)
					{
						score = sum_number(dice, 5, 1);
						sum1_2 = 1;
						combo_selected = 1;
					}
					break;

				case 2:
					if (sum2_2 == 0)
					{
						score = sum_number(dice, 5, 2);
						sum2_2 = 1;
						combo_selected = 1;
					}
					break;

				case 3:
					if (sum3_2 == 0)
					{
						score = sum_number(dice, 5, 3);
						sum3_2 = 1;
						combo_selected = 1;
					}
					break;

				case 4:
					if (sum4_2 == 0)
					{
						score = sum_number(dice, 5, 4);
						sum4_2 = 1;
						combo_selected = 1;
					}
					break;

				case 5:
					if (sum5_2 == 0)
					{
						score = sum_number(dice, 5, 5);
						sum5_2 = 1;
						combo_selected = 1;
					}
					break;

				case 6:
					if (sum6_2 == 0)
					{
						score = sum_number(dice, 5, 6);
						sum6_2 = 1;
						combo_selected = 1;
					}
					break;

				case 7:
					if (three_kind_2 == 0)
					{
						score = three_of_kind(dice, 5);
						three_kind_2 = 1;
						combo_selected = 1;
					}
					break;

				case 8:
					if (four_kind_2 == 0)
					{
						score = four_of_kind(dice, 5);
						four_kind_2 = 1;
						combo_selected = 1;
					}
					break;

				case 9:
					if (full_house_2 == 0)
					{
						score = full_house(dice, 5);
						full_house_2 = 1;
						combo_selected = 1;
					}
					break;

				case 10:
					if (sm_str_2 == 0)
					{
						score = small_straight(dice, 5);
						sm_str_2 = 1;
						combo_selected = 1;
					}
					break;

				case 11:
					if (lg_str_2 == 0)
					{
						score = large_straight(dice, 5);
						lg_str_2 = 1;
						combo_selected = 1;
					}
					break;

				case 12:
					score = yahtzee(dice, 5);
					combo_selected = 1;
					break;

				case 13:
					if (chance_2 == 0)
					{
						score = chance(dice, 5);
						chance_2 = 1;
						combo_selected = 1;
					}
					break;
				}
			}		
		}

		if (turn == 1)
		{
			score1 = score1 + score;
		}
		if (turn == 2)
		{
			score2 = score2 + score;
		}
		combo_selected = 0;
		score = 0;
		++pass_turn;

		printf("Player 1 score: %d\n", score1);
		printf("Player 2 score: %d\n", score2);
		system("pause");
		system("cls");
	}
	if (score1 <= 63)
	{
		score1 = score1 + 35;
	}
	if (score2 <= 63)
	{
		score2 = score2 + 35;
	}

	if (score1 > score2)
	{
		printf("Player 1 wins!!\n\n");
	}

	if (score2 > score1)
	{
		printf("Player 2 wins!!\n\n");
	}

	if (score1 == score2)
	{
		printf("Amazing!!! Its a draw!!!");
	}

	system("pause");
	system("cls");
	return 0;
}