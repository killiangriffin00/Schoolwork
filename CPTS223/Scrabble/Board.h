#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#define X_SIZE 15
#define Y_SIZE 15

#define WINDOW_X_SIZE 1000
#define WINDOW_Y_SIZE 800

#define HAND_TILE_SIZE 80
#define BOARD_TILE_SIZE 40

struct Tile
{
    sf::RectangleShape rect;
    sf::Text text;
    char c;
    int val;
    int x;
    int y;
    bool center;
    bool established;
    
    Tile() 
    { 
        c = '\0'; 
        val = 0; 
        x = -1;
        y = -1;
        established = true;
        center = false;
        text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2));
        initHandTile();
    }
    Tile(char newC, int newV) 
    { 
        c = newC; 
        val = newV; 
        x = -1;
        y = -1;
        established = true;
        center = false; 
        text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2));
        initHandTile();
    };

    void initBoardTile(int ix, int iy)
    {
        rect.setFillColor(sf::Color::White);
        rect.setOutlineColor(sf::Color::Blue);
        rect.setSize(sf::Vector2f(BOARD_TILE_SIZE - 5, BOARD_TILE_SIZE - 5));
        rect.setOutlineThickness(5);
        c = '\0';
        established = true;
        val = 0;
        x = ix;
        y = iy;
        text.setString("\0");
    }

    void initHandTile()
    {
        rect.setSize(sf::Vector2f(HAND_TILE_SIZE, HAND_TILE_SIZE));
        rect.setFillColor(sf::Color::Green);
        rect.setOutlineThickness(0);

        text.setString(c);
        text.setFillColor(sf::Color::Red);
        text.setCharacterSize(30);
        text.setPosition(rect.getPosition().x, rect.getPosition().y);
    }
};

class Board
{
    private:
        
        Tile board[Y_SIZE][X_SIZE];
        void initBoardSprites();

    public:
        Board();

        bool insert(int, int, Tile); // returns true if tile can be inserted at coords
        Tile getTile(int, int);
        bool isTileEmpty(int, int);
        void printBoard();
        Tile north(Tile);
        Tile south(Tile);
        Tile east(Tile);
        Tile west(Tile);
        void recall(std::vector<Tile>&);
        Tile* operator[](int);

};






#endif