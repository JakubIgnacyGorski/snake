//
// Created by jakub on 11.05.24.
//

#ifndef SNAKE_SNAKEMENU_H
#define SNAKE_SNAKEMENU_H
#include "SFML/Graphics.hpp"

class snakeMenu {
    sf::RectangleShape menuButtonShapes[5];
    sf::Font Font;
    sf::Text menuText[5];
    int windowWidth;
    int windowHeight;
    void setupButtons();
    void updateButtons();
    void setupText();
    void updateText();
public:
    explicit snakeMenu(sf::RenderWindow & window);
    void drawMenu(sf::RenderWindow & window) const;
    std::string buttonPressed(int x, int y) const;
};


#endif //SNAKE_SNAKEMENU_H
