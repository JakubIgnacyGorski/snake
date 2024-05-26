//
// Created by c on 5/16/24.
//

#ifndef SNAKE_FONTMANAGER_H
#define SNAKE_FONTMANAGER_H
#include <SFML/Graphics/Text.hpp>

class FontManager {
    sf::Font Font;
public:
    FontManager();
    sf::Font & getFont();
};


#endif //SNAKE_FONTMANAGER_H
