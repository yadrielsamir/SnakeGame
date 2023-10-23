#include "PauseState.h"

//--------------------------------------------------------------
PauseState::PauseState() {
    
}   
//--------------------------------------------------------------
PauseState::~PauseState() {

}
//--------------------------------------------------------------
void PauseState::reset() {
    setFinished(false);
    setNextState("");
}
//--------------------------------------------------------------
void PauseState::update() {

}
//--------------------------------------------------------------
void PauseState::draw() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string buttonText = "Continue";
    int buttonWidth = buttonText.length() * 8;
    int buttonHeight = 20;
    int buttonX = ofGetWidth() / 2 - buttonWidth / 2;
    int buttonY = ofGetHeight() / 2 - buttonHeight / 2;
    continueButton.set(buttonX, buttonY, buttonWidth, buttonHeight);
    ofDrawBitmapString(buttonText, buttonX + 5, buttonY + buttonHeight - 8);
}

//------------------------------------------------------------------
void PauseState::keyPressed(int key){
    
}

//--------------------------------------------------------------
void PauseState::mousePressed(int x, int y, int button){
    if (button == OF_MOUSE_BUTTON_LEFT && continueButton.inside(x, y)) {
        setFinished(true);
        setNextState("GameState");
        return;
    }
}
