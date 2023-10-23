#include "StaticEntity.h"


StaticEntity::StaticEntity(int x, int y, int width, int height) : Entity(x, y, width, height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

StaticEntity::~StaticEntity() {
    // TODO Auto-generated destructor stub
}

void StaticEntity::tick(){
}

void StaticEntity::drawRock() {
    ofSetColor(ofColor::black);
    draw(); 
}

void StaticEntity::draw(){
    ofDrawRectangle(x*width, y*height, width, height);
}