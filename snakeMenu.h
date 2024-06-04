//
// Created by jakub on 11.05.24.
//

#ifndef SNAKE_SNAKEMENU_H
#define SNAKE_SNAKEMENU_H
#include "SFML/Graphics.hpp"
#include "FontManager.h"
#include "TextureManager.h"

class snakeMenu {
    sf::RectangleShape menuButtonShapes[5];
    FontManager & fontmgr;
    TextureManager & texmgr;

    sf::RectangleShape background;
    sf::Text menuText[5];
    sf::Text welcomeText;
    int windowWidth;
    int windowHeight;
    void setupButtons();
    void updateButtons();
    void setupText();
    void updateText();
    void setupBackground();
public:
    explicit snakeMenu(sf::RenderWindow & window, FontManager & f, TextureManager & t);
    void drawMenu(sf::RenderWindow & window) const;
    std::string buttonPressed(float x, float y) const;
};


#endif //SNAKE_SNAKEMENU_H
