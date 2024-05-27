//
// Created by jakub on 26.05.24.
//

#ifndef SNAKE_TEXTUREMANAGER_H
#define SNAKE_TEXTUREMANAGER_H
#include <SFML/Graphics/Texture.hpp>

class TextureManager {
    sf::Texture snakeHead[4];
    sf::Texture snakeBody[4];
    sf::Texture background;
public:
    TextureManager();
    const sf::Texture * getBackgroundTexture() const;
    const sf::Texture * getSnakeHead(int dir) const;
    const sf::Texture * getSnakeBody(int dir) const;
};


#endif //SNAKE_TEXTUREMANAGER_H
