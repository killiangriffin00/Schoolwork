/*
	Name: Killian Griffin
	Date: 9/23/2019

	Description: We will be taking in information from a file, namely GPAs, class standings, and ages, doing various calculations using this
	data, and writing them to an output file.

*/

#include "header.h"

#include <stdio.h>

#include <math.h>

int main(void)
{
	// define and initialize all variables
	int standing1 = 0, standing2 = 0, standing3 = 0, standing4 = 0, standing5 = 0, id1 = 0, id2 = 0, id3 = 0, id4 = 0, id5 = 0, v = 0;
	double GPA1 = 0, GPA2 = 0, GPA3 = 0, GPA4 = 0, GPA5 = 0, age1 = 0, age2 = 0, age3 = 0, age4 = 0, age5 = 0, GPA_sum = 0, stand_sum = 0, age_sum = 0, GPA_mean = 0, stand_mean = 0, age_mean = 0, GPA_var = 0, GPA_stdev = 0, GPA_min = 0, GPA_max = 0, dev1 = 0, dev2 = 0, dev3 = 0, dev4 = 0, dev5 = 0;
	FILE *infile = NULL, *outfile = NULL; //define and initialize files

	infile = fopen("infile.dat", "r"); // open input file

	id1 = read_integer(infile); // read data from input file and store with variables
	GPA1 = read_double(infile);
	standing1 = read_integer(infile);
	age1 = read_double(infile);

	id2 = read_integer(infile);
	GPA2 = read_double(infile);
	standing2 = read_integer(infile);
	age2 = read_double(infile);

	id3 = read_integer(infile);
	GPA3 = read_double(infile);
	standing3 = read_integer(infile);
	age3 = read_double(infile);

	id4 = read_integer(infile);
	GPA4 = read_double(infile);
	standing4 = read_integer(infile);
	age4 = read_double(infile);

	id5 = read_integer(infile);
	GPA5 = read_double(infile);
	standing5 = read_integer(infile);
	age5 = read_double(infile);
	
	infile = fclose(infile); // close input file

	GPA_sum = calc_sum(GPA1, GPA2, GPA3, GPA4, GPA5); // calculate sum of GPAs
	stand_sum = calc_sum(standing1, standing2, standing3, standing4, standing5); // calculate sum of class standings
	age_sum = calc_sum(age1, age2, age3, age4, age5); // calculate sum of ages

	GPA_mean = calc_mean(GPA_sum); // calculate mean of GPAs
	stand_mean = calc_mean(stand_sum); // calculate mean of class standings
	age_mean = calc_mean(age_sum); // claculate mean of ages

	dev1 = calc_deviation(GPA_mean, GPA1); // calculate deviation form mean of all GPAs
	dev2 = calc_deviation(GPA_mean, GPA2);
	dev3 = calc_deviation(GPA_mean, GPA3);
	dev4 = calc_deviation(GPA_mean, GPA4);
	dev5 = calc_deviation(GPA_mean, GPA5);

	GPA_var = calc_variance(dev1, dev2, dev3, dev4, dev5); // calculate variance of GPAs

	GPA_stdev = calc_stdeviation(GPA_var); // calculate standard deviation of data set

	GPA_min = find_min(GPA1, GPA2, GPA3, GPA4, GPA5); // find the minimum GPA
	GPA_max = find_max(GPA1, GPA2, GPA3, GPA4, GPA5); // find the maximum GPA

	outfile = fopen("outfile.dat", "w"); // open the output file

	v = print_double(outfile, GPA_mean); // write data to output file
	v = print_double(outfile, stand_mean);
	v = print_double(outfile, age_mean);
	v = print_double(outfile, GPA_stdev);
	v = print_double(outfile, GPA_min);
	v = print_double(outfile, GPA_max);

	fclose(outfile); // close output file

	printf("%lf", GPA_mean);

	return 0;
}