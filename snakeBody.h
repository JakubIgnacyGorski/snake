//
// Created by jakub on 08.05.24.
//

#ifndef SNAKE_SNAKEBODY_H
#define SNAKE_SNAKEBODY_H
#include <list>
#include <vector>

enum GameState {RUNNING, SCOREBOARD_WRITE, SCOREBOARD_VIEW, MENU};
enum GameDifficulty {EASY, NORMAL, HARD};

struct point {
    int x,y;
    bool operator==(const point &p) const {return (x==p.x && y==p.y);}
    bool operator!=(const point &p) const {return (x!=p.x || y!=p.y);}
};

struct speed {
    int Vx, Vy;
    bool operator==(const speed &s) const {return (Vx==s.Vx && Vy==s.Vy);}
    bool operator!=(const speed &s) const {return (Vx!=s.Vx || Vy!=s.Vy);}
};

struct snakeBodyPart {
    point position;
    speed bodySpeed;
};

class snakeBody {
    std::list<snakeBodyPart> bodyPosition;
    speed snakeSpeed;
    GameState state;
    GameDifficulty difficulty;
    unsigned int score;

    point fruitPoint;
    int boardWidth;
    int boardHeight;
    void placeFruit();
public:
    snakeBody();
    snakeBody(int width, int height, int snakeLength, GameState startupState);
    [[nodiscard]] bool isOnMap(const point & item) const;
    bool snakeMove(const speed & newSnakeSpeed);
    char isPartOfSnake(const point & lookingPoint) const;
    void debug_display() const;
    bool collisionDetection(const point & item) const;
    bool isSnakeCanEat(const point & item) const;
    bool snakeEating();
    const std::list<snakeBodyPart> & snakePosition();
    int getSnakeLength() const;
    point getFruitPoint() const;
    speed getSnakeSpeed() const;
    void setSnakeSpeed(speed newSpeed);
    GameState getGameState() const;
    point getBoardSize() const;
    unsigned int getScore() const;
    GameDifficulty getGameDifficulty() const;
    void setGameDifficulty(GameDifficulty newDif);
};


#endif //SNAKE_SNAKEBODY_H
