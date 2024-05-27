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
    if (!snakeHead[movDir{UP}].loadFromFile("textures/snake/head/head-up.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if (!snakeHead[movDir{RIGHT}].loadFromFile("textures/snake/head/head-right.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if (!snakeHead[movDir{DOWN}].loadFromFile("textures/snake/head/head-down.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if (!snakeHead[movDir{LEFT}].loadFromFile("textures/snake/head/head-left.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if (!snakeBody[0].loadFromFile("textures/snake/body/body-horizontal.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if (!snakeBody[1].loadFromFile("textures/snake/body/body-vertical.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if (!snakeBack[movDir{UP}].loadFromFile("textures/snake/tail/tail-up.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if (!snakeBack[movDir{RIGHT}].loadFromFile("textures/snake/tail/tail-right.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if (!snakeBack[movDir{DOWN}].loadFromFile("textures/snake/tail/tail-down.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    if (!snakeBack[movDir{LEFT}].loadFromFile("textures/snake/tail/tail-left.png")) {
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

const sf::Texture *TextureManager::getSnakeHead(const movDir dir) const {
    return &snakeHead[dir];
}

const sf::Texture *TextureManager::getSnakeBody(const movDir dir) const {
    if (dir == UP || dir == DOWN) return &snakeBody[0];
    return &snakeBody[1];
}

const sf::Texture *TextureManager::getSnakeBack(const movDir dir) const {
    return &snakeBack[dir];
}

const sf::Texture *TextureManager::getSnakeTurn(const turnDir dir) const {
    return &snakeTurn[dir];
}


