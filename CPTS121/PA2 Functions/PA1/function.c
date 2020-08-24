/*
	Name: Killian Griffin
	Date: 9/6/19

	Description: We are creating a program that will take user-inputted numbers and apply them to equations for results.

*/

#include "header.h"

/************************************************************
* Function: resistcalc()                                    *
* Date Created: 9/13/19                                     *
* Date Last Modified: 9/13/19                               *
* Description: Calculates resistance given 3 resistors      *
* Input parameters: Integers                                *
* Returns: Resistance                                       *
* Preconditions: Start of the program.                      *
* Postconditions: Resistance output                         *
*************************************************************/

int resistcalc(int r1, int r2, int r3)
{
	int resistance = 0; // define variable for resistance 
	
	resistance = r1 + r2 + r3; // compute series resistance
	
	return resistance;
}

/*************************************************************
* Function: salestaxcalc()                                   *
* Date Created: 9/13/19                                      *
* Date Last Modified: 9/13/19                                *
* Description: Calculates ammount of sales tax given price   *
* of an item and sales tax rate                              *
* Input parameters: Floating-point value                     *
* Returns: Ammount of sales tax                              *
* Preconditions: Start of the program.                       *
* Postconditions: Sales tax output                           *
*************************************************************/

int salestaxcalc(double item, double rate)
{
	double tax = 0; // define variable for tax
	
	tax = item * rate; // compute sales tax

	return tax;
}

/*************************************************************
* Function: volumecalc()                                     *
* Date Created: 9/13/19                                      *
* Date Last Modified: 9/13/19                                *
* Description: Calculates the volume of a pyramid given a    * 
* length, width, and height                                  *
* Input parameters: Floating-point value                     *
* Returns: Volume of pyramid                                 *
* Preconditions: Start of the program.                       *
* Postconditions: Volume output                              *
*************************************************************/

int volumecalc(double length, double width, double height)
{
	double volume = 0; //define variable for volume

	volume = (length * width * height) / 3; // compute volume

	return volume;
}

/*************************************************************
* Function: dblresistcalc()                                  *
* Date Created: 9/13/19                                      *
* Date Last Modified: 9/13/19                                *
* Description: Calculates resistance given three resistors   *
* Input parameters: Integers                                 *
* Returns: Floating-point resistance                         *
* Preconditions: Start of the program.                       *
* Postconditions: Floating-point resistance output           *
*************************************************************/

int dblresistcalc(int r1, int r2, int r3)
{

	double dblresistance = 0; // define variable for resistance

	dblresistance = 1 / ((double)1 / r1 + (double)1 / r2 + (double)1 / r3); //compute resistance, casting 1 as double to prevent division by 0 due to rounding

	return dblresistance;
}

/*************************************************************
* Function: charcalc()                                       *
* Date Created: 9/13/19                                      *
* Date Last Modified: 9/13/19                                *
* Description: Calculates an encoded character given a       *
* plaintext character and a shift value                      *
* Input parameters: A character and an integer               *
* Returns: Encoded character                                 *
* Preconditions: Start of the program.                       *
* Postconditions: Character output                           *
*************************************************************/

int charcalc(char plaintextchar, int shift)
{
	char encodedchar = 0; // define variable for character
	
	encodedchar = (plaintextchar - 'a') + 'A' - shift; // compute encoded character

	return encodedchar;
}

/*************************************************************
* Function: pointcalc()                                      *
* Date Created: 9/13/19                                      *
* Date Last Modified: 9/13/19                                *
* Description: Calculates the distance between two points    *
* given x and y values for each point                        *
* Input parameters: Floating-point values                    *
* Returns: Distance between points                           *
* Preconditions: Start of the program.                       *
* Postconditions: Distance output                            *
*************************************************************/

int pointcalc(double x1, double y1, double x2, double y2)
{
	double distance = 0; // define variable for distance

	distance = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)); // compute distance

	return distance;
}

/*************************************************************
* Function: equcalc()                                        *
* Date Created: 9/13/19                                      *
* Date Last Modified: 9/13/19                                *
* Description: General equation                              *
* Input parameters: Three floating-point values and an       *
* integer                                                    *
* Returns: Solution                                          *
* Preconditions: Start of the program.                       *
* Postconditions: Solution output                            *
*************************************************************/

int equcalc(double y, double x, double z, int a)
{
	double solution = 0; // define variable for solution
	
	solution = y / ((double)3 / (double)17) - z + x / (a % 2) + PI; // compute solution

	return solution;
}