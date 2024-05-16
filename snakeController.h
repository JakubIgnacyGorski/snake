    //
// Created by jakub on 09.05.24.
//

#ifndef SNAKE_SNAKECONTROLLER_H
#define SNAKE_SNAKECONTROLLER_H
#include <SFML/Graphics.hpp>
#include "snakeBody.h"
#include "snakeViewer.h"
#include "snakeMenu.h"
#include "snakeScoreboard.h"
enum GameDifficulty {EASY, NORMAL, HARD};


class snakeController {
    snakeBody & snake;
    snakeViewer & viewer;
    snakeMenu & menu;
    snakeScoreboard & scoreboard;
    GameDifficulty Difficulty;
    sf::Clock clock;
    sf::Time moveDelay;
    int timeToMove;
    void keyboard(sf::Event & event);
    void timeMove();
    void changeDirection(speed newDir);
    void mouse(sf::Event & event, sf::RenderWindow & window);
    void createNewGame(const sf::RenderWindow & window, GameState State);
public:
    snakeController(snakeBody & b, snakeViewer & v, snakeMenu & m, snakeScoreboard & s);
    void play(sf::RenderWindow & window);
};


#endif //SNAKE_SNAKECONTROLLER_H
