/*
	Name: Killian Griffin
	Date: 9/23/2019

	Description: We will be taking in information from a file, namely GPAs, class standings, and ages, doing various calculations using this
	data, and writing them to an output file.

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <math.h>

double read_double(FILE *infile);

int read_integer(FILE *infile);

double calc_sum(double n1, double n2, double n3, double n4, double n5);

double calc_mean(double GPA_sum);

double calc_deviation(double GPA_mean, double GPA);

double calc_variance(double dev1, double dev2, double dev3, double dev4, double dev5);

double calc_stdeviation(double GPA_var);

double find_max(double number1, double number2, double number3, double number4, double number5);

double find_min(double number1, double number2, double number3, double number4, double number5);

double print_double(FILE *outfile, double number);