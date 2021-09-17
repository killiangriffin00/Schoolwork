#ifndef GAME_H
#define GAME_H

#include "Dictionary.h"
#include "Board.h"

#include <algorithm>
#include <random>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>

using std::vector;

struct Player
{
    int points;
    vector<Tile> hand;
   // Player(int p) { this->points = p; }
};

class Game
{
    private:
        sf::Font font;
        Player p1, p2;
        Player &currentPlayer;
        Dictionary d;
        Board b;
        vector<Tile> deck;

    public:
        Game();

        void draw(Player&);
        void populateDeck();
        void printDeck();
        void printBoard();
        void playGame();
        std::pair<bool, std::string> validate();

        Player getCurrentPlayer() { return currentPlayer; };

        Board getBoard() { return b; };

};






#endif