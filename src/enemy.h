#pragma once
#include <raylib.h>

class Enemy
{
    public: 
        Enemy();
        void Update();
        void Draw() const;

    private:
        int healthPoints;
        int x;
        int y;
        int speedX;
        int speedY;
        int radius;
        Texture2D enemyIdle;
        Rectangle frameRec;
        Vector2 enemyPosition;
        int currentFrame;
        int framesCounter;
        int framesSpeed;
};