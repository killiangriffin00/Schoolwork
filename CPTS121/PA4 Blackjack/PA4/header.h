/*
	Name: Killian Griffin
	Date: 10/5/19

	Description: We are making a program that allows the user to play a game of blackjack dice with up to 5 players.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <math.h>

#include <stdlib.h>

#include <time.h>

int menu(void);
int print_rules(void);
double get_balance(void);
int play_game(double balance);
double get_wager(int player_count, double playerbal, double wager);
int roll_die(void);
int calc_sum_dice(int die, int score);