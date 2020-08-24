/*
	NAME: Killian Griffin
	DATE: 12/3/19

	DESCRIPTION: We are writing a program that executes a variety of functions with different tasks
*/

#include "header.h"

int main(void)
{
	int ordered_num1[100] = { 1, 2, 3, 4, 5, 6, 7 }, ordered_num2[100] = { 1, 4, 5, 7 }, target_index = -1, palendrome_size = 0;
	int palendrome = 0, num = 0, sum_prime = 0, greatest_char = 0;
	char str_1[100] = { '\0' }, str_2[100] = { '\0' }, str_3[100] = { '\0' };
	char str_dest[100] = { '\0' }, str_source[100] = { '\0' }, str_palendrome[100] = { '\0' }, c = '\0';
	Occurrences array_occ[100];

	printf("Enter a word: \n");
	fgets(str_dest, 100, stdin);
	printf("Enter a word to put on the end of the last word: \n");
	fgets(str_source, 100, stdin);
	
	my_str_n_cat(str_dest, str_source);

	printf("%s\n", str_dest);

	system("pause");
	system("cls");

	for (int index = 0; ordered_num1[index] != NULL; ++index)
	{
		printf("%d ", ordered_num1[index]);
	}
	printf("\n");
	target_index = bianary_search(ordered_num1, 3);
	if (target_index == -1)
	{
		printf("3 is not in this set of numbers.\n\n");
	}
	else
	{
		printf("3 is in this set of numbers, at position %d.\n\n", target_index + 1);
	}

	for (int index = 0; ordered_num2[index] != NULL; ++index)
	{
		printf("%d ", ordered_num2[index]);
	}
	printf("\n");
	target_index = bianary_search(ordered_num2, 3);
	if (target_index == -1)
	{
		printf("3 is not in this set of numbers.\n\n");
	}
	else
	{
		printf("3 is in this set of numbers, at position %d", target_index + 1);
	}
	system("pause");
	system("cls");

	printf("Write a word: \n");
	fgets(&str_1, 100, stdin);
	printf("Write another word: \n");
	fgets(&str_2, 100, stdin);
	printf("Write another word: \n");
	fgets(&str_3, 100, stdin);

	char array[10] = { str_1, str_2, str_3 };
	bubble_sort(&array, 3);

	printf("In order: \n%s%s%s", str_1, str_2, str_3);
	system("pause");
	system("cls");

	printf("Enter a word: ");
	fgets(&str_palendrome, 100, stdin);
	while (str_palendrome[palendrome_size] != '\n')
	{
		++palendrome_size;
	}

	palendrome = is_palendrome(&str_palendrome, palendrome_size, 0);
	if (palendrome == 1)
	{
		printf("This word is a palendrome\n");
	}
	if (palendrome == 0)
	{
		printf("This word is not a palendrome\n");
	}
	system("pause");
	system("cls");

	printf("Enter a number: ");
	scanf("%d", &num);
	sum_prime = sum_primes(num);
	printf("The sum of this number's primes is %d\n", sum_prime);
	system("pause");
	system("cls");

	char str_occ[] = "occurrences";

	printf("%s\n", str_occ);
	printf("Type a letter to search for in this word: \n");
	scanf(" %c", &c);
	greatest_char = maximum_occurrences(&str_occ, array_occ, &num, &c);

	printf("The frequency of the given letter is %lf, and the letter that occurs the most is %c", array_occ[num].frequency, array_occ[greatest_char].character);
	
	return 0;
}
