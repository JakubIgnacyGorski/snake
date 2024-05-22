#include <SFML/Graphics.hpp>
#include "snakeBody.h"
#include "snakeViewer.h"
#include "snakeController.h"
#include "snakeScoreboard.h"
#include "FontManager.h"
#include "snakeScoreboardViewer.h"

int main() {

    sf::RenderWindow window (sf::VideoMode(1000,800), "Snake");

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);
    FontManager font;
    snakeBody body;
    snakeViewer viewer(body, font, window);
    snakeMenu menu{window, font};
    snakeScoreboard scoreboard;
    snakeScoreboardViewer scbviewer(body, font, scoreboard, window);
    snakeController ctr(body, viewer, menu,scoreboard, scbviewer);

    ctr.play(window);

    return 0;
}
