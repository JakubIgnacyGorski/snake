//
// Created by jakub on 20.05.24.
//

#ifndef SNAKE_SNAKESCOREBOARDVIEWER_H
#define SNAKE_SNAKESCOREBOARDVIEWER_H
#include "snakeScoreboard.h"
#include "snakeBody.h"
#include "FontManager.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>

class snakeScoreboardViewer {
    snakeBody & snake;
    FontManager & fontmgr;
    TextureManager & texmgr;
    snakeScoreboard & scoreboard;
    int windowWidth;
    int windowHeight;
    unsigned int textSpace;

    // Scoreboard View
    sf::Text ScoreboardTitle;
    sf::Text ScoreboardText[scoreboardSize];
    sf::RectangleShape viewBackground;

    // Scoreboard Write
    sf::Text ScoreTitle;
    sf::Text playerNick;
    sf::Text enterNick;
    sf::RectangleShape writeBackground;

    void setupViewText();
    void setupWriteText();
    void setupBackground();

public:
    snakeScoreboardViewer(const sf::RenderWindow & window, snakeBody & s, FontManager & f, TextureManager & t, snakeScoreboard & scb);
    void drawScoreboard(sf::RenderWindow & window) const;
    void drawScoreboardSave(sf::RenderWindow & window) const;
    void updateViewText();
    void updateWriteText();
    bool inputText(sf::Event & event);
};


#endif //SNAKE_SNAKESCOREBOARDVIEWER_H
