//
// Created by jakub on 20.05.24.
//

#ifndef SNAKE_SNAKESCOREBOARDVIEWER_H
#define SNAKE_SNAKESCOREBOARDVIEWER_H
#include "snakeScoreboard.h"
#include "snakeBody.h"
#include "FontManager.h"
#include <SFML/Graphics.hpp>

class snakeScoreboardViewer {
    snakeBody & snake;
    FontManager & fontmgr;
    snakeScoreboard & scoreboard;
    int windowWidth;
    int windowHeight;
    unsigned int textSpaceY;
    sf::Text ScoreboardTitle;
    sf::Text ScoreboardText[scoreboardSize];

    sf::Text ScoreTitle;
    sf::Text playerNick;

    void setupViewText();
    void setupWriteText();

public:
    snakeScoreboardViewer(snakeBody & s, FontManager & f, snakeScoreboard & scb, const sf::RenderWindow & window);
    void drawScoreboard(sf::RenderWindow & window) const;
    void drawScoreboardSave(sf::RenderWindow & window) const;
    void updateViewText();
    void updateWriteText();
    bool inputText(sf::Event & event);
};


#endif //SNAKE_SNAKESCOREBOARDVIEWER_H
