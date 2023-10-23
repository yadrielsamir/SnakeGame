#pragma once

#include "State.h"
#include "ofMain.h"
#include "GameState.h"

class LoseState : public State {

public:
    LoseState(GameState* gameStatePtr);
    ~LoseState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    GameState* gameState;
};