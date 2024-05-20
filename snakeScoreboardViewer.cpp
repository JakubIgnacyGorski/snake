//
// Created by jakub on 20.05.24.
//

#include "snakeScoreboardViewer.h"

snakeScoreboardViewer::snakeScoreboardViewer( FontManager & f, snakeScoreboard & s, const sf::RenderWindow & window ) : fontmgr(f), scoreboard(s){
    windowWidth = window.getSize().x;
    windowHeight = window.getSize().y;

    setupText();
    updateText();
}

void snakeScoreboardViewer::setupText() {
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

void snakeScoreboardViewer::updateText() {
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
//        std::cout<<ScoreboardText[text].getGlobalBounds().left<<", "<<ScoreboardText[text].getGlobalBounds().width<<std::endl;
    }
}

void snakeScoreboardViewer::drawScoreboard(sf::RenderWindow &window) const {
    window.clear(sf::Color(250, 250, 250));
    window.draw(ScoreboardTitle);
    for (const sf::Text & text : ScoreboardText) {
        window.draw(text);
    }
}


