/*
	NAME: Killian Griffin
	DATE: 2/26/20
	ASSIGNMENT: PA4
	LAB SECTION: 5
	DESCRIPTION: This program lets the user play a game called Hunt the Wumpus, where the user searches for a pot of gold while avoiding 
				 the Wumpus and various pits.
*/

#include "header.h"

int main()
{
	int restart = 0, restartNew = 0;
	char option = '\0';
	ofstream scorefile;

	srand(time(NULL));

	while (option == option) // doesnt end unless player ends the game
	{
		string name;

		cout << "Welcome to Hunt the Wumpus" << endl << endl << "Enter a name:\n";
		cin >> name;

		restartNew = 0;
		system("cls");
		while (restartNew == 0) // ends if player wants to pick a new name, player dies, player wins, or player ends the game
		{
			GameWorld map;
			map.displayPlayerPosition();
			restart = 0;
			while (restartNew == 0 && restart == 0) // ends if player wins, player dies, player chooses either restart option, or player 
			{										// ends the game
				cout << "I: Move Up\n" << "J: Move Left\n" << "K: Move Down\n" << "L: Move Right\n" << "V: Display visible vorld (-2 points)\n"
					<< "C: Display entire world (-5 points)\n" << "R: Restart with same name\n" << "N: Restart with new name\n" << "Q: End game\n\n";
				cin >> option;
				system("cls");

				switch (option) // executes appropriate functions based on the prompted inputs
				{
				case 'i': // moving up
					map.moveUp();
					map.displayPlayerPosition();
					break;

				case 'I':
					map.moveUp();
					map.displayPlayerPosition();
					break;

				case 'j': // moving left
					map.moveLeft();
					map.displayPlayerPosition();
					break;

				case 'J':
					map.moveLeft();
					map.displayPlayerPosition();
					break;

				case 'k': // moving down
					map.moveDown();
					map.displayPlayerPosition();
					break;

				case 'K':
					map.moveDown();
					map.displayPlayerPosition();
					break;

				case 'l': // moving right
					map.moveRight();
					map.displayPlayerPosition();
					break;

				case 'L':
					map.moveRight();
					map.displayPlayerPosition();
					break;

				case 'v': // displaying space adjacent to player
					map.displayVisibleWorld();
					break;

				case 'V':
					map.displayVisibleWorld();
					break;

				case 'c': // displaying entire map
					map.displayEntireWorld();
					break;

				case 'C':
					map.displayEntireWorld();
					break;

				case 'r': // restart with same name
					restart = 1;
					map.setScore(0);
					break;

				case 'R':
					restart = 1;
					map.setScore(0);
					break;

				case 'n': // restart with different name
					restartNew = 1;
					break;

				case 'N':
					restartNew = 1;
					break;

				case 'q': // exit game
					return 0;
					break;

				case 'Q':
					return 0;
					break;
				}

				if (map.amIAlive() == 0) // makes loop end if player has died
				{
					cout << "You died\n\n";
					restartNew = 1;
				}

				if (map.haveIWon() == 1) // makes loop end if player has won
				{
					cout << "You found the gold!\n";
					scorefile.open("score.txt");
					scorefile << name << endl << map.getScore();
					restartNew = 1;
				}
			}
		}
	}
}

