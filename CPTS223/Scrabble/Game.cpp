#include "Game.h"

// ********************* PRIVATE *********************

void Game::populateDeck()
{
    std::ifstream infile;

    char delim = ',', letter = '\0';
    string line = "";
    int pos = 0, worth = 0;
    try
    {
        infile.open("letterDistribution.txt");
        std::getline(infile, line);
        while (std::getline(infile, line))
        {
            pos = line.find(delim);
            letter = line.substr(0, pos)[0];
            line.erase(0, pos + 1);

            pos = line.find(delim);
            worth = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            for (int i = 0; i < stoi(line); ++i)
                deck.push_back(Tile(letter, worth));
        }

        std::random_shuffle(deck.begin(), deck.end());
        infile.close();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "\"letterDistribution.txt\" was not found";
    }
    
}



// ********************* PUBLIC *********************

Game::Game() : currentPlayer(p1)
{
    populateDeck();
    draw(p1);
    draw(p2);
    playGame();
}


void Game::playGame()
{
    int turnCount = 1;
    sf::RenderWindow window(sf::VideoMode(WINDOW_X_SIZE, WINDOW_Y_SIZE), "Grid");
    window.setFramerateLimit(10);
    sf::Font font;
    font.loadFromFile("Roboto-Bold.ttf");
    Tile selectedTile;
    sf::Event event;
    sf::Vector2i mousePos;

    sf::RectangleShape recallButton(sf::Vector2f(WINDOW_X_SIZE / 8, WINDOW_Y_SIZE / 12));
    recallButton.setOrigin(sf::Vector2f(recallButton.getGlobalBounds().width / 2, recallButton.getGlobalBounds().height / 2));
    recallButton.setFillColor(sf::Color::Red);
    recallButton.setOutlineColor(sf::Color(100, 0, 200));
    recallButton.setOutlineThickness(5);
    recallButton.setPosition(BOARD_TILE_SIZE * X_SIZE + (WINDOW_X_SIZE / 24) + 60, WINDOW_Y_SIZE - (WINDOW_Y_SIZE / 24) - 20);

    sf::Text recallText("Recall", font, 30);
    recallText.setOrigin(sf::Vector2f(recallText.getGlobalBounds().width / 2, recallText.getGlobalBounds().height / 2));
    recallText.setFillColor(sf::Color::Blue);
    recallText.setPosition(recallButton.getPosition());

    sf::RectangleShape submitButton(sf::Vector2f(WINDOW_X_SIZE / 8, WINDOW_Y_SIZE / 12));
    submitButton.setOrigin(sf::Vector2f(recallButton.getGlobalBounds().width / 2, recallButton.getGlobalBounds().height / 2));
    submitButton.setFillColor(sf::Color::Red);
    submitButton.setOutlineColor(sf::Color(100, 0, 200));
    submitButton.setOutlineThickness(5);
    submitButton.setPosition(WINDOW_X_SIZE - (WINDOW_X_SIZE / 24) - 20, WINDOW_Y_SIZE - (WINDOW_Y_SIZE / 24) - 20);

    sf::Text submitText("Submit", font, 30);
    submitText.setOrigin(sf::Vector2f(submitText.getGlobalBounds().width / 2, submitText.getGlobalBounds().height / 2));
    submitText.setFillColor(sf::Color::Blue);
    submitText.setPosition(submitButton.getPosition());

    sf::RectangleShape menuBox(sf::Vector2f(WINDOW_X_SIZE - (X_SIZE * BOARD_TILE_SIZE) - 30, ((Y_SIZE * BOARD_TILE_SIZE) / 2) - 20));
    menuBox.setOrigin(sf::Vector2f(menuBox.getGlobalBounds().width / 2, menuBox.getGlobalBounds().height / 2));
    menuBox.setFillColor(sf::Color::White);
    menuBox.setOutlineThickness(5);
    menuBox.setOutlineColor(sf::Color::Blue);
    menuBox.setPosition(WINDOW_X_SIZE - (menuBox.getGlobalBounds().width / 2) - 5, (menuBox.getGlobalBounds().height / 2) + 5);

    sf::Text p1ScoreText("P1 Score: 0", font, 30);
    p1ScoreText.setOrigin(sf::Vector2f(p1ScoreText.getGlobalBounds().width / 2, p1ScoreText.getGlobalBounds().height / 2));
    p1ScoreText.setFillColor(sf::Color::Red);
    p1ScoreText.setPosition(WINDOW_X_SIZE - (p1ScoreText.getGlobalBounds(). width / 2) - 70, (p1ScoreText.getGlobalBounds().height / 2) + 20);

    sf::Text p2ScoreText("P2 Score: 0", font, 30);
    p2ScoreText.setOrigin(sf::Vector2f(p2ScoreText.getGlobalBounds().width / 2, p2ScoreText.getGlobalBounds().height / 2));
    p2ScoreText.setFillColor(sf::Color::Blue);
    p2ScoreText.setPosition(WINDOW_X_SIZE - (p2ScoreText.getGlobalBounds(). width / 2) - 70, (p2ScoreText.getGlobalBounds().height / 2) + p2ScoreText.getGlobalBounds().height + 30);

    sf::RectangleShape turnIndicator(sf::Vector2f(20, 20));
    turnIndicator.setOrigin(sf::Vector2f(turnIndicator.getGlobalBounds().width / 2, turnIndicator.getGlobalBounds().height / 2));
    turnIndicator.setFillColor(sf::Color::Green);
    turnIndicator.setPosition(p1ScoreText.getPosition().x - (p1ScoreText.getGlobalBounds().width / 2) - 40, p1ScoreText.getPosition().y + 10);

    sf::Text gameText("\0", font, 25);
    gameText.setFillColor(sf::Color::Black);
    gameText.setPosition(menuBox.getPosition().x - (menuBox.getGlobalBounds().width / 2) + 10, menuBox.getPosition().y);
    

    while (!deck.empty() && window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == event.Closed)
                window.close();

            if (event.type == event.MouseButtonReleased)
            {
                mousePos = sf::Mouse::getPosition(window);

                // if click was in the board's y rang
                if (mousePos.y < BOARD_TILE_SIZE * Y_SIZE )
                {
                    int x = std::floor(mousePos.x / BOARD_TILE_SIZE);
                    int y = std::floor(mousePos.y / BOARD_TILE_SIZE);

                    // if click was out of board range
                    if ((x < X_SIZE && x >= 0) && (y < Y_SIZE && y >= 0))
                    {
                        if (b.isTileEmpty(x, y) && selectedTile.c != '\0')
                        {
                            selectedTile.established = false;
                            b.insert(x, y, selectedTile);
                            std::cout << "TILE INSERTED: Letter: " << selectedTile.c << " STATUS: " << selectedTile.established << ", X: " << x << ", Y: " << y << std::endl;

                            selectedTile.c = '\0';                        
                        }
                    }
                }
                else if((recallButton.getPosition().x - recallButton.getGlobalBounds().width / 2 < mousePos.x &&
                    recallButton.getPosition().x + recallButton.getGlobalBounds().width / 2 > mousePos.x) &&
                    (recallButton.getPosition().y - recallButton.getGlobalBounds().height / 2 < mousePos.y &&
                    recallButton.getPosition().y + recallButton.getGlobalBounds().height / 2 > mousePos.y))
                {
                    b.recall(currentPlayer.hand);
                    gameText.setString("Tiles Recalled");
                }

                else if((submitButton.getPosition().x - submitButton.getGlobalBounds().width / 2 < mousePos.x &&
                    submitButton.getPosition().x + submitButton.getGlobalBounds().width / 2 > mousePos.x) &&
                    (submitButton.getPosition().y - submitButton.getGlobalBounds().height / 2 < mousePos.y &&
                    submitButton.getPosition().y + submitButton.getGlobalBounds().height / 2 > mousePos.y))
                {
                    std::pair<bool, std::string> data = validate();

                    if(!data.first)
                    {
                        gameText.setString(data.second);

                        b.recall(currentPlayer.hand);
                    }
                    else
                    {
                        std::string playerScore;
                        currentPlayer.points += stoi(data.second);
                        if (turnCount % 2 != 0)
                        {
                            playerScore = "P1 Score: ";
                            p1ScoreText.setString(playerScore.append(std::to_string(currentPlayer.points)));
                            turnIndicator.setPosition(turnIndicator.getPosition().x, p2ScoreText.getPosition().y + 10);
                            gameText.setString("\0");
                            draw(currentPlayer);
                            currentPlayer = p2;
                        }
                        else
                        { 
                            playerScore = "P2 Score: ";
                            p2ScoreText.setString(playerScore.append(std::to_string(currentPlayer.points)));
                            turnIndicator.setPosition(turnIndicator.getPosition().x, p1ScoreText.getPosition().y + 10);
                            gameText.setString("\0");
                            draw(currentPlayer);
                            currentPlayer = p1;
                        }
                        ++turnCount;
                    }
                }

                // if click was in range of player's hand
                else 
                {
                    for (int i = 0 ; i < currentPlayer.hand.size() && selectedTile.c == '\0'; ++i)
                    {
                        
                        sf::RectangleShape* curRect = &currentPlayer.hand.at(i).rect;
                        if ((curRect->getPosition().x - 40 < mousePos.x && curRect->getPosition().x + 40 > mousePos.x) 
                            && (curRect->getPosition().y - 40 < mousePos.y && curRect->getPosition().y + 40 > mousePos.y))
                        {
                            selectedTile = currentPlayer.hand.at(i);
                        
                            std::cout << "TILE SELECTED: Letter: " << currentPlayer.hand.at(i).c << ", Value: " <<  currentPlayer.hand.at(i).val << std::endl;
                            currentPlayer.hand.erase(currentPlayer.hand.begin() + i);
                        }
                    }
                }
            }
        }   

        window.clear();

        for (int i = 0; i < currentPlayer.hand.size(); ++i)
        {
            
            currentPlayer.hand.at(i).rect.setOrigin(sf::Vector2f(HAND_TILE_SIZE / 2, HAND_TILE_SIZE / 2));
            currentPlayer.hand.at(i).rect.setPosition((i * HAND_TILE_SIZE) + (HAND_TILE_SIZE / 2) + (i * 5) + 20, WINDOW_Y_SIZE + 30 - HAND_TILE_SIZE);
            
            currentPlayer.hand.at(i).text.setFont(font);
            currentPlayer.hand.at(i).text.setPosition(currentPlayer.hand.at(i).rect.getPosition());
        }

        // Draw deck, rectangles are designed in constructor of board
        for (int i = 0; i < Y_SIZE; ++i)
        {
            for (int j = 0; j < X_SIZE; ++j)
            {
                window.draw(b.getTile(j, i).rect);
                window.draw(b.getTile(j, i).text);

                if(i < currentPlayer.hand.size())
                {
                    window.draw(currentPlayer.hand.at(i).rect);
                    window.draw(currentPlayer.hand.at(i).text);
                }
            }
        }

        window.draw(recallButton);
        window.draw(recallText);
        window.draw(submitButton);
        window.draw(submitText);
        window.draw(menuBox);
        window.draw(p1ScoreText);
        window.draw(p2ScoreText);
        window.draw(turnIndicator);
        window.draw(gameText);
        
        window.display();
    }
}

void Game::draw(Player& p)
{
    while ((p.hand.size() != 7) && (deck.size() != 0))
    {
        p.hand.push_back(deck.front());
        deck.erase(deck.begin());
    }
}

void Game::printDeck()
{
    for (Tile t : deck)
        std::cout << "Letter: " << t.c << ", Value: " << t.val << std::endl;
}

void Game::printBoard()
{
    b.printBoard();
}

std::pair<bool, std::string> Game::validate()
{
    std::vector<std::vector<Tile*>> words; // A list of words (vectors of tiles)
    words.push_back(std::vector<Tile*>());
    bool axis = false; // Axis is used to define direction of main word. Is true for vertical and false for horizontal

    for(int y = 0; y < Y_SIZE; ++y)
    {
        for(int x = 0; x < X_SIZE; ++x)
        {
            if(!b[y][x].established)
            {
                if(!words[0].size())
                {
                    words[0].push_back(&b[y][x]);
                    
                    bool foundNotEstablished = false;
                    
                    for(int i = x + 1; !foundNotEstablished && (i < X_SIZE && b[y][i].c != '\0'); ++i)
                    {
                        if(!b[y][i].established)
                        {
                            foundNotEstablished = true;
                            // axis = false; not nessisary because axis is initialized false
                        }
                    }
                    for(int i = y + 1; !foundNotEstablished && (i < Y_SIZE && b[i][x].c != '\0'); ++i)
                    {
                        if(!b[i][x].established)
                        {
                            foundNotEstablished = true;
                            axis = true;
                        }
                    }
                    if(foundNotEstablished) 
                    {   
                        if(axis)
                        {
                            for(int i = y + 1; b[i][x].c != '\0' && i < Y_SIZE; ++i)
                            {
                                words[0].push_back(&b[i][x]);
                            }
                            for(int i = y - 1; b[i][x].c != '\0' && i >= 0; --i)
                            {
                                words[0].insert(words[0].begin(), &b[i][x]);
                            }
                        }
                        else
                        {
                            for(int i = x + 1; b[y][i].c != '\0' && i < X_SIZE; ++i)
                            {
                                words[0].push_back(&b[y][i]);
                            }
                            for(int i = x - 1; b[y][i].c != '\0' && i >= 0; --i)
                            {
                                words[0].insert(words[0].begin(), &b[y][i]);
                            }
                        }
                    }
                    else
                    {   
                        if(b[y + 1][x].c != '\0' || b[y - 1][x].c != '\0')
                        {
                            for(int i = y + 1; b[i][x].c != '\0' && i < Y_SIZE; ++i)
                            {
                                words[0].push_back(&b[i][x]);
                            }
                            for(int i = y - 1; b[i][x].c != '\0' && i >= 0; --i)
                            {
                                words[0].insert(words[0].begin(), &b[i][x]);
                            }
                        }
                        else
                        {
                            for(int i = x + 1; b[y][i].c != '\0' && i < X_SIZE; ++i)
                            {
                                words[0].push_back(&b[y][i]);
                            }
                            for(int i = x - 1; b[y][i].c != '\0' && i >= 0; --i)
                            {
                                b[y][i].x = i;
                                b[y][i].y = y;
                                words[0].insert(words[0].begin(), &b[y][i]);
                            }
                        }
                    }
                }
                else
                {
                    bool secondWord = true;
                    for(int i = 0; secondWord && i < words[0].size(); ++i)
                    {
                        if(words[0][i]->x == x && words[0][i]->y == y)
                        {
                            secondWord = false;
                        }
                    }
                    if(secondWord)
                    {
                        return std::pair<bool, std::string>(false, std::string("Words must be placed \nin a straight line."));
                    }
                }
            }
        }
    }
    if(!words[0].size())
    {
        return std::pair<bool, std::string>(false, std::string("No tiles have been placed."));
    }

    for(int i = 0, j = 1; i < words[0].size(); ++i)
    {
        if(!words[0][i]->established)
        {
            if(axis)
            {
                if(b[words[0][i]->y][words[0][i]->x + 1].c != '\0' || b[words[0][i]->y][words[0][i]->x - 1].c != '\0')
                {
                    words.push_back(std::vector<Tile*>());
                    words[j].push_back(words[0][i]);
                    for(int k = words[0][i]->x + 1; b[words[0][i]->y][k].c != '\0' && k < X_SIZE; ++k)
                    {
                        words[j].push_back(&b[words[0][i]->y][k]);
                    }
                    for(int k = words[0][i]->x - 1; b[words[0][i]->y][k].c != '\0' && k >= 0; --k)
                    {
                        words[j].insert(words[j].begin(), &b[words[0][i]->y][k]);
                    }
                    ++j;
                }
            }
            else if(b[words[0][i]->y + 1][words[0][i]->x].c != '\0' || b[words[0][i]->y - 1][words[0][i]->x].c != '\0')
            {
                words.push_back(std::vector<Tile*>());
                words[j].push_back(words[0][i]);
                for(int k = words[0][i]->y + 1; b[k][words[0][i]->x].c != '\0' && k < Y_SIZE; ++k)
                {
                    words[j].push_back(&b[k][words[0][i]->x]);
                }
                for(int k = words[0][i]->y - 1; b[k][words[0][i]->x].c != '\0' && k >= 0; --k)
                {
                    words[j].insert(words[j].begin(), &b[k][words[0][i]->x]);
                }
                ++j;
            }
        }
    }

    bool noEstablished = true;

    for(int i = 0; i < words.size(); ++i)
    {
        for(int j = 0; j < words[i].size(); ++j)
        {
            if(noEstablished && (words[i][j]->established || words[i][j]->center))
            {
                noEstablished = false;
            }
        }
    }

    if(noEstablished)
    {
        return std::pair<bool, std::string>(false, std::string("Word must be connected\n to other words or in the\n center of the board."));
    }

    for(int i = 0; i < words.size(); ++i)
    {
        std::string s;
        for(int j = 0; j < words[i].size(); ++j)
        {
            s.push_back(words[i][j]->c);
        }

        std::string comp;
        for(int j = 0; j < s.size(); ++j)
        {
            comp.push_back(s[j] + 32);
        }

        if(!d.isWord(comp))
        {
            s.append(" is \nnot a word.");
            return std::pair<bool, std::string>(false, s);
        }
    }

    int score = 0;
    for(int i = 0; i < words.size(); ++i)
    {
        for(int j = 0; j < words[i].size(); ++j)
        {
            words[i][j]->rect.setFillColor(sf::Color::Green);
            words[i][j]->established = true;
            score += words[i][j]->val;
        }
    }

    return std::pair<bool, std::string>(true, std::to_string(score));
}