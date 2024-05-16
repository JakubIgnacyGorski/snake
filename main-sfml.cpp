#include <SFML/Graphics.hpp>
#include "snakeBody.h"
#include "snakeViewer.h"
#include "snakeController.h"
#include "snakeScoreboard.h"


int main() {

    sf::RenderWindow window (sf::VideoMode(1000,800), "Snake");

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    snakeBody body;
    snakeViewer viewer(body, window);
    snakeMenu menu{window};
    snakeScoreboard scoreboard;
    snakeController ctr(body, viewer, menu,scoreboard);

    ctr.play(window);
    
    return 0;
}
