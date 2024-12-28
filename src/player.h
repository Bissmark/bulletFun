#pragma once
#include <raylib.h>

class Player
{
    public: 
        Player();
        Vector2 playerPosition;
        void Update();
        void Move();
        void Draw() const;
        void Fire();

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
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        int frameWidth;
        unsigned int numFrames;
        enum Direction { LEFT, RIGHT } direction;
        void UpdateFrame();
};