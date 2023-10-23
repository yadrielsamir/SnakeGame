#pragma once
#include <vector>

enum Direction {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NONE
    };

class Snake {

private:
    std::vector<std::vector<int>> body;
    int boardSizeWidth, boardSizeHeight;
    int segmentSize;
    
public:
    Snake(int segmentSize, int boardSizeW, int boardSizeH);
    ~Snake();

    Direction direction;
    bool crashed;
    bool upgrade;
    bool godmode;
    void update();
    void draw();
    void changeDirection(Direction d);
    void checkSelfCrash();
    void grow();
    void ungrow();
    bool isCrashed() {
        return this->crashed;
    }
    std::vector<int> getHead() {
        return this->body[0];
    }
    std::vector<int> getTail() {
        return this->body[this->body.size() - 1];
    }
    std::vector<std::vector<int>> getBody() {
        return this->body;
    }
};
