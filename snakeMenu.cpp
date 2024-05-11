//
// Created by jakub on 11.05.24.
//

#include "snakeMenu.h"
#include <iostream>
#include <cstring>

snakeMenu::snakeMenu(sf::RenderWindow &window) {
    windowWidth = window.getSize().x;
    windowHeight = window.getSize().y;

    if (!Font.loadFromFile("fonts/sd-snatcher.ttf")) {
        std::cerr <<strerror(errno) << std::endl;
        abort();
    }

    setupButtons();
    setupText();


    updateButtons();
    updateText();
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
    int const longButtonWidth = menuButtonShapes[3].getLocalBounds().width;
    int const buttonSpacing = (longButtonWidth-shortButtonWidth*3)*0.5;
    float const Yoffset = 0.45;

    float positionX;
    float positionY=windowHeight * Yoffset;

    for (int button=0; button<3; button++) {
        positionX = windowWidth * 0.3 + (button * (shortButtonWidth + buttonSpacing));
        menuButtonShapes[button].setPosition(
                sf::Vector2f(positionX-shortButtonWidth*0.5, positionY));
    }

    positionX=windowWidth*0.5;
    for (int button=3; button<5; button++){
        positionY = windowHeight * Yoffset + (button-2) * (shortButtonHeight + buttonSpacing);
        menuButtonShapes[button].setPosition(
                sf::Vector2f(positionX-shortButtonWidth*3*0.5, positionY));
    }
}

void snakeMenu::setupText() {
    std::string const setstring[] = { "EASY", "NORMAL", "HARD", "SCOREBOARD", "EXIT"};
    for (int text=0; text<5; text++) {
        menu[text].setFont(Font);
        menu[text].setCharacterSize(20);
        menu[text].setFillColor(sf::Color::Black);
        menu[text].setString(setstring[text]);
    }
}

void snakeMenu::updateText() {
    int textWidth, textHeight;
    int buttonWidth, buttonHeight;
    int leftUpButtonCornerX, leftUpButtonCornerY;
    for (int text=0; text<5; text++) {
        textWidth = menu[text].getLocalBounds().width;
        textHeight = menu[text].getLocalBounds().height;
        buttonWidth = menuButtonShapes[text].getLocalBounds().width;
        buttonHeight = menuButtonShapes[text].getLocalBounds().height;
        leftUpButtonCornerX = menuButtonShapes[text].getPosition().x;
        leftUpButtonCornerY = menuButtonShapes[text].getPosition().y;
        std::cout<<text<<": "<<buttonWidth<<','<<buttonHeight<<std::endl;
        menu[text].setPosition(leftUpButtonCornerX+(buttonWidth-textWidth)*0.5, leftUpButtonCornerY+(buttonHeight-textHeight)*0.5);
    }
}

void snakeMenu::drawMenu(sf::RenderWindow &window) const {
    window.clear(sf::Color::White);
    for (sf::RectangleShape const & button : menuButtonShapes) {
        window.draw(button);
    }
    for (sf::Text const & button : menu) {
        window.draw(button);
    }
}

std::string snakeMenu::buttonPressed(int x, int y) const {
    int buttonX, buttonY;
    int buttonWidth, buttonHeight;
    for (int button=0; button<5; button++) {
        buttonX = menuButtonShapes[button].getPosition().x;
        buttonY = menuButtonShapes[button].getPosition().y;
        buttonWidth = menuButtonShapes[button].getLocalBounds().width;
        buttonHeight = menuButtonShapes[button].getLocalBounds().height;
        if (x>=buttonX && x<=buttonX+buttonWidth &&
            y>=buttonY && y<=buttonY+buttonHeight) return menu[button].getString();
    }
    return "NULL";
}








