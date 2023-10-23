#pragma once
#include "Entity.h"

class StaticEntity: public Entity{

    public:
        StaticEntity(int x, int y, int width, int height);
        ~StaticEntity();
        int x, y, width, height;
        void tick();
        void drawRock();
        void draw();
};