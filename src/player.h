#pragma once
#include <raylib.h>
#include "bullet.h"
#include <vector>

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
        std::vector<Bullet> bullets;

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