/*
	Name: Killian Griffin
	Date: 9/6/19

	Description: We are creating a program that will take user-inputted numbers and apply them to equations for results.

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <math.h>

#define PI 3.1415;

int main(void)
{
	int resistance = 0, r1 = 0, r2 = 0, r3 = 0, shift = 0, a = 0; // define and initialize variables
	double tax = 0, item = 0, rate = 0, length = 0, width = 0, height = 0, volume = 0, dblresistance = 0, distance = 0, x1 = 0, x2 = 0, y1 = 0, y2 = 0, y = 0, x = 0, z = 0, solution = 0;
	char plaintext_character = '\0', encoded_character = '\0';

	printf("Enter three resistor values: "); // prompt user for values
	scanf("%d%d%d", &r1, &r2, &r3);  // store imputted values
	
	resistance = r1 + r2 + r3; // compute series resistance

	printf("Series resistance = r1 + +r2 + r3 = %d + %d + %d = %d \n", r1, r2, r3, resistance); // display result
	printf("Enter price of item: "); //prompt and store values for price and rate
	scanf("%lf", &item);
	printf("Enter sales tax rate: "); 
	scanf("%lf", &rate); 

	tax = item * rate; // compute sales tax

	printf("Sales tax = item price x rate = %lf x %lf = %lf\n", item, rate, tax); // display resut

	printf("Enter length of pyramid: "); // prompt and store values for length, width, and height
	scanf("%lf", &length);
	printf("Enter width of pyramid: ");
	scanf("%lf", &width);
	printf("Enter height of pyramid: ");
	scanf("%lf", &height);

	volume = (length * width * height) / 3; // compute volume

	printf("Volume of pyramid = (length x width x height) / 3 = (%lf x %lf x %lf) /3 = %lf\n", length, width, height, volume); // display result
	printf("Enter 3 resistor values: "); // prompt and store values for resistors
	scanf("%d%d%d", &r1, &r2, &r3);

	dblresistance = 1 / ((double)1 / r1 + (double)1 / r2 + (double)1 / r3); // casting 1 as double to prevent division by 0 due to rounding

	printf("Parallel resistance = 1 / (1 / r1 + 1 / r2 + 1 / r3) = 1 / ( 1 / %d + 1 / %d + 1 / %d) = %lf\n", r1, r2, r3, dblresistance); // display result
	
	printf("Enter a character: ");
	scanf("%c", &plaintext_character);
	printf("Enter an integer: ");
	scanf("%d", &shift);

	encoded_character = (plaintext_character - 'a') + 'A' - shift;

	printf("Encoded character = (plaintext character - 'a') + 'A' - shift = (%c - 'a') + 'A' - %d = encoded_character\n");

	printf("Enter first point: "); // prompt and store values for points
	scanf("%lf%lf", &x1, &y1);
	printf("Enter second point: ");
	scanf("%lf%lf", &x2, &y2);
	
	distance = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)); // compute distance

	printf("Distance between points = ((x1 - x2)^2 + (y1 - y2)^2)^1/2 = ((%lf - %lf)^2 + (%lf - %lf)^2)^1/2 = %lf\n", x1, x2, y1, y2, distance); // display result
	printf("Enter a value for y: ");
	scanf("%lf", &y);
	printf("Enter a value for x: ");
	scanf("%lf", &x);
	printf("Enter a value for z: ");
	scanf("%lf", &z);
	printf("Enter an integer for a: ");
	scanf("%d", &a);

	solution = y / ((double)3 / (double)17) - z + x / (a % 2) + PI;

	printf("Result: %lf / (3 / 17) - %lf + %lf / (%d % 2) = %lf", y, z, x, a, solution);

	return 0;

}