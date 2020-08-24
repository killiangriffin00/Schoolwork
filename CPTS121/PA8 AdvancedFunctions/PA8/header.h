/*
	NAME: Killian Griffin
	DATE: 12/3/19

	DESCRIPTION: We are writing a program that executes a variety of functions with different tasks
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct occurrences
{
	int num_occurrences;
	double frequency;
	char character;
}Occurrences;

char my_str_n_cat(char destination[], char source[]);
int bianary_search(int sorted[], int target);
void bubble_sort(char array[], int num);
int is_palendrome(char string[], int size, int start);
int sum_primes(int n);
int maximum_occurrences(char string[], Occurrences array[], int* index_char, char* c);