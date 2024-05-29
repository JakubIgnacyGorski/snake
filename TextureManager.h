//
// Created by jakub on 26.05.24.
//

#ifndef SNAKE_TEXTUREMANAGER_H
#define SNAKE_TEXTUREMANAGER_H
#include <SFML/Graphics/Texture.hpp>
#include <array>

enum turnDir { DOWNLEFT, DOWNRIGHT, UPLEFT, UPRIGHT};

const int fruitCount = 2;

class TextureManager {
    sf::Texture snakeHead;
    sf::Texture snakeBack;
    sf::Texture snakeTurn[4];
    sf::Texture snakeBody;
    sf::Texture background;
    std::array<sf::Texture, fruitCount> fruits;
public:
    TextureManager();
    const sf::Texture * getBackgroundTexture() const;
    const sf::Texture * getSnakeHead() const;
    const sf::Texture * getSnakeBody() const;
    const sf::Texture * getSnakeBack() const;
    const sf::Texture * getSnakeTurn(turnDir dir) const;
    const sf::Texture * getFruitTexture(int textNum) const;
};


#endif //SNAKE_TEXTUREMANAGER_H
