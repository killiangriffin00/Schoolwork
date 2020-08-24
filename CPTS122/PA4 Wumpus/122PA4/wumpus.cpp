/*
	NAME: Killian Griffin
	DATE: 2/26/20
	ASSIGNMENT: PA4
	LAB SECTION: 5
	DESCRIPTION: This program lets the user play a game called Hunt the Wumpus, where the user searches for a pot of gold while avoiding
				 the Wumpus and various pits.
*/

#include "header.h"

// Function: GameWorld (constructor)
// Class: GameWorld
// Description: Constructs a game world for the user to explore using random generation of pitfalls, 
//              gold, wumpus, and player position 

GameWorld::GameWorld()
{
	int pits = (rand() % 5) + 5, pitWorld = 0, wumpus = 0, gold = 0, player = 0; // Variables are used to exit loops when items are randomly
																				 // placed. Ammount of pits in the world is a randomly 
																				 // generated number between 5 and 10
	for (int index1 = 0; index1 < 5; ++index1) // initialization loop for world array
	{
		for (int index2 = 0; index2 < 5; ++index2)
		{
			world[index1][index2] = ' ';
		}
	}

	while (pitWorld < pits) // executed for as long as the present pits are less than the random number of pits to be placed
	{
		for (int index1 = 0; index1 < 5 && pitWorld < pits; ++index1) // places pits at random throughout the 2d array
		{
			for (int index2 = 0; index2 < 5 && pitWorld < pits; ++index2)
			{
				if (rand() % 5 == 4 && world[index1][index2] == ' ')
				{
					world[index1][index2] = 'P';
					++pitWorld;
				}
			}
		}
	}

	for (int index1 = 0; !wumpus; ++index1) // places the wumpus at random within the 2d array
	{
		for (int index2 = 0; !wumpus && index2 < 5; ++index2)
		{
			if (rand() % 25 == 24 && world[index1][index2] == ' ')
			{
				world[index1][index2] = 'W';
				wumpus = 1;
			}
		}
		if (index1 == 4)
		{
			index1 = 0;
		}
	}

	for (int index1 = 0; !gold; ++index1) // places gold at random within the 2d array
	{
		for (int index2 = 0; !gold && index2 < 5; ++index2)
		{
			if (rand() % 25 == 24 && world[index1][index2] == ' ')
			{
				world[index1][index2] = 'G';
				gold = 1;
			}
		}
		if (index1 == 4)
		{
			index1 = 0;
		}
	}

	for (int index1 = 0; !player; ++index1) // places player at random within the 2d array
	{
		for (int index2 = 0; !player && index2 < 5; ++index2)
		{
			if (rand() % 25 == 24 && world[index1][index2] == ' ')
			{
				world[index1][index2] = 'U';
				player = 1;
				playerPositionX = index2;
				playerPositionY = index1;
			}
		}
		if (index1 == 4)
		{
			index1 = 0;
		}
	}
	strncpy(worldInitial[0], world[0], 5); // 2d array is copied to the array representing the initial position of everything
	strncpy(worldInitial[1], world[1], 5);
	strncpy(worldInitial[2], world[2], 5);
	strncpy(worldInitial[3], world[3], 5);
	strncpy(worldInitial[4], world[4], 5);
}

// Function: setScore
// Class: GameWorld
// Description: Takes a value as an argument and sets the score in the object equal to that value

int GameWorld::setScore(int newScore)
{
	score = newScore;
	return 0;
}

// Function: getScore
// Class: GameWorld
// Description: Outputs the value of the score stored in the object

int GameWorld::getScore()
{
	return score;
}

// Function: displayEntireWorld
// Class: GameWorld
// Description: displays the entire game world to the output window and deducts 5 points from the score

void GameWorld::displayEntireWorld()
{
	for (int index1 = 0; index1 < 5; ++index1)
	{
		for (int index2 = 0; index2 < 5; ++index2)
		{
			cout << " " << world[index1][index2] << " ";
		}
		cout << endl;
	}
	score = score - 5;
}

// Function: displayVisibleWorld
// Class: GameWorld
// Description: displays only the area adjacent to the player to the output window and deducts 2 points from the score

void GameWorld::displayVisibleWorld()
{
	for (int index1 = 0; index1 < 5; ++index1)
	{
		for (int index2 = 0; index2 < 5; ++index2)
		{
			if (((index2 - 1 == playerPositionX || index2 + 1 == playerPositionX) || index2 == playerPositionX) &&
				(index1 == playerPositionY || (index1 + 1 == playerPositionY || index1 - 1 == playerPositionY))) // only if both indexes 
			{																									 // are adjacent to the
				cout << " " << world[index1][index2] << " ";													 // player
			}
			else
				cout << "   ";
		}
		cout << endl;
	}
	score = score - 2;
}

// Function: displayPlayerPosition
// Class: GameWorld
// Description: displays only the players position in the world to the output window
//     

void GameWorld::displayPlayerPosition()
{
	for (int index1 = 0; index1 < 5; ++index1)
	{
		for (int index2 = 0; index2 < 5; ++index2)
		{
			if (index1 == playerPositionY && index2 == playerPositionX)
			{
				cout << " " << world[index1][index2] << " ";
			}
			else
				cout << "   ";
		}
		cout << endl;
	}
}

// Function: moveUp
// Class: GameWorld
// Description: moves the character up on the board and adds 5 points to the score

int GameWorld::moveUp()
{
	if (playerPositionY != 0)
	{
		world[playerPositionY][playerPositionX] = ' ';
		world[playerPositionY - 1][playerPositionX] = 'U';
		--playerPositionY;
		score += 5;
		return 1;
	}
	else
	return 0;
	
}

// Function: moveDown
// Class: GameWorld
// Description: moves the character down on the board and adds 5 points to the score

int GameWorld::moveDown()
{
	if (playerPositionY != 4)
	{
		world[playerPositionY][playerPositionX] = ' ';
		world[playerPositionY + 1][playerPositionX] = 'U';
		++playerPositionY;
		score += 5;
		return 1;
	}
	else
	return 0;
}

// Function: moveRight
// Class: GameWorld
// Description: moves the character right on the board and adds 5 points to the score

int GameWorld::moveRight()
{
	if (playerPositionX != 4)
	{
		world[playerPositionY][playerPositionX] = ' ';
		world[playerPositionY][playerPositionX + 1] = 'U';
		++playerPositionX;
		score += 5;
		return 1;
	}
	else
	return 0;
}

// Function: moveLeft
// Class: GameWorld
// Description: moves the character left on the board and adds 5 points to the score

int GameWorld::moveLeft()
{
	if (playerPositionX != 0)
	{
		world[playerPositionY][playerPositionX] = ' ';
		world[playerPositionY][playerPositionX - 1] = 'U';
		--playerPositionX;
		score += 5;
		return 1;
	}
	else
	return 0;
}

// Function: haveIWon
// Class: GameWorld
// Description: checks if the player has won by moving onto the gold. returns 1 if the player has won, returns 0 if not

int GameWorld::haveIWon()
{
	if (worldInitial[playerPositionY][playerPositionX] == 'G')
	{
		return 1;
	}
	return 0;
}

// Function: haveIWon
// Class: GameWorld
// Description: checks if the player has died by moving onto a pit or the wumpus. returns 1 if the player is alive, returns 0 if not

int GameWorld::amIAlive()
{
	if (worldInitial[playerPositionY][playerPositionX] == 'P' || worldInitial[playerPositionY][playerPositionX] == 'W')
	{
		return 0;
	}
	return 1;
}