//
// Created by jakub on 20.05.24.
//

#include "snakeScoreboardViewer.h"

snakeScoreboardViewer::snakeScoreboardViewer(snakeBody & s, FontManager & f, snakeScoreboard & scb, const sf::RenderWindow & window ) : snake(s), fontmgr(f), scoreboard(scb){
    windowWidth = window.getSize().x;
    windowHeight = window.getSize().y;

    setupViewText();
    updateViewText();
}

void snakeScoreboardViewer::setupViewText() {
    const unsigned int textSpaceY=windowHeight/(scoreboardSize+4);

    ScoreboardTitle.setCharacterSize(textSpaceY*0.8);
    ScoreboardTitle.setFont(fontmgr.getFont());
    ScoreboardTitle.setFillColor(sf::Color::Black);
    ScoreboardTitle.setString("Scoreboard:");
    unsigned int x=(windowWidth-ScoreboardTitle.getLocalBounds().width)*0.5;
    ScoreboardTitle.setPosition(x,textSpaceY*0.2);

    for (sf::Text & text : ScoreboardText) {
        text.setCharacterSize(textSpaceY*0.5);
        text.setFont(fontmgr.getFont());
        text.setFillColor(sf::Color::Black);
    }
}

void snakeScoreboardViewer::updateViewText() {
    const unsigned int textSpaceY=windowHeight/(scoreboardSize+4);
    const unsigned int x=(windowWidth-ScoreboardText[0].getCharacterSize()*(5 + playerNickLength + playerScoreLength))*0.5;
    unsigned int y;
    std::string tmpString;
    for (int text=0; text<scoreboard.getScoreboardCount(); text++) {
        if (text<9) tmpString.append("  ");                                     // Dodanie spacji żeby . liczb się zgadzały
        tmpString.append(std::to_string(text+1));                          // numeracja
        tmpString.append(". ");                                                 // kropka od numeracji
        tmpString.append(scoreboard.getPlayerdata(text).name);
        while (tmpString.size() < 5 + playerNickLength) tmpString.append(".");  // kropki po nazwie gracza
        if (text == 9) tmpString.pop_back();                                       // jeśli to jest 10 usuń 1 kropkę (ponieważ 1 == dwie spacje)
        tmpString.append(" ");                                                  // spacja po kropkach
        tmpString.append(std::to_string(scoreboard.getPlayerdata(text).score));

        y=textSpaceY*(text+2);
        ScoreboardText[text].setString(tmpString);
        ScoreboardText[text].setPosition(x, y);
        tmpString.clear();
    }
}

void snakeScoreboardViewer::setupWriteText() {
    const unsigned int textSpaceY=windowHeight/(scoreboardSize+4);

    ScoreTitle.setCharacterSize(textSpaceY*0.8);
    ScoreTitle.setFont(fontmgr.getFont());
    ScoreTitle.setFillColor(sf::Color::Black);
    ScoreTitle.setString("Your score was: ");
}

void snakeScoreboardViewer::drawScoreboard(sf::RenderWindow &window) const {
    window.clear(sf::Color(250, 250, 250));
    window.draw(ScoreboardTitle);
    for (const sf::Text & text : ScoreboardText) {
        window.draw(text);
    }
}

void snakeScoreboardViewer::drawScoreboardSave(sf::RenderWindow &window) const {
    window.clear(sf::Color(250, 250, 250));
    window.draw(ScoreTitle);
    window.draw(playerScore);
}


