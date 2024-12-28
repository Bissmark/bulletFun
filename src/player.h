#pragma once
#include <raylib.h>

class Player
{
    public: 
        Player();
        void Update();
        void Move();
        void Draw() const;

    private:
        int healthPoints;
        int x;
        int y;
        int speedX;
        int speedY;
        int radius;
        Texture2D playerIdle;
        Texture2D playerWalk;
        Texture2D currentTexture;
        Rectangle frameRec;
        Vector2 playerPosition;
        int currentFrame;
        int framesCounter;
        int framesSpeed;
};