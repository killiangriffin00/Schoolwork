/*
	Name: Killian Griffin
	Date: 9/23/2019

	Description: We will be taking in information from a file, namely GPAs, class standings, and ages, doing various calculations using this
	data, and writing them to an output file.

*/

#include "header.h"

#include <stdio.h>

#include <math.h>

double read_double(FILE *infile)
{
	double number = 0;

	fscanf(infile, "%lf", &number);

	return number;
}

int read_integer(FILE *infile)
{
	int number = 0;

	fscanf(infile, "%d", &number);

	return number;
}

double calc_sum(double n1, double n2, double n3, double n4, double n5)
{
	double sum = 0;

	sum = n1 + n2 + n3 + n4 + n5;

	return sum;
}

double calc_mean(double GPA_sum)
{
	double mean = 0;

	mean = GPA_sum / 5;

	return mean;
}

double calc_deviation(double GPA_mean, double GPA)
{
	double deviation;

	deviation = GPA - GPA_mean;

	return deviation;
}

double calc_variance(double dev1, double dev2, double dev3, double dev4, double dev5)
{
	double variance;

	variance = (pow(dev1, 2) + pow(dev2, 2) + pow(dev3, 2) + pow(dev4, 2) + pow(dev5, 2));

	return variance;
}

double calc_stdeviation(double variance)
{
	double stdeviation = 0;

	stdeviation = sqrt(variance);

	return stdeviation;
}

double find_min(double GPA1, double GPA2, double GPA3, double GPA4, double GPA5)
{
	double minimum = GPA1;
	
	if (minimum > GPA2)
	{
		minimum = GPA2;
	}

	if (minimum > GPA3)
	{
		minimum = GPA3;
	}

	if (minimum > GPA4)
	{
		minimum = GPA4;
	}

	if (minimum > GPA5)
	{
		minimum = GPA5;
	}

	return minimum;
}

double find_max(double GPA1, double GPA2, double GPA3, double GPA4, double GPA5)
{
	double maximum = GPA1;

	if (maximum < GPA2)
	{
		maximum = GPA2;
	}

	if (maximum < GPA3)
	{
		maximum = GPA3;
	}

	if (maximum < GPA4)
	{
		maximum = GPA4;
	}

	if (maximum < GPA5)
	{
		maximum = GPA5;
	}

	return maximum;
}

double print_double(FILE* outfile, double n)
{
	fprintf(outfile, "%lf\n", n);

	return 0;
}