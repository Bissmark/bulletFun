#pragma once
#include <raylib.h>
#include <vector>
#include "bullet.h"

class Player
{
    public: 
        Player();
        Vector2 playerPosition;
        int radius;
        int healthPoints;
        void Update();
        void Move();
        void Draw() const;
        void Fire();
        std::vector<Bullet> bullets;

    private:
        Texture2D playerIdle;
        Texture2D playerWalk;
        Texture2D currentTexture;
        Rectangle frameRec;
        Rectangle boxCollision;
        int speedX;
        int speedY;
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        int frameWidth;
        int currentEnemiesKilled;
        unsigned int numFrames;
        enum Direction { LEFT, RIGHT } direction;
        void UpdateFrame();
};