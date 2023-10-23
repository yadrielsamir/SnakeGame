#include "GameState.h"

//--------------------------------------------------------------
GameState::GameState() {
    foodSpawned = false;
    path = false; 
    cellSize = 25;
    boardSizeWidth = 64;
    boardSizeHeight = 36;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
}
//--------------------------------------------------------------
GameState::~GameState() {
    delete snake;
}
//--------------------------------------------------------------
void GameState::reset() {
    delete snake;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
    rocks.clear();
    for(int i = 0; i < 30; i++){
        enX = ofRandom(1, boardSizeWidth-1);
        enY = ofRandom(1, boardSizeHeight-1);
        StaticEntity* rock = new StaticEntity(enX, enY, cellSize, cellSize);
        rocks.push_back(rock);
    }
    foodSpawned = false;
    path = false; 
    score = 0;
    boostime = 0;
    godtime = 0;
    power = "None";
    used = false; 
}
//--------------------------------------------------------------
void GameState::update() {
    if(snake->isCrashed()) {
        this->setNextState("LoseState");
        this->setFinished(true);
        return;
    }

    if(snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY) {      
        score += 10;                           
        snake->grow();
        foodSpawned = false;
    }

    for (unsigned int i = 0; i < rocks.size(); i++) {
        if (!snake->godmode && snake->getHead()[0] == rocks[i]->x && snake->getHead()[1] == rocks[i]->y) {
            snake->crashed = true;
            break;
        }
    }

    foodSpawner();

    //SpeedBoost timer
    if(boostime > 0) {
        if(ofGetFrameNum() % 5 == 0) { 
            snake->update();
        }
        boostime--; 
    } else {
        if(ofGetFrameNum() % 10 == 0) {
            snake->update();
        }
    }

    // GodMode timer
    if(godtime > 0) {
        snake->godmode = true;
        godtime--;
    }
    else{
        snake->godmode = false;
    }

    //Powerup milestone
    if(!used){
        if(score == 60){
            power = "SpeedBoost";
        }
        else if(score == 110){
            power = "BetterApple";
        }
        else if(score == 160){
            power = "GodMode";
        }
    }
}
//--------------------------------------------------------------
void GameState::draw() {
    drawBoardGrid();
    snake->draw();
    drawFood();
    drawScore();
    drawPowerUp();
    for (unsigned int i = 0; i < rocks.size(); i++) {
        rocks[i]->drawRock();
    }
    if(path){
        pathFinding();
    }
}
//--------------------------------------------------------------
void GameState::keyPressed(int key) {

    if(key != OF_KEY_LEFT && key != OF_KEY_RIGHT && key != OF_KEY_UP && key != OF_KEY_DOWN && key != 'a' && key != 'u' && key != 'p' && key != 'b' && key != 'g') { return; }

    switch(key) {
        case OF_KEY_LEFT:
            snake->changeDirection(LEFT);
            break;
        case OF_KEY_RIGHT:
            snake->changeDirection(RIGHT);
            break;
        case OF_KEY_UP:
            snake->changeDirection(UP);
            break;
        case OF_KEY_DOWN:
            snake->changeDirection(DOWN);
            break;
        case 'a':
            score += 10;
            break;
        case 'u':
            snake->ungrow();
            break;
        case 'p':
            this->setNextState("PauseState");
            this->setFinished(true); 
        case 'b':
            powerUp(power);
            break;
        case 'g':
            path = !path;
            break;
    }
}
//--------------------------------------------------------------
void GameState::foodSpawner() {
    if(!foodSpawned) {
        bool isInSnakeBody;
        do {
            isInSnakeBody = false;
            currentFoodX = ofRandom(1, boardSizeWidth-1);
            currentFoodY = ofRandom(1, boardSizeHeight-1);
            for(unsigned int i = 0; i < snake->getBody().size(); i++) {
                if(currentFoodX == snake->getBody()[i][0] and currentFoodY == snake->getBody()[i][1]) {
                    isInSnakeBody = true;
                }
            }
        } while(isInSnakeBody);
        foodSpawned = true;
        foodSpawnTime = 0;
    }
    else{
        if(foodSpawnTime > 15000){
            foodSpawned = false;
            drawFood();
        }
        else{
            foodSpawnTime += ofGetLastFrameTime() * 1000;
        }
    }
}
//--------------------------------------------------------------
void GameState::drawScore() {               
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Score: " + ofToString(score), 20, 40);
}
//--------------------------------------------------------------
void GameState::drawPowerUp() {
    ofSetColor(ofColor::white);
    ofDrawBitmapString("PowerUp: " + power, 20, 60);
    if(boostime > 0){
        ofDrawBitmapString("Time of SpeedBoost: " + ofToString(boostime) , 20, 80);
    }
    if(godtime > 0){
        ofDrawBitmapString("Time of GodMode: " + ofToString(godtime) , 20, 80);
    }
}
//--------------------------------------------------------------
void GameState::drawFood() {
    if(foodSpawned){
        float rotten = foodSpawnTime / 15000.0;
        ofColor foodColor = ofColor(210 * (1.0 - rotten / 1.5), 75 * (1.0 - rotten), 40 * (1.0 - rotten / 2));
        ofSetColor(foodColor);
        if(score == 50){
            used = false; 
            ofSetColor(ofColor::blue);
        }
        else if(score == 100){
            used = false; 
            ofSetColor(ofColor::orange);
        }
        else if(score == 150){
            used = false; 
            ofSetColor(ofColor::violet);
        }
        ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
    }
}
//--------------------------------------------------------------
void GameState::drawStartScreen() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "Press any arrow key to start.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    return;
}
//--------------------------------------------------------------
void GameState::drawLostScreen() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "You lost! Press any arrow key to play again";
    string text2 = "or press ESC to exit.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    ofDrawBitmapString(text2, ofGetWidth()/2-8*text2.length()/2, ofGetHeight()/2+2);
    return;
}
//--------------------------------------------------------------
void GameState::drawBoardGrid() {
    
    ofDrawGrid(25, 64, false, false, false, true);
    
    // ofSetColor(ofColor::white);
    // for(int i = 0; i <= boardSize; i++) {
    //     ofDrawLine(i*cellSize, 0, i*cellSize, ofGetHeight());
    //     ofDrawLine(0, i*cellSize, ofGetWidth(), i*cellSize);
    // }
}
//--------------------------------------------------------------
void GameState::mousePressed(int x, int y, int button){
    
}
//--------------------------------------------------------------
void GameState::powerUp(string powerName){
    if(powerName == "SpeedBoost"){
        boostime = 15 * ofGetFrameRate();
    }
    else if(powerName == "BetterApple"){
        (snake->upgrade = true);
    }
    else if(powerName == "GodMode"){
        godtime = 10 * ofGetFrameRate();
    }
    used = true;
    power = "None";
}
//--------------------------------------------------------------
int rockLocation(vector<int> head, int cellSize, vector<StaticEntity*> rocks,  Snake* snake){
    for(unsigned int i = 0; i < rocks.size(); i++) {
        if(rocks[i]->x  ==  head[0] && rocks[i]->y == head[1]){
            return 0;
        }
    }
    for(unsigned int i = 0; i < snake->getBody().size(); i++) {
        if(snake->getBody()[i][0] == head[0] && snake->getBody()[i][1] == head[1]) {
            return 1;
        }
    }
    return 2;
}

void drawX(vector<int> head, int x, int cellSize, int currentFoodX, vector<StaticEntity*> rocks,  Snake* snake) {
    if(head[0] == currentFoodX) {
        return;
    }
    if(rockLocation(head, cellSize, rocks, snake) == 2) {
        ofDrawRectangle(head[0] * cellSize, head[1] * cellSize, cellSize, cellSize);
    } 
    else if(rockLocation(head, cellSize, rocks, snake) == 1 && snake->direction == RIGHT){
        ofDrawRectangle((head[0] - (snake->getBody().size())) * cellSize, head[1]* cellSize, cellSize, cellSize);
    }
    else if(rockLocation(head, cellSize, rocks, snake) == 1 && snake->direction == LEFT){
        ofDrawRectangle((head[0] + (snake->getBody().size())) * cellSize, head[1] * cellSize, cellSize, cellSize);
    }
    else if(rockLocation(head, cellSize, rocks, snake) == 0){
        ofDrawRectangle(head[0] * cellSize, (head[1] + 1) * cellSize, cellSize, cellSize);
    }
    head[0] += x;
    drawX(head, x, cellSize, currentFoodX, rocks, snake);
}


void drawY(vector<int> head, int y, int cellSize, int currentFoodY, int& currentFoodX, vector<StaticEntity*> rocks,  Snake* snake){
    if (head[1] == currentFoodY){
        return; 
    }
    ofDrawRectangle(currentFoodX * cellSize, head[1] * cellSize, cellSize, cellSize);
    head [1] += y;
    drawY(head, y, cellSize, currentFoodY, currentFoodX, rocks, snake);
}

void GameState::pathFinding(){
    ofSetColor(ofColor::orange);
    if (snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY){
        return;
    }
    int dirx = (currentFoodX > snake->getHead()[0]) ? 1 : -1; 
    int diry = (currentFoodY > snake->getHead()[1]) ? 1 : -1;
    if(snake->getHead()[0] != currentFoodX){
        vector<int> head = {snake->getHead()[0] + dirx, snake->getHead()[1]};
        drawX(snake->getHead(), dirx, cellSize, currentFoodX, rocks, snake);
    }
    if(snake->getHead()[1] != currentFoodY) {
        vector<int> head = {snake->getHead()[0], snake->getHead()[1] + diry};
        drawY(snake->getHead(), diry, cellSize, currentFoodY, currentFoodX, rocks, snake);
    }
}
