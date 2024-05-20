//
// Created by jakub on 20.05.24.
//

#ifndef SNAKE_SNAKESCOREBOARDVIEWER_H
#define SNAKE_SNAKESCOREBOARDVIEWER_H
#include "snakeScoreboard.h"
#include "FontManager.h"
#include <SFML/Graphics.hpp>

class snakeScoreboardViewer {
    FontManager & fontmgr;
    snakeScoreboard & scoreboard;
    int windowWidth;
    int windowHeight;
    sf::Text ScoreboardTitle;
    sf::Text ScoreboardText[scoreboardSize];

    void setupText();
    void updateText();
public:
    snakeScoreboardViewer(FontManager & f, snakeScoreboard & s, const sf::RenderWindow & window);
    void drawScoreboard(sf::RenderWindow & window) const;
};


#endif //SNAKE_SNAKESCOREBOARDVIEWER_H
