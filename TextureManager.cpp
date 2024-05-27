//
// Created by jakub on 26.05.24.
//

#include <cstring>
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include "TextureManager.h"

TextureManager::TextureManager() {

    if (!background.loadFromFile("textures/background.png")) {
        std::cerr << strerror(errno) << std::endl;
        abort();
    }
    background.setRepeated(true); //źródło: https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Texture.php#aaa87d1eff053b9d4d34a24c784a28658
}

const sf::Texture * TextureManager::getBackgroundTexture() const {
    return &background;
}

const sf::Texture *TextureManager::getSnakeHead(const int dir) const {
    if (dir>=4 || dir<0) return nullptr;
    return &snakeHead[dir];
}

const sf::Texture *TextureManager::getSnakeBody(const int dir) const {
    if (dir>=4 || dir<0) return nullptr;
    return &snakeBody[dir];
}