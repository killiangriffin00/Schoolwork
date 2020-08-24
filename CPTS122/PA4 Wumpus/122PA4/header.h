/*
	NAME: Killian Griffin
	DATE: 2/26/20
	ASSIGNMENT: PA4
	LAB SECTION: 5
	DESCRIPTION: This program lets the user play a game called Hunt the Wumpus, where the user searches for a pot of gold while avoiding
				 the Wumpus and various pits.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class GameWorld
{
private:
	char world[5][5];        // the board explored by the user
	char worldInitial[5][5]; // the initial position of everything on the board (used to calculate position of player with respect to hazards)
	int score = 0;           // player score
	int playerPositionX = 0; // position on x-axis of the board
	int playerPositionY = 0; // position on y axis of board

public:
	GameWorld();
	int getScore();
	int setScore(int newScore);
	void displayEntireWorld();
	void displayVisibleWorld();
	void displayPlayerPosition();
	int moveUp();
	int moveDown();
	int moveRight();
	int moveLeft();
	int haveIWon();
	int amIAlive();
};