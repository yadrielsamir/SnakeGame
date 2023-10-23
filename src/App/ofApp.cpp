#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetWindowTitle("Snake");

    gameState = new GameState();
    menuState = new MenuState();
    loseState = new LoseState(gameState);
    pauseState = new PauseState();
    currentState = menuState;

    //music
    sound.load("Beach.mp3");
	sound.setLoop(true);
	sound.play();

}

//--------------------------------------------------------------
void ofApp::update(){
    if(currentState->hasFinished()) {
        if(currentState->getNextState() == "GameState") {
           if(currentState != pauseState){
                gameState->reset();
           }
            currentState = gameState;
            gameState->setFinished(false);
            gameState->setNextState("");
        } else if(currentState->getNextState() == "MenuState") {
            menuState->reset();
            currentState = menuState;
        }
        else if(currentState->getNextState() == "LoseState") {
            loseState->reset();
            currentState = loseState; 
        }
        else if(currentState->getNextState() == "PauseState") {
            pauseState->reset();
            currentState = pauseState; 
        }
    }
    currentState->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    currentState->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    currentState->keyPressed(key);
}
//--------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button){
    currentState->mousePressed(x, y, button);
}