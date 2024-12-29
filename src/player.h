#pragma once
#include <raylib.h>

class Player
{
    public: 
        Player();
        int radius;
        int healthPoints;
        Vector2 playerPosition;
        void Update();
        void Move();
        void Draw() const;
        void Fire();

    private:
        int speedX;
        int speedY;
        Texture2D playerIdle;
        Texture2D playerWalk;
        Texture2D currentTexture;
        Rectangle frameRec;
        Rectangle boxCollision;
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        int frameWidth;
        int currentEnemiesKilled;
        unsigned int numFrames;
        enum Direction { LEFT, RIGHT } direction;
        void UpdateFrame();
};