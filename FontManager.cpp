//
// Created by c on 5/16/24.
//

#include "FontManager.h"
#include <iostream>
#include <cstring>

FontManager::FontManager() {
    if (!Font.loadFromFile("fonts/sd-snatcher.ttf")) {
        std::cerr <<strerror(errno) << std::endl;
        abort();
    }
}

sf::Font & FontManager::getFont() {
    return Font;
}
