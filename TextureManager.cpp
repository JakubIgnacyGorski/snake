//
// Created by jakub on 26.05.24.
//

#include <cstring>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include "TextureManager.h"

TextureManager::TextureManager() {

    if (!background.loadFromFile("textures/background/runningBackground.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    background.setRepeated(true); //źródło: https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Texture.php#aaa87d1eff053b9d4d34a24c784a28658
    if (!snakeHead.loadFromFile("textures/snake/head.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if (!snakeBody.loadFromFile("textures/snake/body.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if (!snakeBack.loadFromFile("textures/snake/tail.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }

    if (!snakeTurn[turnDir{DOWNLEFT}].loadFromFile("textures/snake/turn/turn-down-left.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if (!snakeTurn[turnDir{DOWNRIGHT}].loadFromFile("textures/snake/turn/turn-down-right.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if (!snakeTurn[turnDir{UPLEFT}].loadFromFile("textures/snake/turn/turn-up-left.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if (!snakeTurn[turnDir{UPRIGHT}].loadFromFile("textures/snake/turn/turn-up-right.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
}

const sf::Texture * TextureManager::getBackgroundTexture() const {
    return &background;
}

const sf::Texture *TextureManager::getSnakeHead() const {
    return &snakeHead;
}

const sf::Texture *TextureManager::getSnakeBody() const {
    return &snakeBody;
}

const sf::Texture *TextureManager::getSnakeBack() const {
    return &snakeBack;
}

const sf::Texture *TextureManager::getSnakeTurn(const turnDir dir) const {
    return &snakeTurn[dir];
}


