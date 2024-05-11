//
// Created by jakub on 11.05.24.
//

#include "snakeMenu.h"

snakeMenu::snakeMenu(sf::RenderWindow &window) {
    windowWidth = window.getSize().x;
    windowHeight = window.getSize().y;
    setupButtons();
    updateButtons();
}

void snakeMenu::setupButtons() {
    float const shortButtonWidth = windowWidth * 0.20;
    float const buttonHeight = windowHeight * 0.1;
    float const longButtonWidth = shortButtonWidth * 3 + std::max(shortButtonWidth, buttonHeight) * 0.05*2;
    for (sf::RectangleShape & button : menuButtonShapes){
        button.setFillColor(sf::Color::Cyan);
    }
    for (int button=0; button<3; button++) {
        menuButtonShapes[button].setSize(sf::Vector2f(shortButtonWidth, buttonHeight));
    }
    for (int button=3; button<5; button++) {
        menuButtonShapes[button].setSize(sf::Vector2f(longButtonWidth, buttonHeight));
    }
}

void snakeMenu::updateButtons() {
    int const shortButtonWidth = menuButtonShapes[0].getLocalBounds().width;
    int const shortButtonHeight = menuButtonShapes[0].getLocalBounds().height;
    int const buttonSpacing = std::max(shortButtonWidth, shortButtonHeight) * 0.05; //Ten sam parametr w dwóch różnych funkcjach!
    float positionX;
    float positionY=windowHeight * 0.45;

    for (int button=0; button<3; button++) {
        positionX = windowWidth * 0.3 + (button * (shortButtonWidth + buttonSpacing));
        menuButtonShapes[button].setPosition(
                sf::Vector2f(positionX-shortButtonWidth*0.5, positionY));
    }

    positionX=windowWidth*0.5;
    for (int button=3; button<5; button++){
        positionY = windowHeight * 0.45 + (button-2) * (shortButtonHeight + buttonSpacing);
        menuButtonShapes[button].setPosition(
                sf::Vector2f(positionX-shortButtonWidth*3*0.5, positionY));
    }
}

void snakeMenu::drawMenu(sf::RenderWindow &window) const {
    window.clear(sf::Color(0, 0, 0));
    for (sf::RectangleShape const & button : menuButtonShapes) {
        window.draw(button);
    }
}




