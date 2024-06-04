//
// Created by jakub on 11.05.24.
//
#include <iostream>
#include <cstring>
#include "snakeMenu.h"
#include "FontManager.h"
#include "ColorsConsts.h"

snakeMenu::snakeMenu(sf::RenderWindow &window, FontManager & f, TextureManager & t) : fontmgr(f), texmgr(t) {
    windowWidth = window.getSize().x;
    windowHeight = window.getSize().y;

    setupButtons();
    updateButtons();

    setupText();
    updateText();

    setupBackground();
}

void snakeMenu::setupButtons() {
    float const shortButtonWidth = windowWidth * 0.20;
    float const buttonHeight = windowHeight * 0.1;
    float const longButtonWidth = shortButtonWidth * 3 + std::max(shortButtonWidth, buttonHeight) * 0.05*2;
    for (sf::RectangleShape & button : menuButtonShapes){
        button.setFillColor(buttonColor);
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
    const std::string setstring[] = { "EASY", "NORMAL", "HARD", "SCOREBOARD", "EXIT"};
    float textSize,buttonSize;
    for (int text=0; text<5; text++) {
        menuText[text].setFont(fontmgr.getFont());
        menuText[text].setFillColor(textColor);
        menuText[text].setString(setstring[text]);
        menuText[text].setCharacterSize(menuButtonShapes[text].getSize().y*0.3);
        textSize = menuText[text].getLocalBounds().width;
        buttonSize = menuButtonShapes[text].getSize().x;
        if (textSize > buttonSize) {
            menuText[text].setCharacterSize(menuText[text].getCharacterSize()*(buttonSize / textSize));
        }
    }

    welcomeText.setFont(fontmgr.getFont());
    welcomeText.setCharacterSize(std::min(windowWidth, windowHeight)*0.15);
    welcomeText.setFillColor(textColor);
    welcomeText.setString("SNAKE");
}

void snakeMenu::updateText() {
    int textWidth, textHeight;
    int buttonWidth, buttonHeight;
    int leftUpButtonCornerX, leftUpButtonCornerY;
    for (int text=0; text<5; text++) {
        textWidth = menuText[text].getLocalBounds().width;
        textHeight = menuText[text].getLocalBounds().height;
        buttonWidth = menuButtonShapes[text].getLocalBounds().width;
        buttonHeight = menuButtonShapes[text].getLocalBounds().height;
        leftUpButtonCornerX = menuButtonShapes[text].getPosition().x;
        leftUpButtonCornerY = menuButtonShapes[text].getPosition().y;
        menuText[text].setPosition(leftUpButtonCornerX + (buttonWidth - textWidth) * 0.5, leftUpButtonCornerY + (buttonHeight - textHeight) * 0.5);
    }
    welcomeText.setPosition((windowWidth-welcomeText.getLocalBounds().width)*0.5, (menuButtonShapes[1].getGlobalBounds().top-welcomeText.getLocalBounds().height)*0.5);
}

void snakeMenu::setupBackground() {
    const sf::Texture * backgroundTex = texmgr.getBackgroundTexture();
    background.setFillColor(menuBackgroundColor);
    background.setTexture(backgroundTex);
    background.setTextureRect(sf::IntRect(0,0,windowWidth*0.005*backgroundTex->getSize().x,windowHeight*0.005*backgroundTex->getSize().y));
    background.setSize(sf::Vector2f(windowWidth,windowHeight));
    background.setPosition(0.f, 0.f);
}


void snakeMenu::drawMenu(sf::RenderWindow &window) const {
        window.clear(menuBackgroundColor);
        window.draw(background);
    for (sf::RectangleShape const & button : menuButtonShapes) {
        window.draw(button);
    }
    window.draw(welcomeText);
    for (sf::Text const & button : menuText) {
        window.draw(button);
    }
}

std::string snakeMenu::buttonPressed(const float x, const float y) const {
    float buttonX, buttonY;
    float buttonWidth, buttonHeight;
    for (int button=0; button<5; button++) {
        buttonX = menuButtonShapes[button].getPosition().x;
        buttonY = menuButtonShapes[button].getPosition().y;
        buttonWidth = buttonX + menuButtonShapes[button].getLocalBounds().width;
        buttonHeight = buttonY + menuButtonShapes[button].getLocalBounds().height;
        if (x>=buttonX && x<=buttonWidth && y>=buttonY && y<=buttonHeight)
            return menuText[button].getString();
    }
    return "NULL";
}