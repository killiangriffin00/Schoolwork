/*
	Name: Killian Griffin
	Date: 10/15/19

	Description: We are making a program that lets the user play the game Yahtzee.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <time.h>

int print_menu(void);
int print_rules(void);
int play_game(void);
int roll_dice(int dice[], int size);
int roll_spec_die(int dice[], int index);
int sum_number(int dice[], int size, int number);
int three_of_kind(int dice[], int size);
int four_of_kind(int dice[], int size);
int full_house(int dice[], int size);
int chance(int dice[]);
int large_straight(int dice[], int size);
int small_straight(int dice[], int size);
int yahtzee(int dice[], int size);
int combo_menu(int dice[]);