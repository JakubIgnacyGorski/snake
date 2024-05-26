//
// Created by jakub on 26.05.24.
//

#ifndef SNAKE_TEXTUREMANAGER_H
#define SNAKE_TEXTUREMANAGER_H
#include <SFML/Graphics/Texture.hpp>

enum textureNames { TEST };

struct tex {
    sf::Texture texture;
    textureNames name;
    bool operator==(const textureNames &n) const {return (name==n);}
};

class TextureManager {
public:
    TextureManager();
    sf::Texture & getTexture(const textureNames texName );
};


#endif //SNAKE_TEXTUREMANAGER_H
