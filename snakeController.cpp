//
// Created by jakub on 09.05.24.
//

#include "snakeController.h"
#include <iostream>
#include <cmath>

snakeController::snakeController(snakeBody &b, snakeViewer &v, snakeMenu &m, snakeScoreboardViewer & scb) : snake(b), viewer(v), menu(m), scbViewer(scb) {
    timeToMove = 200;
}

void snakeController::keyboardGame(sf::Event &event) {
    switch (event.key.code) {
        case (sf::Keyboard::Key::Right):
            changeDirection(speed{1, 0});
            break;
        case (sf::Keyboard::Key::Left):
            changeDirection(speed{-1, 0});
            break;
        case (sf::Keyboard::Key::Up):
            changeDirection(speed{0, -1});
            break;
        case (sf::Keyboard::Key::Down):
            changeDirection(speed{0, 1});
            break;
        default:
            return;
    }
    viewer.updateView();
}

void snakeController::timeMove() {
    speed snakeSpeed = snake.getSnakeSpeed();
    if (snakeSpeed == speed{0,0}) return;

    moveDelay = clock.getElapsedTime();
    if (moveDelay.asMilliseconds()<=timeToMove) return;

    snake.snakeMove(snakeSpeed);
    if (snake.snakeEating()) viewer.addSnakePart();
    viewer.updateView();
    moveDelay = clock.restart();
}

void snakeController::changeDirection(speed newDir) {
    const speed reversDir {-newDir.Vx, -newDir.Vy};
    speed snakeSpeed = snake.getSnakeSpeed();
    if (snakeSpeed == newDir || snake.getSnakeSpeed()==reversDir) return;
    if (snakeSpeed == speed{0,0} && newDir.Vx<0) return;
    snake.snakeMove(newDir);
    if (snake.snakeEating()) viewer.addSnakePart();
    moveDelay=clock.restart();
}

void snakeController::mouse(sf::Event &event, sf::RenderWindow & window) {
    if (snake.getGameState()==SCOREBOARD_VIEW) {
        createNewGame(window, MENU);
        return;
    }
    if (event.mouseButton.button != sf::Mouse::Button::Left) return;

    std::string button = menu.buttonPressed(event.mouseButton.x, event.mouseButton.y);

    if (button == "EXIT") {
        window.close();
    } else if (button == "EASY") {
        snake.setGameDifficulty(EASY);
        createNewGame(window, RUNNING);
    } else if (button == "NORMAL") {
        snake.setGameDifficulty(NORMAL);
        createNewGame(window, RUNNING);
    } else if (button == "HARD") {
        snake.setGameDifficulty(HARD);
        createNewGame(window, RUNNING);
    } else if (button == "SCOREBOARD") {
        createNewGame(window, SCOREBOARD_VIEW);
    }
}

int snakeController::findBoardDevider(const int windowWidth, const int windowHeight) const {
    //źródło: https://pl.wikipedia.org/wiki/Algorytm_Euklidesa
    int div=windowWidth;
    int b=windowHeight;
    int c;
    while (b != 0){
        c = div % b;
        div = b;
        b = c;
    }

    while (div > windowWidth * 0.07 || div > windowHeight * 0.07) {
        b = std::round(div * 0.5);
        while (b != 0){
            c = div % b;
            div = b;
            b = c;
        }
    }
    return div;
}

void snakeController::createNewGame(const sf::RenderWindow & window, const GameState State) {
    const int windowWidth = window.getSize().x;
    const int windowHeight = window.getSize().y-viewer.getOffsetY();
    int dev = findBoardDevider(windowWidth, windowHeight);

    int width = windowWidth/dev;
    int height = windowHeight/dev;

    int snakeLength;
    GameDifficulty newDif = snake.getGameDifficulty();
    switch (newDif) {
        case EASY:
            snakeLength = static_cast<int>(width*0.3);
            timeToMove = 1000;
            break;
        case NORMAL:
            snakeLength = static_cast<int>(width*0.5);
            timeToMove = 75;
            break;
        case HARD:
            snakeLength = static_cast<int>(width*0.7);
            timeToMove = 25;
            break;
    }

    snake = snakeBody(width, height, snakeLength, State);
    snake.setGameDifficulty(newDif);
    viewer.newSnake();
}


void snakeController::play(sf::RenderWindow & window) {
    sf::Event event{};
    GameState previousState=snake.getGameState();
    while (window.isOpen()) {
        while(window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (snake.getGameState() == RUNNING)
                        keyboardGame(event);
                    if (snake.getGameState() == SCOREBOARD_VIEW &&
                        event.key.code == sf::Keyboard::Key::Enter)
                        createNewGame(window, MENU);
                    break;
                case sf::Event::MouseButtonPressed:
                    if (snake.getGameState() == MENU || snake.getGameState() == SCOREBOARD_VIEW)
                        mouse(event, window);
                    break;
                case sf::Event::TextEntered:
                    if (snake.getGameState() == SCOREBOARD_WRITE) {
                        if (scbViewer.inputText(event))
                            createNewGame(window, SCOREBOARD_VIEW);
                    }
                    break;
                default:
                    break;
            }
        }

        switch (snake.getGameState()) {
            case RUNNING:
                timeMove();
                viewer.drawGame(window);
                previousState=RUNNING;
                break;
            case MENU:
                menu.drawMenu(window);
                previousState=MENU;
                break;
            case SCOREBOARD_WRITE:
                if (previousState!=SCOREBOARD_WRITE) scbViewer.updateWriteText();
                scbViewer.drawScoreboardSave(window);
                previousState=SCOREBOARD_WRITE;
                break;
            case SCOREBOARD_VIEW:
                if (previousState!=SCOREBOARD_VIEW) scbViewer.updateViewText();
                scbViewer.drawScoreboard(window);
                previousState=SCOREBOARD_VIEW;
                break;
        }
        window.display();
    }
}






