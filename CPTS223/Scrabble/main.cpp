/*
    PROJECT CREATORS: Killian Griffin and Ethan Nelson
    DATE: 12/11/20
    PROJECT: PA6
    
    Welcome to Scrabble!!! To play, just click on the bottom tiles in your hand and place them on the 
    board so that they form a word. Make sure that the tiles you place are in a straight horizontal or 
    vertical line, and make sure the word is either in the center of the board or connected to an already
    established word on the board. This game uses a hash table of std::maps to search for words in 
    our dictionary. Have fun!!!
*/


#include "Game.h"
#include <SFML/Graphics.hpp>

#define EMPTY_TILE_SPRITE_FILEPATH "${workspaceFolder}/Resources/Tile.png" 
#define NUM_COLUMNS 15
#define NUM_ROWS 15
#define OUTLINE_THICKNESS 5

// MAKE SURE SFML IS INSTALLED. TO INSTALL SFML, USE THE FOLLOWING COMMAND
// sudo apt-get install libsfml-dev

int main(void)
{
    srand(time(nullptr));

    Game gg;

    return 0;
}