#pragma once

#include "State.h"
#include "Snake.h"
#include "ofMain.h"
#include "StaticEntity.h"

class GameState : public State {
    public:
        GameState();
        ~GameState();
        void reset();
        void update();
        void draw();
        void keyPressed(int key);
        void foodSpawner();
        void drawScore();
        void drawFood();
        void drawPowerUp(); 
        void drawStartScreen();
        void drawLostScreen();
        void drawBoardGrid();
        void mousePressed(int x, int y, int button);
        void powerUp(string powerName);
        void pathFinding();
        
        Snake* snake;
        
        bool foodSpawned = false;

        int currentFoodX;
        int currentFoodY;

        int boardSizeWidth, boardSizeHeight;
        int cellSize; // Pixels
        int score;
        bool path;
        string power;
        int boostime;
        int godtime;
        bool used;
        bool dontActivate;
        int enX, enY, enW, enH;
        vector<StaticEntity*> rocks;
        int foodSpawnTime; 
};