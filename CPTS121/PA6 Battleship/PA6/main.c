/*
	NAME: Killian Griffin
	DATE: 10/29/19

	DESCRIPTION: We are making a program that lets the user play the game Battleship against an A.I.

*/

#include "header.h"

int main(void)
{
	sp board_player[10][10], board_ai[10][10], board_print[10][10];
	int option = 0, turn = 2, win = 0, x_strike = 0, y_strike = 0, carrier = 0, battleship = 0, submarine = 0, cruiser = 0, destroyer = 0;
	int carrier_ai = 0, battleship_ai = 0, submarine_ai = 0, cruiser_ai = 0, destroyer_ai = 0, is_sunk = 0, win_ai = 0, win_player = 0;
	int ship_detected = 0, ship_dx = 0, ship_dy = 0, ship_direct = 0, rand_strike = 0, found_rand_strike = 0;
	char carrier_str[] = "CARRIER", battleship_str[] = "BATTLESHIP", submarine_str[] = "SUBMARINE", cruiser_str[] = "CRUISER";
	char destroyer_str[] = "DESTROYER", check = "\0";
	FILE* output = NULL;

	rules();
	initialize(board_ai, 10);
	initialize(board_player, 10);
	initialize(board_print, 10);
	srand(time(NULL));

	output = fopen("output.dat", "w");

	printf("Choose an option: \n");
	printf("1. Randomly select ship placement\n");
	printf("2. Manually select ship placement\n");

	scanf("%d", &option);
	system("cls");
	if (option != 1 && option != 2)
	{
		printf("Choose an option: \n");
		printf("1. Randomly select ship placement\n");
		printf("2. Manually select ship placement\n");

		scanf("%d", &option);
		system("cls");
	}

	if (option == 1)
	{
		place_rand(board_player);
	}

	if (option == 2)
	{
		place_manual(board_player);
	}

	place_rand(board_ai);
	printf("Player 2's board has been randomly generated\n");
	turn = rand() % 2;
	if (turn == 0)
	{
		printf("Player 1 has been randomly selected to go first\n");
	}
	if (turn == 1)
	{
		printf("Player 2 has been randomly selected to go first\n");
	}
	for (int turn_number = 1; win == 0; ++turn_number)
	{
		switch (turn)
		{
		case 0:
			print_board(board_print);
			printf("\n");
			print_board(board_player);

			printf("Choose a coordinate to strike: ");
			scanf("%d%d", &x_strike, &y_strike);

			while (board_print[x_strike - 1][y_strike - 1].status != '~')
			{
				printf("Choose a new coordinate to strike: ");
				scanf("%d%d", &x_strike, &y_strike);
			}
			system("cls");

			if (board_ai[x_strike - 1][y_strike - 1].status == '~')
			{
				board_print[x_strike - 1][y_strike - 1].status = 'O';
				printf("It's a miss...\n");
				fprintf(output, "Turn %d:\nPlayer 1 struck coordinate (%d, %d). They got a miss\n\n", turn_number, x_strike, y_strike);
			}
			else
			{
				if (board_ai[x_strike - 1][y_strike - 1].status != '~')
				{
					board_print[x_strike - 1][y_strike - 1].status = 'X';
					printf("It's a hit!\n");
					fprintf(output, "Turn %d:\nPlayer 1 struck coordinate (%d, %d). They got a hit", turn_number, x_strike, y_strike);
					check = board_ai[x_strike - 1][y_strike - 1].status;
					is_sunk = ship_check(board_ai, check);
					if (is_sunk == 1)
					{
						switch (check)
						{
						case 'C':
							printf("You sunk their CARRIER!\n");
							carrier_ai = 1;
							fprintf(output, " and sunk Player 2's CARRIER");
							is_sunk = 0;
							break;

						case 'B':
							printf("You sunk their BATTLESHIP!\n");
							battleship_ai = 1;
							fprintf(output, " and sunk Player 2's BATTLESHIP");
							is_sunk = 0;
							break;

						case 'S':
							printf("You sunk their SUBMARINE!\n");
							submarine_ai = 1;
							fprintf(output, " and sunk Player 2's SUBMARINE");
							is_sunk = 0;
							break;

						case 'R':
							printf("You sunk their CRUISER!\n");
							cruiser_ai = 1;
							fprintf(output, " and sunk Player 2's CRUISER");
							is_sunk = 0;
							break;

						case 'D':
							printf("You sunk their DESTROYER!\n");
							destroyer_ai = 1;
							fprintf(output, " and sunk Player 2's DESTROYER");
							is_sunk = 0;
							break;
						}
						fprintf(output, "\n\n");
					}
					if (destroyer_ai + cruiser_ai + submarine_ai + battleship_ai + cruiser_ai == 5)
					{
						win = 1;
						win_player = 1;
					}
				}
			}
			turn = 1;
			break;

		case 1:
			if (ship_detected == 0)
			{
				x_strike = rand() % 10;
				y_strike = rand() % 10;

				while (board_player[x_strike][y_strike].status == 'X' || board_player[x_strike][y_strike].status == 'O')
				{
					x_strike = rand() % 10;
					y_strike = rand() % 10;
				}
			}
			if (ship_detected == 1)
			{
				switch (ship_direct)
				{
				case 0:
					while (found_rand_strike == 0)
					{
						rand_strike = rand() % 4;
						switch (rand_strike)
						{
						case 0:
							if (ship_dy - 1 > -1)
							{
								x_strike = ship_dx;
								y_strike = ship_dy - 1;
								found_rand_strike = 1;
							}
							break;

						case 1:
							if (ship_dy + 1 < 10)
							{
								x_strike = ship_dx;
								y_strike = ship_dy + 1;
								found_rand_strike = 1;
							}
							break;

						case 2:
							if (ship_dx - 1 > -1)
							{
								x_strike = ship_dx - 1;
								y_strike = ship_dy;
								found_rand_strike = 1;
							}
							break;

						case 3:
							if (ship_dx + 1 < 10)
							{
								x_strike = ship_dx + 1;
								y_strike = ship_dy;
								found_rand_strike = 1;
							}
							break;
						}
					}
					found_rand_strike = 0;
					break;
				case 1:
					while (found_rand_strike == 0)
					{
						rand_strike = rand() % 2;
						switch (rand_strike)
						{
						case 0:
							for (int index = 0; board_player[ship_dx][ship_dy + index].status != '~'; ++index)
							{
								if (ship_dy + index < 10 && board_player[ship_dx][ship_dy + index].status != 'O')
								{
									y_strike = index + ship_dy;
									found_rand_strike = 1;
								}
							}
							break;
						case 1:
							for (int index = 0; board_player[ship_dx][ship_dy - index].status != '~'; ++index)
							{
								if (ship_dy - index > -1 && board_player[ship_dx][ship_dy - index].status != 'O')
								{
									y_strike = ship_dy - index;
									found_rand_strike = 1;
								}
							}
							break;
						}

					}
					found_rand_strike = 0;
					break;

				case 2:
					while (found_rand_strike == 0)
					{
						rand_strike = rand() % 2;
						switch (rand_strike)
						{
						case 0:
							for (int index = 0; board_player[ship_dx + index][ship_dy].status != '~'; ++index)
							{
								if (ship_dx + index < 10 && board_player[ship_dx + index][ship_dy].status != 'O')
								{
									x_strike = index + ship_dx;
									found_rand_strike = 1;
								}
							}
							break;
						case 1:
							for (int index = 0; board_player[ship_dx - index][ship_dy].status != '~'; ++index)
							{
								if (ship_dx - index > -1 && board_player[ship_dx - index][ship_dy].status != 'O')
								{
									x_strike = ship_dx - index;
									found_rand_strike = 1;
								}
							}
							break;
						}

					}
					found_rand_strike = 0;
					break;
				
				}
			}
			if (board_player[x_strike][y_strike].status == '~')
			{
				board_player[x_strike][y_strike].status = 'O';
				printf("Player 2 struck coordinate (%d, %d) and missed your ships\n", x_strike + 1, y_strike + 1);
				fprintf(output, "Turn %d:\nPlayer 2 struck coordinate (%d, %d). They got a miss\n\n", turn_number, x_strike + 1, y_strike + 1);
			}
			else
			{
				if (board_player[x_strike][y_strike].status != '~')
				{
					board_player[x_strike][y_strike].status = 'X';
					printf("Player 2 got a hit on (%d, %d)!\n", x_strike + 1, y_strike + 1);
					fprintf(output, "Turn %d:\nPlayer 2 struck coordinate (%d, %d). They got a hit", turn_number, x_strike + 1, y_strike + 1);

					ship_dx = x_strike;
					ship_dy = y_strike;
					if (ship_direct == 0 && ship_detected == 1)
					{
						switch (rand_strike)
						{
						case 0:
							ship_direct = 1;
							break;
						case 1:
							ship_direct = 1;
							break;
						case 2:
							ship_direct = 2;
							break;
						case 3:
							ship_direct = 2;
							break;
						}
					}
					ship_detected = 1;

					check = board_ai[x_strike - 1][y_strike - 1].status;
					is_sunk = ship_check(board_ai, check);
					if (is_sunk == 1)
					{
						switch (check)
						{
						case 'C':
							printf("They sunk your CARRIER!\n");
							carrier_ai = 1;
							fprintf(output, " and sunk Player 1's CARRIER");
							ship_detected = 0;
							ship_direct = 0;
							is_sunk = 0;
							break;

						case 'B':
							printf("They sunk your BATTLESHIP!\n");
							battleship_ai = 1;
							fprintf(output, " and sunk Player 1's BATTLESHIP");
							ship_detected = 0;
							ship_direct = 0;
							is_sunk = 0;
							break;

						case 'S':
							printf("You sunk their SUBMARINE!\n");
							submarine_ai = 1;
							fprintf(output, " and sunk Player 1's SUBMARINE");
							ship_detected = 0;
							ship_direct = 0;
							is_sunk = 0;
							break;

						case 'R':
							printf("They sunk your CRUISER!\n");
							cruiser_ai = 1;
							fprintf(output, " and sunk Player 1's CRUISER");
							ship_detected = 0;
							ship_direct = 0;
							is_sunk = 0;
							break;

						case 'D':
							printf("They sunk your DESTROYER!\n");
							destroyer_ai = 1;
							fprintf(output, " and sunk Player 1's DESTROYER");
							ship_detected = 0;
							ship_direct = 0;
							is_sunk = 0;
							break;
						}
					}
					fprintf(output, "\n\n");
					if (destroyer + cruiser + submarine + battleship + cruiser == 5)
					{
						win = 1;
						win_ai = 1;
					}
				}
			}
		turn = 0;
		break;
		}
	}
	if (win_ai == 1)
	{
		printf("Player 2 wins!\n");
	}
	if (win_player == 1)
	{
		printf("Player 1 wins!\n");
	}
	return 0;
}