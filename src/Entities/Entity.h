#pragma once
#include "ofMain.h"

class Entity {

  public:
    explicit Entity(int x, int y, int width, int height);

    int x, y, width, height;
    virtual void tick() = 0;
    virtual void draw() = 0;
};