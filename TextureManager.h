//
// Created by jakub on 26.05.24.
//

#ifndef SNAKE_TEXTUREMANAGER_H
#define SNAKE_TEXTUREMANAGER_H
#include <SFML/Graphics/Texture.hpp>

enum movDir { UP, RIGHT, DOWN, LEFT};
enum turnDir { DOWNLEFT, DOWNRIGHT, UPLEFT, UPRIGHT};

class TextureManager {
    sf::Texture snakeHead[4];
    sf::Texture snakeBack[4];
    sf::Texture snakeTurn[4];
    sf::Texture snakeBody[2];
    sf::Texture background;
public:
    TextureManager();
    const sf::Texture * getBackgroundTexture() const;
    const sf::Texture * getSnakeHead(movDir dir) const;
    const sf::Texture * getSnakeBody(movDir dir) const;
    const sf::Texture * getSnakeBack(movDir dir) const;
    const sf::Texture * getSnakeTurn(turnDir dir) const;
};


#endif //SNAKE_TEXTUREMANAGER_H
