/*
	NAME: Killian Griffin
	DATE: 12/3/19

	DESCRIPTION: We are writing a program that executes a variety of functions with different tasks
*/

#include "header.h"

char my_str_n_cat(char destination[], char source[])
{
	int end = 0; // marks the end of the destination array
	char copy = 'a';

	for (int index = 0; copy != '\n'; ++index) // ends the loop once it finds '\n'
	{
		end = index;
		copy = destination[index];
	}

	for (int index = 0; source[index] != '\n'; ++index) // appends source array to the end of destination until it encounters '\n'
	{
		destination[end] = source[index];
		++end;
	}
	destination[end] = NULL; // puts a null character at the end so it is a proper string

	return 0;
}

int bianary_search(int sorted[], int target)
{
	int left = 1, right = 0, mid = 0, targetindex = -1, count = 0, found = 0;

	while (sorted[count] != NULL) // finds the numbers of items in the array
	{
		++count;
	}
	left = 0;
	right = count;
	while (found == 0 && left <= right) 
	{
		mid = left + ((right - left) / 2); // midpoint between left and right bound
		
		if (sorted[mid] == target) // condition for when target number is found
		{
			found = 1; // ends the loop
			targetindex = mid; // sets the return index to correspond with the found number 
		}
		if (sorted[mid] < target) // conditiion for when target is to the left of the midpoint
		{
			left = mid + 1;
		}
		if (sorted[mid] > target) // condition for when target is to the right of the midpoint
		{
			right = mid - 1;
		}
	}
	return targetindex;
}

void bubble_sort(char array[], int num)
{
	int U = num, C = 0, temp = 0;

	while (U > 1) // ends once U is at the final value
	{
		C = 0;
		while (C <= U)
		{
			if (array[C] < array[C - 1])
			{
				temp = array[C];
				array[C] = array[C - 1];
				array[C - 1] = temp;
			}
			++C;
		}
		--U;
	}
}

int is_palendrome(char string[], int size, int start)
{
	if (string[start] == string[size - 1])
	{
		if (string[start] >= string[size - 1])
		{
			return 1;
		}
	}
	else
	{
		return 0;
	}
	if (is_palendrome(string, size - 2, start + 1) == 1)
	{
		return 1;
	}
	if (is_palendrome(string, size - 2, start + 1) == 0)
	{
		return 0;
	}
}

int sum_primes(int n)
{
	if (n <= 2)
	{
		return 0;
	}
	for (int check = 2; check == check; ++check)
	{
		if (check == n)
		{
			return sum_primes(n - 1) + n;
		}

		if (n / check == (double)n / check)
		{
			return sum_primes(n - 1);
		}
	}
}

int maximum_occurrences(char string[], Occurrences array[], int* index_char, char *c)
{
	double amount_char = 0;
	int amount_spec = 0, used = 0, space = 0, most_index = 0, given_c_index = 0;
	char comp_char = '\0', used_char[30] = { '\0' };

	for (int index = 0; string[index] != NULL; ++index)
	{
		if (string[index] == *c)
		{
			++amount_spec;
		}
		++amount_char;
	}
	for (int index1 = 0; string[index1] != NULL; ++index1)
	{
		comp_char = string[index1];
		for (int index = 0; used_char[index] != NULL; ++index)
		{
			if (comp_char == used_char[index])
			{
				used = 1;
			}
		}
		if (used == 0)
		{
			array[index1].num_occurrences = 1;
			for (int index2 = index1 + 1; string[index2] != NULL; ++index2)
			{
				if (comp_char == string[index2])
				{
					++array[space].num_occurrences;

					used_char[space] = comp_char;
					if (comp_char == *c)
					{
						*index_char = space;
					}
				}
			}
			array[space].frequency = array[space].num_occurrences / amount_char;
			array[space].character = comp_char;
			++space;
		}
		used = 0;
	}
	for (int index = 0; array[index].num_occurrences != NULL; ++index)
	{
		if (array[most_index].num_occurrences < array[index].num_occurrences)
		{
			most_index = index;
		}
	}

	return most_index;
}

