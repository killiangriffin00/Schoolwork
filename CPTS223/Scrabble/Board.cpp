#include "Board.h"

Board::Board()
{
    for (int i = 0; i < Y_SIZE; ++i)
    {
        for (int j = 0; j < X_SIZE; ++j)
        {
            board[i][j].initBoardTile(j, i);
            board[i][j].rect.setOrigin(board[i][j].rect.getGlobalBounds().width / 2, board[i][j].rect.getGlobalBounds().height / 2);
            //board[i][j].rect.setPosition(i*cellSize.x + board[i][j].rect.getOutlineThickness(), j*cellSize.y + board[i][j].rect.getOutlineThickness());
            //board[i][j].rect.setPosition((i*(cellSize.x)) + (cellSize.x / 2) + 10 + (i*5), (j*(cellSize.y)) + (cellSize.y / 2) + 10 + (j*5));
            board[i][j].rect.setPosition(10 + j*BOARD_TILE_SIZE + BOARD_TILE_SIZE / 2, 10 + i*BOARD_TILE_SIZE + BOARD_TILE_SIZE / 2);

            if(j == X_SIZE / 2 && i == Y_SIZE / 2)
            {
                board[i][j].center = true;
                board[i][j].rect.setFillColor(sf::Color::Green);
            }
        }
    }
}



bool Board::insert(int x, int y, Tile newTile)
{
    //newTile.rect.setSize(sf::Vector2f(BOARD_TILE_SIZE - 5, BOARD_TILE_SIZE - 5));
    //newTile.rect.setPosition(board[y][x].rect.getPosition().x + BOARD_TILE_SIZE / 2 - 3, board[y][x].rect.getPosition().y + BOARD_TILE_SIZE / 2 - 2);
    //newTile.rect.setFillColor(sf::Color::Red);
    //newTile.rect.setOutlineColor(sf::Color::Blue);
    //newTile.rect.setOutlineThickness(5);

    newTile.text.setString(newTile.c);
    newTile.text.setCharacterSize(20);
    newTile.text.setFillColor(sf::Color::Blue);
    newTile.text.setPosition(board[y][x].rect.getPosition().x - (BOARD_TILE_SIZE / 2), board[y][x].rect.getPosition().y - (BOARD_TILE_SIZE / 2));

    board[y][x].c = newTile.c;
    board[y][x].val = newTile.val;
    board[y][x].rect.setFillColor(sf::Color::Red);
    board[y][x].text = newTile.text;
    board[y][x].established = newTile.established;

    return true;
}

Tile Board::getTile(int x, int y)
{
    if ((x < X_SIZE && x >= 0) && (y < Y_SIZE && y >= 0))
        return board[y][x];
}

void Board::printBoard()
{
    for (int i = 0; i < Y_SIZE; ++i)
    {
        for (int j = 0; j < X_SIZE; ++j)
        {
            std::cout << board[i][j].c << " ";
        }
        std::cout << std::endl;
    }
}

Tile* Board::operator[](int y)
{
    return board[y];
}

void Board::recall(std::vector<Tile>& h)
{
    for(int i = 0; i < Y_SIZE; ++i)
    {
        for(int j = 0; j < X_SIZE; ++j)
        {
            if(!board[i][j].established)
            {
                board[i][j].initHandTile();
                h.push_back(board[i][j]);
                board[i][j].initBoardTile(j, i);    
                if(board[i][j].center)
                {
                    board[i][j].rect.setFillColor(sf::Color::Green);
                }

            }
        }
    }
}

bool Board::isTileEmpty(int x, int y)
{
    if (board[y][x].val == 0)
        return true;
    return false;
}