//
// Created by jakub on 12.05.24.
//

#include "snakeScoreboard.h"
#include <fstream> // źródło: https://cplusplus.com/doc/tutorial/files/
#include <sstream>
#include <algorithm>

snakeScoreboard::snakeScoreboard(){
    std::ifstream scoreboardFile;
    std::string line;
    scoreboardCount=0;
    scoreboardFile.open(saveFileName);

    if (!scoreboardFile.is_open()) {
        std::cerr << "Scoreboard file doesn't exist" << std::endl;
        return;
    }

    while (std::getline(scoreboardFile, line) && scoreboardCount<scoreboardSize){
        std::istringstream iss(line); //źródło: https://cplusplus.com/reference/sstream/istringstream/istringstream/
        iss >> player[scoreboardCount].name >> player[scoreboardCount].score;
//        std::cout << "Nazwa: " << player[scoreboardCount].name << " Punkty: " << player[scoreboardCount].score << std::endl;
        scoreboardCount++;
    }

    scoreboardFile.close();
    sortPlayerScoreboard();
}

void snakeScoreboard::sortPlayerScoreboard() {
    struct { //źródło: https://en.cppreference.com/w/cpp/algorithm/sort
        bool operator()(playerScoreboard const & a, playerScoreboard const & b) const { return  a.score> b.score; }
    } sortCompare;

    std::sort(player.begin(), player.begin()+scoreboardCount, sortCompare);
}

bool snakeScoreboard::saveScoreboardToFile() {
    std::ofstream scoreboardFile;
    scoreboardFile.open(saveFileName, std::ios::trunc);

    if (!scoreboardFile.is_open()) {
        std::cerr << "Can't save scoreboard" << std::endl;
        abort();
    }

    for (int lineCount=0; lineCount<scoreboardCount; lineCount++) {
        scoreboardFile << player[lineCount].name << ' ' <<player[lineCount].score<<std::endl;
    }
    scoreboardFile.close();

    return true;
}

bool snakeScoreboard::compareName(const std::string &playerName, const unsigned int playerScore) {
    for (int playerCount=0; playerCount<scoreboardCount; playerCount++) {
        if (std::equal(player[playerCount].name.begin(), player[playerCount].name.end(),
                       playerName.begin(), playerName.end())){
            if (playerScore>player[playerCount].score) {
                player[playerCount].score = playerScore;
            }
            return true;
        }
    }
    return false;
}

bool snakeScoreboard::compareScore(const std::string &playerName, const unsigned int playerScore) {
    if (playerScore > player[scoreboardCount-1].score) {
        player[scoreboardCount-1].name = playerName;
        player[scoreboardCount-1].score = playerScore;
        return true;
    }
    return false;
}

void snakeScoreboard::addPlayerToScoreboard(std::string playerName, const unsigned int playerScore) {
    while (playerName.size() > playerNickLength) playerName.pop_back();
    if (!compareName(playerName, playerScore)) {
        if (scoreboardCount==scoreboardSize) {
            compareScore(playerName, playerScore);
        } else {
            player[scoreboardCount].name=playerName;
            player[scoreboardCount].score=playerScore;
            scoreboardCount++;
        }
    }

    sortPlayerScoreboard();
    saveScoreboardToFile();
}

int snakeScoreboard::getScoreboardCount() const {
    return scoreboardCount;
}

playerScoreboard &snakeScoreboard::getPlayerdata(const unsigned int playerNumber) {
    if ( playerNumber >= scoreboardCount ) {
        // dodać informacje o powodzie błędu
        abort();
    }
    return player[playerNumber];
}
