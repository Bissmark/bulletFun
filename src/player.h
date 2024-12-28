#pragma once
#include <raylib.h>

class Player
{
    public: 
        Player();
        Vector2 playerPosition;
        int healthPoints;
        int radius;
        void Update();
        void Move();
        void Draw() const;
        void Fire();

    private:
        int x;
        int y;
        int speedX;
        int speedY;
        Texture2D playerIdle;
        Texture2D playerWalk;
        Texture2D currentTexture;
        Rectangle frameRec;
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        int frameWidth;
        unsigned int numFrames;
        enum Direction { LEFT, RIGHT } direction;
        void UpdateFrame();
};