//
// Created by jakub on 12.05.24.
//

#ifndef SNAKE_SNAKESCOREBOARD_H
#define SNAKE_SNAKESCOREBOARD_H
#include <iostream>
#include <array>

const unsigned int scoreboardSize = 10;

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
    bool compareScore(const std::string &playerName, unsigned int playerScore);
public:
    snakeScoreboard();
    void addPlayerToScoreboard(const std::string & playerName, unsigned int playerScore);
};


#endif //SNAKE_SNAKESCOREBOARD_H
