#pragma once
#include <raylib.h>
#include "player.h"

class Enemy
{
    public: 
        Enemy(Player& player);
        void Update();
        void Move();
        void Draw() const;
        void Attack();

    private:
        int healthPoints;
        int x;
        int y;
        int speedX;
        int speedY;
        int radius;
        Texture2D enemyIdle;
        Texture2D enemyWalk;
        Texture2D currentTexture;
        Rectangle frameRec;
        Vector2 enemyPosition;
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        int frameWidth;
        unsigned int numFrames;
        enum Direction { LEFT, RIGHT } direction;
        Player& player;
        void UpdateFrame();
};