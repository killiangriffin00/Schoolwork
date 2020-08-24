/*
	NAME: Killian Griffin
	DATE: 10/29/19

	DESCRIPTION: We are making a program that lets the user play the game Battleship against an A.I.

*/

#include "header.h"

int rules(void)
{

	printf("|||||||||| WELCOME TO BATTLESHIP ||||||||||\n");
	printf("rules\n");

	system("pause");
	system("cls");

	return 0;
}

int initialize(sp array[][10], int row)
{
	for (int index_y = 0; index_y < 10; ++index_y)
	{
		for (int index_x = 0; index_x < row; ++index_x)
		{
			array[index_x][index_y].x = index_x + 1;
			array[index_x][index_y].y = index_y + 1;
			array[index_x][index_y].status = '~';
		}
	}
	return 0;
}

int print_board(sp array[][10])
{
	printf("   1 2 3 4 5 6 7 8 9 10\n");
	for (int index_y = 0; index_y < 10; ++index_y)
	{
		printf("%d", index_y + 1);
		if (index_y < 9)
		{
			printf(" ");
		}
		for (int index_x = 0; index_x < 10; ++index_x)
		{
			printf(" %c", array[index_x][index_y].status);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

int valid_rand(sp array[][10], int ship, int *x, int *y, int *direction)
{
	int rand_start_x = 0, rand_start_y = 0, rand_direction = 0, exit1 = 0, vertical = 0, horizontal = 0, exit2 = 0;

	for (int valid_startpoint = 0; valid_startpoint == 0;)
	{
		horizontal = 0;
		vertical = 0;
		exit2 = 0;
		rand_start_x = (rand() % 10);
		rand_start_y = (rand() % 10);
		for (int valid_direction = 0; valid_direction == 0 && exit2 == 0;)
		{
			rand_direction = (rand() % 2);
			switch (rand_direction)
			{
			case 0:
				if (vertical == 0)
				{
					if (rand_start_y + (ship - 1) < 9)
					{
						for (int check = 0; check < ship && exit1 == 0; ++check)
						{
							if (array[rand_start_x][rand_start_y + check].status != '~')
							{
								valid_direction = 0;
								valid_startpoint = 0;
								exit1 = 1;
							}
							else
							{
								valid_direction = 1;
								valid_startpoint = 1;
							}
						}
					}
					else
					{
						valid_direction = 0;
						valid_startpoint = 0;
					}
				}
				vertical = 1;
				break;

			case 1:
				if (horizontal == 0)
				{
					if (rand_start_x + (ship - 1) < 9)
					{
						for (int check = 0; check < ship && exit1 == 0; ++check)
						{
							if (array[rand_start_x + check][rand_start_y].status != '~')
							{
								valid_direction = 0;
								valid_startpoint = 0;
								exit1 = 1;
							}
							else
							{
								valid_direction = 1;
								valid_startpoint = 1;
							}
						}
					}
					else
					{
						valid_direction = 0;
						valid_startpoint = 0;
					}
				}
				horizontal = 1;
				break;
			}
			exit1 = 0;
			if (vertical + horizontal == 2)
			{
				exit2 = 1;
			}
		}
	}

	*x = rand_start_x;
	*y = rand_start_y;
	*direction = rand_direction;
	return 0;
}

int place_ship_rand(sp array[][10], int ship, int x, int y, int direction, char ship_type)
{
	switch (direction)
	{
	case 0:
		for (int index = 0; index < ship; ++index)
		{
			array[x][y + index].status = ship_type;
		}
		break;

	case 1:
		for (int index = 0; index < ship; ++index)
		{
			array[x + index][y].status = ship_type;
		}
		break;
	}
	return 0;
}

int place_rand(sp array[][10])
{
	int carrier_x = 0, carrier_y = 0, carrier_direction = 5, sub_x = 0, sub_y = 0, sub_direction = 5, battleship_x = 0, battleship_y = 0;
	int battleship_direction = 0, cruiser_x = 0, cruiser_y = 0, cruiser_direction = 0, destroyer_x = 0, destroyer_y = 0, destroyer_direction = 0;

	valid_rand(array, 5, &carrier_x, &carrier_y, &carrier_direction);
	place_ship_rand(array, 5, carrier_x, carrier_y, carrier_direction, 'C');

	valid_rand(array, 4, &battleship_x, &battleship_y, &battleship_direction);
	place_ship_rand(array, 4, battleship_x, battleship_y, battleship_direction, 'B');

	valid_rand(array, 3, &sub_x, &sub_y, &sub_direction);
	place_ship_rand(array, 3, sub_x, sub_y, sub_direction, 'S');

	valid_rand(array, 3, &cruiser_x, &cruiser_y, &cruiser_direction);
	place_ship_rand(array, 3, cruiser_x, cruiser_y, cruiser_direction, 'R');

	valid_rand(array, 2, &destroyer_x, &destroyer_y, &destroyer_direction);
	place_ship_rand(array, 2, destroyer_x, destroyer_y, destroyer_direction, 'D');

	return 0;
}

place_ship_manual(sp array[][10], char ship_name[], char ship_type, int ship_size)
{
	int x_coord = 0, y_coord = 0, x_coord_new = 0, y_coord_new = 0, direction = 0;
	print_board(array);
	printf("Enter an x and y coordinate between 0 and 11 for your %s: ", ship_name);
	scanf("%d%d", &x_coord, &y_coord);

	while ((1 > x_coord || 1 > y_coord)||(10 < x_coord || 10 < y_coord))
	{
		printf("Enter an x and y coordinate between 0 and 11 for your %s: ", ship_name);
		scanf("%d%d", &x_coord, &y_coord);
	}

	array[x_coord - 1][y_coord - 1].status = ship_type;
	system("cls");
	for (int check = 1; check < ship_size; ++check)
	{
		print_board(array);
		printf("Enter another x and y coordinate adjacent and in line with the last %s point: ", ship_name);
		scanf("%d%d", &x_coord_new, &y_coord_new);

		while (((1 > x_coord_new || 1 > y_coord_new) || (10 < x_coord_new || 10 < y_coord_new)) || (array[x_coord_new - 1][y_coord_new - 1].status != '~') || 
			(x_coord != x_coord_new && y_coord != y_coord_new))
		{
			printf("Enter another x and y coordinate adjacent and in line with the last %s point: ", ship_name);
			scanf("%d%d", &x_coord_new, &y_coord_new);
		}
		
		if (direction == 0)
		{
			if (x_coord_new == x_coord)
			{
				direction = 1;
			}
			if (y_coord_new == y_coord)
			{
				direction = 2;
			}
		}
		switch (direction)
		{
		case 1:
			while (((array[x_coord_new - 1][y_coord_new - 1].status != '~') || (x_coord != x_coord_new && y_coord != y_coord_new)) || 
				 (y_coord_new != y_coord - 1 && y_coord_new != y_coord + 1))
			{
				printf("Enter another x and y coordinate adjacent and in line with the last %s point: ", ship_name);
				scanf("%d%d", &x_coord_new, &y_coord_new);
			}
			break;

		case 2:
			while (((array[x_coord_new - 1][y_coord_new - 1].status != '~') || (x_coord != x_coord_new && y_coord != y_coord_new)) || 
				 (x_coord_new != x_coord - 1 && x_coord_new != x_coord + 1))
			{
				printf("Enter another x and y coordinate adjacent and in line with the last %s point: ", ship_name);
				scanf("%d%d", &x_coord_new, &y_coord_new);
			}

		}
		x_coord = x_coord_new;
		y_coord = y_coord_new;
		array[x_coord_new - 1][y_coord_new - 1].status = ship_type;
		system("cls");
	}
	return 0;
}

int place_manual(sp array[][10])
{
	char carrier[] = "CARRIER", battleship[] = "BATTLESHIP", submarine[] = "SUBMARINE", cruiser[] = "CRUISER", destroyer[] = "DESTROYER";

	place_ship_manual(array, carrier, 'C', 5);
	place_ship_manual(array, battleship, 'B', 4);
	place_ship_manual(array, submarine, 'S', 3);
	place_ship_manual(array, cruiser, 'R', 3);
	place_ship_manual(array, destroyer, 'D', 2);
	return 0;
}

int ship_check(sp array[][10], char check)
{
	int no_ship = 1;
	for (int index_y = 0; index_y < 10; ++index_y)
	{
		for (int index_x = 0; index_x < 10; ++index_x)
		{
			if (array[index_x][index_y].status = check)
			{
				no_ship = 0;
			}
		}
	}
	return no_ship;
}