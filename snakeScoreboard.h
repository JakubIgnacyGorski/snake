//
// Created by jakub on 12.05.24.
//

#ifndef SNAKE_SNAKESCOREBOARD_H
#define SNAKE_SNAKESCOREBOARD_H
#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>

#include "FontManager.h"

constexpr unsigned int scoreboardSize = 10;
constexpr unsigned int playerNickLength = 12;
constexpr unsigned int playerScoreLength = 9;

struct playerScoreboard {
    std::string name;
    unsigned int score;
};

class snakeScoreboard {
    std::array<playerScoreboard, scoreboardSize> player;
    unsigned short int scoreboardCount;
    const std::string saveFileName="scoreboard.save";
    void sortPlayerScoreboard();
    bool saveScoreboardToFile();
    bool compareName(const std::string & playerName, unsigned int playerScore);
    bool compareScore(const std::string & playerName, unsigned int playerScore);
public:
    snakeScoreboard();
    void addPlayerToScoreboard(std::string playerName, unsigned int playerScore);
    int getScoreboardCount() const;
    playerScoreboard & getPlayerdata(unsigned int playerNumber);
};


#endif //SNAKE_SNAKESCOREBOARD_H
