//
// Created by jakub on 11.05.24.
//

#ifndef SNAKE_SNAKEMENU_H
#define SNAKE_SNAKEMENU_H
#include "SFML/Graphics.hpp"

class snakeMenu {
//    sf::RectangleShape easyButtonShape;
//    sf::RectangleShape normalButtonShape;
//    sf::RectangleShape hardButtonShape;
//    sf::RectangleShape scoreboardShape;
//    sf::RectangleShape exitButton;
    sf::RectangleShape menuButtonShapes[5];
    int windowWidth;
    int windowHeight;
    void setupButtons();
    void updateButtons();
public:
    explicit snakeMenu(sf::RenderWindow & window);
    void drawMenu(sf::RenderWindow & window) const;
};


#endif //SNAKE_SNAKEMENU_H
